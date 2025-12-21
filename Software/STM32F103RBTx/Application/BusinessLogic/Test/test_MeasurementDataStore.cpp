#include "BusinessLogic/Inc/MeasurementDataStore.hpp"
#include "Device/Interfaces/IMeasurementRecorder.hpp"
#include "Driver/Inc/UartExchangeStatus.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mock class for Device::IMeasurementRecorder
class MockMeasurementRecorder : public Device::IMeasurementRecorder
{
public:
    MOCK_METHOD(bool, initialize, (), (override));
    MOCK_METHOD(bool, start, (), (override));
    MOCK_METHOD(bool, notify, (Device::MeasurementType & measurement), (override));
    MOCK_METHOD(bool, onInitialize, (), (override));
    MOCK_METHOD(bool, onStart, (), (override));
    MOCK_METHOD(bool, onStop, (), (override));
    MOCK_METHOD(bool, onReset, (), (override));
    MOCK_METHOD(bool, flush, (), (override));
};

// Test Fixture for BusinessLogic::MeasurementDataStore
class MeasurementDataStoreTest : public ::testing::Test
{
protected:
    BusinessLogic::MeasurementDataStore *dataStore;
    MockMeasurementRecorder mockRecorder1;
    MockMeasurementRecorder mockRecorder2;

    void SetUp() override
    {
        dataStore = new BusinessLogic::MeasurementDataStore();
    }

    void TearDown() override
    {
        delete dataStore;
    }
};

// Test initialize() method
TEST_F(MeasurementDataStoreTest, InitializeShouldCallInitializeOnAllObservers)
{
    EXPECT_CALL(mockRecorder1, initialize()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockRecorder2, initialize()).WillOnce(::testing::Return(true));

    dataStore->addObserver(mockRecorder1);
    dataStore->addObserver(mockRecorder2);

    EXPECT_TRUE(dataStore->initialize());
}

// Test start() method
TEST_F(MeasurementDataStoreTest, StartShouldCallStartOnAllObservers)
{
    EXPECT_CALL(mockRecorder1, start()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockRecorder2, start()).WillOnce(::testing::Return(true));

    dataStore->addObserver(mockRecorder1);
    dataStore->addObserver(mockRecorder2);

    EXPECT_TRUE(dataStore->start());
}

// Test addObserver() method
TEST_F(MeasurementDataStoreTest, AddObserverShouldAddObserverSuccessfully)
{
    EXPECT_TRUE(dataStore->addObserver(mockRecorder1));
    EXPECT_TRUE(dataStore->addObserver(mockRecorder2));
}

// Test removeObserver() method
TEST_F(MeasurementDataStoreTest, RemoveObserverShouldRemoveObserverSuccessfully)
{
    dataStore->addObserver(mockRecorder1);
    EXPECT_TRUE(dataStore->removeObserver(mockRecorder1));
}
/*
TEST_F(MeasurementDataStoreTest, NotifyObserversShouldCallNotifyOnAllObserversWithCorrectValue)
{
    Device::MeasurementType mockMeasurement{42u}; // The expected measurement value

    // Check that notify is called with the exact value 42u
    EXPECT_CALL(mockRecorder1, notify(::testing::_))
        .Times(1)
        .WillOnce(::testing::Invoke([](Device::MeasurementType &measurement) -> bool
                                    {
                                        EXPECT_TRUE(std::holds_alternative<uint32_t>(measurement));
                                        EXPECT_EQ(std::get<uint32_t>(measurement), 42u);
                                        return true; // Must return bool
                                    }));

    EXPECT_CALL(mockRecorder2, notify(::testing::_))
        .Times(1)
        .WillOnce(::testing::Invoke([](Device::MeasurementType &measurement) -> bool
                                    {
                                        EXPECT_TRUE(std::holds_alternative<uint32_t>(measurement));
                                        EXPECT_EQ(std::get<uint32_t>(measurement), 42u);
                                        return true; // Must return bool
                                    }));

    dataStore->addObserver(mockRecorder1);
    dataStore->addObserver(mockRecorder2);

    dataStore->notifyObservers(mockMeasurement);
}
*/