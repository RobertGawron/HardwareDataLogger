#include "UartStateMachine.hpp"
#include "ISerialInterface.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mock for ISerialInterface
#include <gmock/gmock.h>
#include "ISerialInterface.hpp"

class MockSerialInterface : public ISerialInterface
{
public:
    MockSerialInterface() : ISerialInterface(0) {}

    MOCK_METHOD(void, begin, (unsigned long baud), (override));
    MOCK_METHOD(void, begin, (unsigned long baud, SerialConfig config), (override));
    MOCK_METHOD(void, begin, (unsigned long baud, SerialConfig config, SerialMode mode), (override));
    MOCK_METHOD(void, begin, (unsigned long baud, SerialConfig config, SerialMode mode, uint8_t tx_pin), (override));
    MOCK_METHOD(void, begin, (unsigned long baud, SerialConfig config, SerialMode mode, uint8_t tx_pin, bool invert), (override));
    MOCK_METHOD(void, end, (), (override));
    MOCK_METHOD(void, updateBaudRate, (unsigned long baud), (override));
    MOCK_METHOD(size_t, setRxBufferSize, (size_t size), (override));
    MOCK_METHOD(size_t, getRxBufferSize, (), (override));
    MOCK_METHOD(bool, swap, (), (override));
    MOCK_METHOD(bool, swap, (uint8_t tx_pin), (override));
    MOCK_METHOD(bool, set_tx, (uint8_t tx_pin), (override));
    MOCK_METHOD(bool, pins, (uint8_t tx, uint8_t rx), (override));
    MOCK_METHOD(int, available, (), (override));
    MOCK_METHOD(int, peek, (), (override));
    MOCK_METHOD(bool, hasPeekBufferAPI, (), (const, override));
    MOCK_METHOD(const char *, peekBuffer, (), (override));
    MOCK_METHOD(size_t, peekAvailable, (), (override));
    MOCK_METHOD(void, peekConsume, (size_t consume), (override));

    // Mocking read()
    MOCK_METHOD(int, read, (), (override));
    MOCK_METHOD(int, read, (char *buffer, size_t size), (override));
    MOCK_METHOD(int, read, (uint8_t *buffer, size_t size), (override));
    MOCK_METHOD(size_t, readBytes, (char *buffer, size_t size), (override));
    MOCK_METHOD(size_t, readBytes, (uint8_t *buffer, size_t size), (override));

    // Mocking the write method
    MOCK_METHOD(size_t, write, (uint8_t c), (override));
    MOCK_METHOD(size_t, write, (const uint8_t *buffer, size_t size), (override));

    MOCK_METHOD(int, availableForWrite, (), (override));
    MOCK_METHOD(void, flush, (), (override));
    MOCK_METHOD(void, setDebugOutput, (bool), (override));
    MOCK_METHOD(bool, isTxEnabled, (), (override));
    MOCK_METHOD(bool, isRxEnabled, (), (override));
    MOCK_METHOD(int, baudRate, (), (override));
    MOCK_METHOD(bool, hasOverrun, (), (override));
    MOCK_METHOD(bool, hasRxError, (), (override));
    MOCK_METHOD(void, startDetectBaudrate, (), (override));
    MOCK_METHOD(unsigned long, testBaudrate, (), (override));
    MOCK_METHOD(unsigned long, detectBaudrate, (time_t timeoutMillis), (override));
};

class UartStateMachineTest : public ::testing::Test
{
protected:
    MockSerialInterface mockSerial;
    Device::UartStateMachine *stateMachine;

    void SetUp() override
    {
        stateMachine = new Device::UartStateMachine(mockSerial);
    }

    void TearDown() override
    {
        delete stateMachine;
    }
};
#if 0
/**
 * @test OpenSetsStateToIdle
 * @brief Verifies that when the state machine is opened with a baud rate, the state is set to `Idle`.
 */
TEST_F(UartStateMachineTest, OpenSetsStateToIdle)
{
    const unsigned long baud = 115200;

    EXPECT_CALL(mockSerial, begin(baud)).Times(1);
    bool result = stateMachine->open(baud);

    EXPECT_TRUE(result);
    EXPECT_EQ(stateMachine->getState(), Device::UartStateMachine::StateMachineState::Idle);
}

/**
 * @test CloseSetsStateToInactive
 * @brief Verifies that when the state machine is closed, the state is set to `Inactive`.
 */
