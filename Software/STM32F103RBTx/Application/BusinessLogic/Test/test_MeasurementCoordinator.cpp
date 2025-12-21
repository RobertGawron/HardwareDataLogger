#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "BusinessLogic/Inc/MeasurementDataStore.hpp"
#include "Device/Interfaces/IMeasurementSource.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <variant>

// Mock class for Device::IMeasurementSource
class MockMeasurementSource : public Device::IMeasurementSource
{
public:
    explicit MockMeasurementSource(Device::MeasurementDeviceId id)
        : IMeasurementSource(id) {}

    MOCK_METHOD(bool, initialize, (), (override));
    MOCK_METHOD(bool, start, (), (override));
    MOCK_METHOD(bool, isMeasurementAvailable, (), (override));
    MOCK_METHOD(Device::MeasurementType, getMeasurement, (), (override));
    MOCK_METHOD(bool, stop, (), (override));
};

// Mock class for BusinessLogic::MeasurementDataStore
class MockMeasurementDataStore : public BusinessLogic::IMeasurementDataStore
{
public:
    MOCK_METHOD(bool, notifyObservers, (Device::MeasurementType measurement), (override));
    MOCK_METHOD(bool, addObserver, (Device::IMeasurementRecorder &), (override));
    MOCK_METHOD(bool, removeObserver, (Device::IMeasurementRecorder &), (override));
    MOCK_METHOD(bool, initialize, (), (override));
    MOCK_METHOD(bool, start, (), (override));
};

// Test Fixture for MeasurementCoordinator
class MeasurementCoordinatorTest : public ::testing::Test
{
protected:
    MockMeasurementDataStore mockStorage;
    MockMeasurementSource mockSource1{Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1};
    MockMeasurementSource mockSource2{Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_2};
    BusinessLogic::MeasurementCoordinator *coordinator;

    void SetUp() override
    {
        coordinator = new BusinessLogic::MeasurementCoordinator(mockStorage);
    }

    void TearDown() override
    {
        delete coordinator;
    }
};

// Test initialize() method
TEST_F(MeasurementCoordinatorTest, InitializeShouldCallInitializeAndStartOnAllObservers)
{
    EXPECT_CALL(mockSource1, initialize()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockSource1, start()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockSource2, initialize()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockSource2, start()).WillOnce(::testing::Return(true));

    coordinator->addObserver(mockSource1);
    coordinator->addObserver(mockSource2);

    EXPECT_TRUE(coordinator->initialize());
}

// Test tick() method
TEST_F(MeasurementCoordinatorTest, TickShouldUpdateMeasurements)
{
    EXPECT_CALL(mockSource1, isMeasurementAvailable()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockSource1, getMeasurement()).WillOnce(::testing::Return(Device::MeasurementType{}));
    EXPECT_CALL(mockStorage, notifyObservers(::testing::_)).Times(1);

    EXPECT_CALL(mockSource2, isMeasurementAvailable()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockSource2, getMeasurement()).Times(0);

    coordinator->addObserver(mockSource1);
    coordinator->addObserver(mockSource2);

    EXPECT_TRUE(coordinator->tick());
}

// Test tick() when no observers are present
TEST_F(MeasurementCoordinatorTest, TickSucceedsWithNoObservers)
{
    EXPECT_TRUE(coordinator->tick());
}

// Test addObserver() method
TEST_F(MeasurementCoordinatorTest, AddObserverShouldAddObserversSuccessfully)
{
    EXPECT_TRUE(coordinator->addObserver(mockSource1));
    EXPECT_TRUE(coordinator->addObserver(mockSource2));
}

// Test removeObserver() method
TEST_F(MeasurementCoordinatorTest, RemoveObserverShouldRemoveObserversSuccessfully)
{
    coordinator->addObserver(mockSource1);
    EXPECT_TRUE(coordinator->removeObserver(mockSource1));
}

// Test removeObserver() with non-existent observer
TEST_F(MeasurementCoordinatorTest, RemoveObserverFailsForNonExistentObserver)
{
    EXPECT_FALSE(coordinator->removeObserver(mockSource1));
}

// Test initialize() failure when one observer fails to initialize
TEST_F(MeasurementCoordinatorTest, InitializeFailsIfAnyObserverFailsToInitialize)
{
    EXPECT_CALL(mockSource1, initialize()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockSource1, start()).Times(0);
    EXPECT_CALL(mockSource2, initialize()).Times(0);
    EXPECT_CALL(mockSource2, start()).Times(0);

    coordinator->addObserver(mockSource1);
    coordinator->addObserver(mockSource2);

    EXPECT_FALSE(coordinator->initialize());
}
