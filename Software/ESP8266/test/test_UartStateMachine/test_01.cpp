#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <vector>

#include "HardwareSerial.h"
#include "UartStateMachine.hpp"
#include "CobsEncoder.hpp"
#include "Crc32.hpp"

using ::testing::Invoke;
using ::testing::Return;

class MockHardwareSerial : public HardwareSerial
{
public:
    MockHardwareSerial()
        : HardwareSerial(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr)
    {
    }

    MOCK_METHOD(std::int32_t, available, (), (override));
    MOCK_METHOD(std::int32_t, peek, (), (override));
    MOCK_METHOD(std::int32_t, read, (), (override));
    MOCK_METHOD(std::int32_t, availableForWrite, (), (override));
    MOCK_METHOD(void, flush, (), (override));
    MOCK_METHOD(std::size_t, write, (std::uint8_t), (override));

    void setRxBuffer(const std::vector<std::uint8_t> &data)
    {
        testData = data;
        testDataIndex = 0;
    }

    std::vector<std::uint8_t> testData;
    size_t testDataIndex = 0;

    std::int32_t availableMock()
    {
        return static_cast<std::int32_t>(testData.size() - testDataIndex);
    }

    std::int32_t readMock()
    {
        if (testDataIndex < testData.size())
        {
            return testData[testDataIndex++];
        }
        return -1; // no more data
    }
};

class UartStateMachineTest : public ::testing::Test
{
protected:
    using ReceiverState = Device::UartStateMachine::ReceiverState;
    using RxStatus = Device::UartStateMachine::RxStatus;
    using RxSubstatus = Device::UartStateMachine::RxSubstatus;

    std::array<std::uint8_t, Device::UartStateMachine::MaxRxSize> rxBuffer{};

    MockHardwareSerial serialMock;
    Device::UartStateMachine *uartStateMachine = nullptr;

    void SetUp() override
    {
        // Set up default actions for read() / available() so it uses our internal buffers
        ON_CALL(serialMock, available())
            .WillByDefault(Invoke(&serialMock, &MockHardwareSerial::availableMock));
        ON_CALL(serialMock, read())
            .WillByDefault(Invoke(&serialMock, &MockHardwareSerial::readMock));

        uartStateMachine = new Device::UartStateMachine(serialMock);
    }

    void TearDown() override
    {
        delete uartStateMachine;
        uartStateMachine = nullptr;
    }
};

// Helper to build a valid COBS-framed packet:
//  [0] + <COBS-encoded [ length(2) + data + CRC(4) ]> + [0].
static std::vector<std::uint8_t> buildValidCobsPacket(std::vector<std::uint8_t> &payload)
{
    // 'payload' should be: [2 bytes length][data][4 bytes CRC]
    // e.g. length = payload.size() - 6
    std::vector<std::uint8_t> cobsEncoded(payload.size() + 1); // worst-case: +1 is enough for cobs overhead
    std::size_t encodedLen = Device::CobsEncoder::encode(
        payload.data(),
        payload.size(),
        cobsEncoded.data(),
        cobsEncoded.size());
    cobsEncoded.resize(encodedLen);

    // Now wrap it with [0] at start, and [0] at end
    // [0, cobsEncoded..., 0]
    std::vector<std::uint8_t> result;
    result.push_back(0x00);
    result.insert(result.end(), cobsEncoded.begin(), cobsEncoded.end());
    result.push_back(0x00);
    return result;
}

TEST_F(UartStateMachineTest, TestValidPacketFullFlow)
{
    // 1) Build a data portion
    // Let's say length = 3 bytes of data
    // so total is 2 (length field) + 3 (data) + 4 (crc) = 9
    // We'll fill it out:
    //  - [0] and [1] => length=3 (little-endian => 3=0x03, then 0x00)
    //  - data => let's pick {0xAA, 0xBB, 0xCC}
    //  - CRC => we'll compute with Crc32 on the data bytes
    std::uint16_t dataLen = 3;
    std::vector<std::uint8_t> raw;
    raw.push_back(static_cast<std::uint8_t>(dataLen & 0xFF));        // LSB
    raw.push_back(static_cast<std::uint8_t>((dataLen >> 8) & 0xFF)); // MSB
    raw.push_back(0xAA);
    raw.push_back(0xBB);
    raw.push_back(0xCC);

    std::uint32_t crcVal = Device::Crc32::compute(&raw[2], dataLen);
    // store in raw as 4 bytes
    raw.push_back(static_cast<std::uint8_t>((crcVal >> 0) & 0xFF));
    raw.push_back(static_cast<std::uint8_t>((crcVal >> 8) & 0xFF));
    raw.push_back(static_cast<std::uint8_t>((crcVal >> 16) & 0xFF));
    raw.push_back(static_cast<std::uint8_t>((crcVal >> 24) & 0xFF));

    // So 'raw' is 9 bytes total: [ lengthLow, lengthHigh, data..., CRC(4) ]

    // 2) Encode it with COBS and wrap with 0 delimiters
    auto cobsFramed = buildValidCobsPacket(raw);

    // Provide the data to the mock
    serialMock.setRxBuffer(cobsFramed);

    uartStateMachine->setRxBuffer(rxBuffer);
    uartStateMachine->open(115200);

    // 3) Repeatedly tick until we’re done
    while (uartStateMachine->getRxStatus() == RxStatus::Ongoing)
    {
        uartStateMachine->tick();
    }

    // 4) Check final results
    EXPECT_EQ(uartStateMachine->getState(), ReceiverState::Complete);
    EXPECT_EQ(uartStateMachine->getRxStatus(), RxStatus::Done);
    EXPECT_EQ(uartStateMachine->getRxSubstatus(), RxSubstatus::Ok);
}

TEST_F(UartStateMachineTest, TestOverflowBeforeDelimiter)
{
    // Provide a bunch of non-zero bytes and never a zero,
    // so the buffer gets filled without seeing a delimiter.
    // Then we expect an error.
    std::vector<std::uint8_t> bigPacket(200, 0x55); // bigger than 128
    serialMock.setRxBuffer(bigPacket);

    uartStateMachine->setRxBuffer(rxBuffer);
    uartStateMachine->open(115200);

    // Tick repeatedly
    while (serialMock.availableMock() > 0 &&
           uartStateMachine->getRxStatus() == RxStatus::Ongoing)
    {
        uartStateMachine->tick();
    }

    // We expect an error due to overflow
    EXPECT_EQ(uartStateMachine->getState(), ReceiverState::Error);
    EXPECT_EQ(uartStateMachine->getRxStatus(), RxStatus::Done);
    EXPECT_EQ(uartStateMachine->getRxSubstatus(), RxSubstatus::CobsDecodeFail);
    // or a new substatus if you prefer "Overflow"
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