TEST_F(UartStateMachineTest, CloseSetsStateToInactive)
{
    const unsigned long baud = 115200;

    // Expect the serial interface to begin with the correct baud rate
    EXPECT_CALL(mockSerial, begin(baud)).Times(1);

    EXPECT_CALL(mockSerial, end()).Times(1);

    bool openResult = stateMachine->open(baud);
    bool closeResult = stateMachine->close();

    EXPECT_TRUE(openResult);
    EXPECT_TRUE(closeResult);

    EXPECT_EQ(stateMachine->getState(), Device::UartStateMachine::StateMachineState::Inactive);
}

/**
 * @test TransitionFromIdleToReceivingOnData
 * @brief Verifies that when the state machine is in the `Idle` state and data is available, it transitions to the `Receiving` state.
 */
TEST_F(UartStateMachineTest, TransitionFromIdleToReceivingOnData)
{
    const unsigned long baud = 115200;

    // Expect the serial interface to begin with the correct baud rate
    EXPECT_CALL(mockSerial, begin(baud)).Times(1);

    stateMachine->open(baud);

    // Set up the buffer for receiving data
    std::array<std::uint8_t, Device::UartStateMachine::MaxRxSize> rxBuffer;
    stateMachine->setRxBuffer(rxBuffer);

    // Simulate incoming data for packet start
    EXPECT_CALL(mockSerial, available()).WillOnce(testing::Return(1)); // 1 byte available
    EXPECT_CALL(mockSerial, read()).WillOnce(testing::Return(0));      // Start of a new packet (byte 0)

    // Call tick to process the data
    stateMachine->tick();

    // Verify that the state machine transitions to the Receiving state
    EXPECT_EQ(stateMachine->getState(), Device::UartStateMachine::StateMachineState::Receiving);
    EXPECT_EQ(stateMachine->getRxStatus(), Device::UartStateMachine::RxStatus::Active);
    EXPECT_EQ(stateMachine->getRxSubstatus(), Device::UartStateMachine::RxSubstatus::Ok);
}

/**
 * @test NoRxBufferResultsInFault
 * @brief Verifies that when no `rxBuffer` is set, the state machine transitions to the `Fault` state.
 */
TEST_F(UartStateMachineTest, NoRxBufferResultsInFault)
{
    const unsigned long baud = 115200;

    // Expect the serial interface to begin with the correct baud rate
    EXPECT_CALL(mockSerial, begin(baud)).Times(1);

    stateMachine->open(baud);

    // Call tick, but since rxBuffer is not set, it should transition to Fault
    stateMachine->tick();

    // Verify that the state machine transitions to the Fault state
    EXPECT_EQ(stateMachine->getState(), Device::UartStateMachine::StateMachineState::Fault);
    EXPECT_EQ(stateMachine->getRxStatus(), Device::UartStateMachine::RxStatus::Inactive);
    EXPECT_EQ(stateMachine->getRxSubstatus(), Device::UartStateMachine::RxSubstatus::NoRxBuffer);
}

/**
 * @test TickDoesNothingWhenStateIsInactive
 * @brief Verifies that the `tick()` method does nothing when the state machine is in the `Inactive` state.
 *
 * @scenario
 * 1. The state machine is opened and then closed to set it to `Inactive`.
 * 2. `tick()` is called but no data should be processed.
 * 3. The state remains `Inactive`.
 */
TEST_F(UartStateMachineTest, TickDoesNothingWhenStateIsInactive)
{
    const unsigned long baud = 115200;

    EXPECT_CALL(mockSerial, begin(baud)).Times(1);
    EXPECT_CALL(mockSerial, end()).Times(1);

    // Simulate the state being Inactive
    stateMachine->open(baud); // Open with the baud rate
    stateMachine->close();    // Close the state machine to set the state to Inactive

    // We expect tick to do nothing because the state is Inactive
    EXPECT_CALL(mockSerial, available()).Times(0); // No data should be processed

    // Call tick when the state is Inactive
    stateMachine->tick();

    // Verify that the state has not changed and remains Inactive
    EXPECT_EQ(stateMachine->getState(), Device::UartStateMachine::StateMachineState::Inactive);
}

/**
 * @test ProcessesDataWhenBytesAvailable
 * @brief Verifies that the `tick()` method processes available data when the state machine is in the `Idle` state.
 *
 * @scenario
 * 1. The state machine is opened and a `rxBuffer` is set for receiving data.
 * 2. A byte (`0`) is simulated to be available for reading.
 * 3. The `tick()` method processes the byte and transitions to the `Receiving` state.
 */
