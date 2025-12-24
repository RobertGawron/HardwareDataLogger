#include "BusinessLogic/Interface/IMeasurementDataStore.hpp"
#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "Device/Interface/IMeasurementRecorder.hpp"
#include "Device/Interface/IMeasurementSource.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// --- Mocks ---

class MockMeasurementSource : public Device::IMeasurementSource
{
public:
    explicit MockMeasurementSource(Device::MeasurementDeviceId id) : IMeasurementSource(id) {}

    MOCK_METHOD(bool, initialize, (), (override));
    MOCK_METHOD(bool, start, (), (override));
    MOCK_METHOD(bool, isMeasurementAvailable, (), (override));
    MOCK_METHOD(Device::MeasurementType, getMeasurement, (), (override));
    MOCK_METHOD(bool, stop, (), (override));
};

class MockMeasurementDataStore : public BusinessLogic::IMeasurementDataStore
{
public:
    MOCK_METHOD(bool, notifyObservers, (Device::MeasurementType measurement), (override));
    MOCK_METHOD(bool, addObserver, (Device::IMeasurementRecorder &), (override));
    MOCK_METHOD(bool, removeObserver, (Device::IMeasurementRecorder &), (override));
    MOCK_METHOD(bool, initialize, (), (override));
    MOCK_METHOD(bool, start, (), (override));
};

// --- Test Fixture ---

class MeasurementCoordinatorTest : public ::testing::Test
{
private:
    // Private fields
    std::unique_ptr<BusinessLogic::MeasurementCoordinator> coordinator;
    MockMeasurementDataStore mockStorage;
    MockMeasurementSource mockSource1{Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1};
    MockMeasurementSource mockSource2{Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_2};

protected:
    void SetUp() override
    {
        coordinator = std::make_unique<BusinessLogic::MeasurementCoordinator>(mockStorage);
    }

public:
    // Public Getters
    BusinessLogic::MeasurementCoordinator &getCoordinator() { return *coordinator; }
    MockMeasurementDataStore &getMockStorage() { return mockStorage; }
    MockMeasurementSource &getMockSource1() { return mockSource1; }
    MockMeasurementSource &getMockSource2() { return mockSource2; }
};

// --- Test Cases ---

TEST_F(MeasurementCoordinatorTest, InitializeShouldCallInitializeAndStartOnAllObservers)
{
    EXPECT_CALL(getMockSource1(), initialize()).WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockSource1(), start()).WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockSource2(), initialize()).WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockSource2(), start()).WillOnce(::testing::Return(true));

    getCoordinator().addObserver(getMockSource1());
    getCoordinator().addObserver(getMockSource2());

    EXPECT_TRUE(getCoordinator().initialize());
}

TEST_F(MeasurementCoordinatorTest, TickShouldUpdateMeasurements)
{
    // Arrange
    EXPECT_CALL(getMockSource1(), isMeasurementAvailable()).WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockSource1(), getMeasurement()).WillOnce(::testing::Return(Device::MeasurementType{}));
    EXPECT_CALL(getMockStorage(), notifyObservers(::testing::_))
        .Times(1)
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(getMockSource2(), isMeasurementAvailable()).WillOnce(::testing::Return(false));
    EXPECT_CALL(getMockSource2(), getMeasurement()).Times(0);

    // Act
    getCoordinator().addObserver(getMockSource1());
    getCoordinator().addObserver(getMockSource2());

    // Assert
    EXPECT_TRUE(getCoordinator().tick());
}

TEST_F(MeasurementCoordinatorTest, TickSucceedsWithNoObservers)
{
    EXPECT_TRUE(getCoordinator().tick());
}

TEST_F(MeasurementCoordinatorTest, AddObserverShouldAddObserversSuccessfully)
{
    EXPECT_TRUE(getCoordinator().addObserver(getMockSource1()));
    EXPECT_TRUE(getCoordinator().addObserver(getMockSource2()));
}

TEST_F(MeasurementCoordinatorTest, RemoveObserverShouldRemoveObserversSuccessfully)
{
    getCoordinator().addObserver(getMockSource1());
    EXPECT_TRUE(getCoordinator().removeObserver(getMockSource1()));
}

TEST_F(MeasurementCoordinatorTest, RemoveObserverFailsForNonExistentObserver)
{
    EXPECT_FALSE(getCoordinator().removeObserver(getMockSource1()));
}

TEST_F(MeasurementCoordinatorTest, InitializeFailsIfAnyObserverFailsToInitialize)
{
    EXPECT_CALL(getMockSource1(), initialize()).WillOnce(::testing::Return(false));
    EXPECT_CALL(getMockSource1(), start()).Times(0);
    EXPECT_CALL(getMockSource2(), initialize()).Times(0);

    getCoordinator().addObserver(getMockSource1());
    getCoordinator().addObserver(getMockSource2());

    EXPECT_FALSE(getCoordinator().initialize());
}
