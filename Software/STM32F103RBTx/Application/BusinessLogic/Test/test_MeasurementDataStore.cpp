#include "BusinessLogic/Inc/MeasurementDataStore.hpp"
#include "Device/Interfaces/IMeasurementRecorder.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// --- Mocks ---

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

// --- Test Fixture ---

class MeasurementDataStoreTest : public ::testing::Test
{
private:
    // All fields are now private
    std::unique_ptr<BusinessLogic::MeasurementDataStore> dataStore;
    MockMeasurementRecorder mockRecorder1;
    MockMeasurementRecorder mockRecorder2;

protected:
    void SetUp() override
    {
        dataStore = std::make_unique<BusinessLogic::MeasurementDataStore>();
    }

public:
    // Public getters to access private members
    BusinessLogic::MeasurementDataStore &getDataStore() { return *dataStore; }
    MockMeasurementRecorder &getMockRecorder1() { return mockRecorder1; }
    MockMeasurementRecorder &getMockRecorder2() { return mockRecorder2; }
};

// --- Test Cases ---

TEST_F(MeasurementDataStoreTest, InitializeShouldCallInitializeOnAllObservers)
{
    EXPECT_CALL(getMockRecorder1(), initialize()).WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockRecorder2(), initialize()).WillOnce(::testing::Return(true));

    getDataStore().addObserver(getMockRecorder1());
    getDataStore().addObserver(getMockRecorder2());

    EXPECT_TRUE(getDataStore().initialize());
}

TEST_F(MeasurementDataStoreTest, StartShouldCallStartOnAllObservers)
{
    EXPECT_CALL(getMockRecorder1(), start()).WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockRecorder2(), start()).WillOnce(::testing::Return(true));

    getDataStore().addObserver(getMockRecorder1());
    getDataStore().addObserver(getMockRecorder2());

    EXPECT_TRUE(getDataStore().start());
}

TEST_F(MeasurementDataStoreTest, AddObserverShouldAddObserverSuccessfully)
{
    EXPECT_TRUE(getDataStore().addObserver(getMockRecorder1()));
    EXPECT_TRUE(getDataStore().addObserver(getMockRecorder2()));
}

TEST_F(MeasurementDataStoreTest, RemoveObserverShouldRemoveObserverSuccessfully)
{
    getDataStore().addObserver(getMockRecorder1());
    EXPECT_TRUE(getDataStore().removeObserver(getMockRecorder1()));
}