TEST_F(UartStateMachineTest, ProcessesDataWhenBytesAvailable)
{
    const unsigned long baud = 115200;
    std::array<std::uint8_t, Device::UartStateMachine::MaxRxSize> rxBuffer;

    // Expect the serial interface to begin with the correct baud rate
    EXPECT_CALL(mockSerial, begin(baud)).Times(1);

    stateMachine->open(baud);

    // Set the rxBuffer for the state machine
    stateMachine->setRxBuffer(rxBuffer);

    // Simulate incoming data for packet start
    EXPECT_CALL(mockSerial, available()).WillOnce(testing::Return(1)); // 1 byte available
    EXPECT_CALL(mockSerial, read()).WillOnce(testing::Return(0));      // Start of a new packet (byte 0)

    // Call tick to process the data
    stateMachine->tick();

    // Verify that the state machine transitions to the Receiving state
    EXPECT_EQ(stateMachine->getState(), Device::UartStateMachine::StateMachineState::Receiving);
    EXPECT_EQ(stateMachine->getRxStatus(), Device::UartStateMachine::RxStatus::Active);
    EXPECT_EQ(stateMachine->getRxSubstatus(), Device::UartStateMachine::RxSubstatus::Ok);

    // Verify that the data was processed and written to the rxBuffer
    EXPECT_EQ(rxBuffer[0], 0); // The first byte read should be stored in the buffer
}

/**
 * @test TransitionFromReceivingToDecodingOnSecondByteZero
 * @brief Verifies that the state machine transitions from `Receiving` to `Decoding` when two consecutive `0` bytes are received.
 *
 * @scenario
 * 1. The state machine is opened and a `rxBuffer` is set for receiving data.
 * 2. Two `0` bytes are simulated: the first byte indicates the start of the COBS frame, and the second byte indicates the end of the COBS frame.
 * 3. The state machine should transition to `Decoding` when the second `0` byte is encountered.
 */
TEST_F(UartStateMachineTest, TransitionFromReceivingToDecodingOnSecondByteZero)
{
    const unsigned long baud = 115200;

    // Expect the serial interface to begin with the correct baud rate
    EXPECT_CALL(mockSerial, begin(baud)).Times(1);

    stateMachine->open(baud);

    // Set the rxBuffer for the state machine
    std::array<std::uint8_t, Device::UartStateMachine::MaxRxSize> rxBuffer;
    stateMachine->setRxBuffer(rxBuffer);

    // Simulate receiving two bytes: the first byte is 0 (COBS delimiter), and the second byte is also 0 (end of COBS frame)
    EXPECT_CALL(mockSerial, available()).WillOnce(testing::Return(2)); // 2 bytes available to read
    EXPECT_CALL(mockSerial, read()).WillOnce(testing::Return(0))       // First byte (start of frame)
        .WillOnce(testing::Return(0));                                 // Second byte (end of frame)

    // Call tick to process the data
    stateMachine->tick();

    // Verify that the state machine transitions from Receiving to Decoding
    EXPECT_EQ(stateMachine->getState(), Device::UartStateMachine::StateMachineState::Decoding);
    EXPECT_EQ(stateMachine->getRxStatus(), Device::UartStateMachine::RxStatus::Active);
    EXPECT_EQ(stateMachine->getRxSubstatus(), Device::UartStateMachine::RxSubstatus::Ok);
}

/**
 * @test TransitionToFaultOnCobsDecodeFail
 * @brief Verifies that the state machine transitions to the `Fault` state when an invalid COBS frame is encountered during decoding.
 *
 * @scenario
 * 1. The state machine is opened with a baud rate.
 * 2. The `rxBuffer` is set up for receiving data.
 * 3. During the `Receiving` state, an invalid byte is encountered that causes a COBS decode failure.
 * 4. The state machine should transition to the `Fault` state, and the `rxStatus` should be set to `Finished` with `CobsDecodeFail` as the `rxSubstatus`.
 * 5. We expect the `Fault` state to be set, indicating that a COBS decode failure occurred.
 */
TEST_F(UartStateMachineTest, TransitionToFaultOnCobsDecodeFail)
{
    const unsigned long baud = 115200;

    // Expect the serial interface to begin with the correct baud rate
    EXPECT_CALL(mockSerial, begin(baud)).Times(1);

    stateMachine->open(baud);

    // Set the rxBuffer for the state machine
    std::array<std::uint8_t, Device::UartStateMachine::MaxRxSize> rxBuffer;
    stateMachine->setRxBuffer(rxBuffer);

    // Simulate invalid COBS frame: we send data that will cause a decode failure
    EXPECT_CALL(mockSerial, available()).WillOnce(testing::Return(1)); // 1 byte available
    EXPECT_CALL(mockSerial, read()).WillOnce(testing::Return(1));      // Invalid byte causing decode failure

    // Call tick to process the data
    stateMachine->tick();

    // Verify that the state machine transitions to the Fault state
    EXPECT_EQ(stateMachine->getState(), Device::UartStateMachine::StateMachineState::Fault);

    // Verify that the rxStatus is Finished, and the rxSubstatus is CobsDecodeFail
    EXPECT_EQ(stateMachine->getRxStatus(), Device::UartStateMachine::RxStatus::Finished);
    EXPECT_EQ(stateMachine->getRxSubstatus(), Device::UartStateMachine::RxSubstatus::CobsDecodeFail);
}

/**
 * @test TransitionToFaultOnBufferOverflow
 * @brief Verifies that the state machine transitions to the `Fault` state when the buffer overflows (i.e., `rxWriteIndex` exceeds `MaxRxSize`).
 *
 * @scenario
 * 1. The state machine is opened with a baud rate.
 * 2. The `rxBuffer` is set up for receiving data.
 * 3. During the `Receiving` state, more data is received than the buffer can handle, causing the `rxWriteIndex` to exceed `MaxRxSize`.
 * 4. The state machine should transition to the `Fault` state with `Overflow` as the `rxSubstatus`.
 * 5. We expect the state to transition to `Fault`, indicating a buffer overflow error.
 */

TEST_F(UartStateMachineTest, TransitionToFaultOnBufferOverflow)
{
    const unsigned long baud = 115200;

    // Expect the serial interface to begin with the correct baud rate
    EXPECT_CALL(mockSerial, begin(baud)).Times(1);

    stateMachine->open(baud);

    // Set the rxBuffer for the state machine
    std::array<std::uint8_t, Device::UartStateMachine::MaxRxSize> rxBuffer;
    stateMachine->setRxBuffer(rxBuffer);

    // Simulate receiving data that will cause the buffer to overflow
    EXPECT_CALL(mockSerial, available()).WillOnce(testing::Return(Device::UartStateMachine::MaxRxSize + 555));
    // Simulate reading 0 once and then 1 for the subsequent calls
    EXPECT_CALL(mockSerial, read())
        .WillOnce(testing::Return(0))        // First byte (start of frame)
        .WillRepeatedly(testing::Return(1)); // Next bytes (data causing overflow)

    // Call tick to process the data
    stateMachine->tick();

    // Verify that the state machine transitions to the Fault state due to overflow
    EXPECT_EQ(stateMachine->getState(), Device::UartStateMachine::StateMachineState::Fault);

    // Verify that the rxStatus is Finished, and the rxSubstatus is Overflow
    EXPECT_EQ(stateMachine->getRxStatus(), Device::UartStateMachine::RxStatus::Finished);
    EXPECT_EQ(stateMachine->getRxSubstatus(), Device::UartStateMachine::RxSubstatus::Overflow);
}
#endif
TEST_F(UartStateMachineTest, DoDecodingWhenCobsDecodeSucceeds)
{
    const unsigned long baud = 115200;

    // Expect the serial interface to begin with the correct baud rate
    EXPECT_CALL(mockSerial, begin(baud)).Times(1);
    stateMachine->open(baud);

    // Set the rxBuffer for the state machine
    std::array<std::uint8_t, Device::UartStateMachine::MaxRxSize> rxBuffer{};
    stateMachine->setRxBuffer(rxBuffer);

    // Define an array to simulate received data (COBS delimiter and data bytes)
    std::array<int, 7> mockData = {6, 10, 11, 12, 5, 85, 0}; // First and last byte are COBS delimiters, middle byte is data

    // Simulate available bytes: the length of the array will be returned by available()
    EXPECT_CALL(mockSerial, available()).WillOnce(testing::Return(mockData.size()));

    // Stub read() to return each byte in sequence
    testing::Sequence seq;
    for (auto byte : mockData)
    {
        EXPECT_CALL(mockSerial, read())
            .InSequence(seq)
            .WillOnce(testing::Return(byte));
    }

    // First tick - should read all 7 bytes
    stateMachine->tick();

    // Verify we're in Decoding state
    EXPECT_EQ(stateMachine->getState(), Device::UartStateMachine::StateMachineState::Decoding);

    // Second tick - should process the packet
    // EXPECT_CALL(mockSerial, available()).WillOnce(testing::Return(0));
    stateMachine->tick();

    // Verify successful processing
    EXPECT_EQ(stateMachine->getState(), Device::UartStateMachine::StateMachineState::Verifying);
    EXPECT_EQ(stateMachine->getRxStatus(), Device::UartStateMachine::RxStatus::Active);
    EXPECT_EQ(stateMachine->getRxSubstatus(), Device::UartStateMachine::RxSubstatus::Ok);
}