#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "Device/Interface/IMeasurementSource.hpp"
#include "Device/Interface/IMeasurementRecorder.hpp"

#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

// Mock classes - must match actual interface signatures
class MockMeasurementSource : public Device::IMeasurementSource
{
public:
    // Constructor - base class now has default constructor
    MockMeasurementSource() = default;

    MOCK_METHOD(bool, initialize, (), (override));
    MOCK_METHOD(bool, start, (), (override));
    MOCK_METHOD(bool, stop, (), (override));
    MOCK_METHOD(bool, isMeasurementAvailable, (), (override));
    MOCK_METHOD(Device::MeasurementType, getMeasurement, (), (override));
};

class MockMeasurementRecorder : public Device::IMeasurementRecorder
{
public:
    MOCK_METHOD(bool, initialize, (), (override));
    MOCK_METHOD(bool, start, (), (override));
    MOCK_METHOD(bool, stop, (), (override));
    MOCK_METHOD(bool, onInitialize, (), (override));
    MOCK_METHOD(bool, onStart, (), (override));
    MOCK_METHOD(bool, onStop, (), (override));
    MOCK_METHOD(bool, onReset, (), (override));
    // Note: notify returns bool and takes non-const reference
    MOCK_METHOD(bool, notify, (Device::MeasurementType &), (override));
};

// Test fixture
class MeasurementCoordinatorTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Create mock objects
        mockSource1 = std::make_unique<testing::NiceMock<MockMeasurementSource>>();
        mockSource2 = std::make_unique<testing::NiceMock<MockMeasurementSource>>();
        mockRecorder1 = std::make_unique<testing::NiceMock<MockMeasurementRecorder>>();
        mockRecorder2 = std::make_unique<testing::NiceMock<MockMeasurementRecorder>>();

        // Set default return values for methods that return bool
        ON_CALL(*mockSource1, start()).WillByDefault(testing::Return(true));
        ON_CALL(*mockSource2, start()).WillByDefault(testing::Return(true));
        ON_CALL(*mockRecorder1, start()).WillByDefault(testing::Return(true));
        ON_CALL(*mockRecorder2, start()).WillByDefault(testing::Return(true));

        ON_CALL(*mockSource1, stop()).WillByDefault(testing::Return(true));
        ON_CALL(*mockSource2, stop()).WillByDefault(testing::Return(true));
        ON_CALL(*mockRecorder1, stop()).WillByDefault(testing::Return(true));
        ON_CALL(*mockRecorder2, stop()).WillByDefault(testing::Return(true));

        ON_CALL(*mockRecorder1, notify(testing::_)).WillByDefault(testing::Return(true));
        ON_CALL(*mockRecorder2, notify(testing::_)).WillByDefault(testing::Return(true));

        // Create reference arrays using make_unique with aggregate initialization
        sources = std::make_unique<std::array<std::reference_wrapper<Device::IMeasurementSource>, 2>>(
            std::array<std::reference_wrapper<Device::IMeasurementSource>, 2>{{std::ref(*mockSource1),
                                                                               std::ref(*mockSource2)}});

        recorders = std::make_unique<std::array<std::reference_wrapper<Device::IMeasurementRecorder>, 2>>(
            std::array<std::reference_wrapper<Device::IMeasurementRecorder>, 2>{{std::ref(*mockRecorder1),
                                                                                 std::ref(*mockRecorder2)}});

        // Create coordinator
        coordinator = std::make_unique<BusinessLogic::MeasurementCoordinator<2, 2>>(*sources, *recorders);
    }

    void TearDown() override
    {
        coordinator.reset();
        sources.reset();
        recorders.reset();
        mockSource1.reset();
        mockSource2.reset();
        mockRecorder1.reset();
        mockRecorder2.reset();
    }

    MockMeasurementSource *getMockSource1() { return mockSource1.get(); }
    MockMeasurementSource *getMockSource2() { return mockSource2.get(); }
    MockMeasurementRecorder *getMockRecorder1() { return mockRecorder1.get(); }
    MockMeasurementRecorder *getMockRecorder2() { return mockRecorder2.get(); }
    BusinessLogic::MeasurementCoordinator<2, 2> *getCoordinator() { return coordinator.get(); }

private:
    std::unique_ptr<MockMeasurementSource> mockSource1;
    std::unique_ptr<MockMeasurementSource> mockSource2;
    std::unique_ptr<MockMeasurementRecorder> mockRecorder1;
    std::unique_ptr<MockMeasurementRecorder> mockRecorder2;

    std::unique_ptr<std::array<std::reference_wrapper<Device::IMeasurementSource>, 2>> sources;
    std::unique_ptr<std::array<std::reference_wrapper<Device::IMeasurementRecorder>, 2>> recorders;

    std::unique_ptr<BusinessLogic::MeasurementCoordinator<2, 2>> coordinator;
};

// ==================== Initialize Tests ====================

TEST_F(MeasurementCoordinatorTest, Initialize_AllSourcesSucceed_ReturnsTrue)
{
    // Arrange
    EXPECT_CALL(*getMockSource1(), initialize()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), initialize()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), initialize()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), initialize()).WillOnce(testing::Return(true));

    // Act
    const bool result = getCoordinator()->initialize();

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, Initialize_SourceFails_ReturnsFalse)
{
    // Arrange
    EXPECT_CALL(*getMockSource1(), initialize()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockSource2(), initialize()).Times(0);

    // Act
    const bool result = getCoordinator()->initialize();

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(MeasurementCoordinatorTest, Initialize_SourcesSucceedRecorderFails_ReturnsFalse)
{
    // Arrange
    EXPECT_CALL(*getMockSource1(), initialize()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), initialize()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), initialize()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockRecorder2(), initialize()).Times(0);

    // Act
    const bool result = getCoordinator()->initialize();

    // Assert
    EXPECT_FALSE(result);
}

// ==================== Start Tests ====================

TEST_F(MeasurementCoordinatorTest, Start_AllSucceed_ReturnsTrue)
{
    // Arrange
    EXPECT_CALL(*getMockSource1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), start()).WillOnce(testing::Return(true));

    // Act
    const bool result = getCoordinator()->start();

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, Start_SourceFails_ReturnsFalse)
{
    // Arrange
    EXPECT_CALL(*getMockSource1(), start()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockSource2(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), start()).WillOnce(testing::Return(true));

    // Act
    const bool result = getCoordinator()->start();

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(MeasurementCoordinatorTest, Start_RecorderFails_ReturnsFalse)
{
    // Arrange
    EXPECT_CALL(*getMockSource1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), start()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockRecorder2(), start()).WillOnce(testing::Return(true));

    // Act
    const bool result = getCoordinator()->start();

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(MeasurementCoordinatorTest, Start_MultipleFailures_ReturnsFalse)
{
    // Arrange
    EXPECT_CALL(*getMockSource1(), start()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockSource2(), start()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockRecorder1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), start()).WillOnce(testing::Return(true));

    // Act
    const bool result = getCoordinator()->start();

    // Assert
    EXPECT_FALSE(result);
}

// ==================== Stop Tests ====================

TEST_F(MeasurementCoordinatorTest, Stop_AllSucceed_ReturnsTrue)
{
    // Arrange
    EXPECT_CALL(*getMockSource1(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), stop()).WillOnce(testing::Return(true));

    // Act
    const bool result = getCoordinator()->stop();

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, Stop_SourceFails_ReturnsFalse)
{
    // Arrange
    EXPECT_CALL(*getMockSource1(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), stop()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockRecorder1(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), stop()).WillOnce(testing::Return(true));

    // Act
    const bool result = getCoordinator()->stop();

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(MeasurementCoordinatorTest, Stop_RecorderFails_ReturnsFalse)
{
    // Arrange
    EXPECT_CALL(*getMockSource1(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), stop()).WillOnce(testing::Return(false));

    // Act
    const bool result = getCoordinator()->stop();

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(MeasurementCoordinatorTest, Stop_MultipleFailures_ReturnsFalse)
{
    // Arrange
    EXPECT_CALL(*getMockSource1(), stop()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockSource2(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), stop()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockRecorder2(), stop()).WillOnce(testing::Return(true));

    // Act
    const bool result = getCoordinator()->stop();

    // Assert
    EXPECT_FALSE(result);
}

// ==================== Tick Tests ====================

TEST_F(MeasurementCoordinatorTest, Tick_NoMeasurementsAvailable_NoRecordersNotified)
{
    // Arrange
    EXPECT_CALL(*getMockSource1(), isMeasurementAvailable()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockSource2(), isMeasurementAvailable()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockRecorder1(), notify(testing::_)).Times(0);
    EXPECT_CALL(*getMockRecorder2(), notify(testing::_)).Times(0);

    // Act
    const bool result = getCoordinator()->tick();

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, Tick_OneMeasurementAvailable_AllRecordersNotified)
{
    // Arrange
    const Device::MeasurementType measurement{
        std::uint32_t{100U},
        Device::MeasurementDeviceId::PULSE_COUNTER_1};

    EXPECT_CALL(*getMockSource1(), isMeasurementAvailable()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource1(), getMeasurement()).WillOnce(testing::Return(measurement));
    EXPECT_CALL(*getMockSource2(), isMeasurementAvailable()).WillOnce(testing::Return(false));

    EXPECT_CALL(*getMockRecorder1(), notify(testing::_)).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), notify(testing::_)).WillOnce(testing::Return(true));

    // Act
    const bool result = getCoordinator()->tick();

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, Tick_BothMeasurementsAvailable_AllRecordersNotifiedTwice)
{
    // Arrange
    const Device::MeasurementType measurement1{
        std::uint32_t{100U},
        Device::MeasurementDeviceId::PULSE_COUNTER_1};
    const Device::MeasurementType measurement2{
        std::uint32_t{200U},
        Device::MeasurementDeviceId::PULSE_COUNTER_2};

    EXPECT_CALL(*getMockSource1(), isMeasurementAvailable()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource1(), getMeasurement()).WillOnce(testing::Return(measurement1));
    EXPECT_CALL(*getMockSource2(), isMeasurementAvailable()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), getMeasurement()).WillOnce(testing::Return(measurement2));

    // Each recorder should be notified twice (once per measurement)
    EXPECT_CALL(*getMockRecorder1(), notify(testing::_)).Times(2).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), notify(testing::_)).Times(2).WillRepeatedly(testing::Return(true));

    // Act
    const bool result = getCoordinator()->tick();

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, MultipleTicks_HandlesMultipleCycles)
{
    // Arrange
    constexpr std::uint32_t TEST_MEASUREMENT_VALUE = 100U;
    const Device::MeasurementType measurement{
        std::uint32_t{TEST_MEASUREMENT_VALUE},
        Device::MeasurementDeviceId::PULSE_COUNTER_1};

    EXPECT_CALL(*getMockSource1(), isMeasurementAvailable())
        .WillOnce(testing::Return(true))
        .WillOnce(testing::Return(false))
        .WillOnce(testing::Return(true));

    EXPECT_CALL(*getMockSource1(), getMeasurement())
        .Times(2)
        .WillRepeatedly(testing::Return(measurement));

    EXPECT_CALL(*getMockSource2(), isMeasurementAvailable())
        .Times(3)
        .WillRepeatedly(testing::Return(false));

    // Set up expectations for notify calls - 2 measurements mean 2 notifications per recorder
    EXPECT_CALL(*getMockRecorder1(), notify(testing::_))
        .Times(2)
        .WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), notify(testing::_))
        .Times(2)
        .WillRepeatedly(testing::Return(true));

    // Act & Assert
    EXPECT_TRUE(getCoordinator()->tick());
    EXPECT_TRUE(getCoordinator()->tick());
    EXPECT_TRUE(getCoordinator()->tick());
}

// ==================== Test with Many Sources/Recorders ====================

class MeasurementCoordinatorLargeTest : public ::testing::Test
{
protected:
    static constexpr std::size_t NUM_SOURCES = 5U;
    static constexpr std::size_t NUM_RECORDERS = 3U;

    void SetUp() override
    {
        for (std::size_t i = 0U; i < NUM_SOURCES; ++i)
        {
            mockSources.push_back(std::make_unique<testing::NiceMock<MockMeasurementSource>>());
        }

        for (std::size_t i = 0U; i < NUM_RECORDERS; ++i)
        {
            mockRecorders.push_back(std::make_unique<testing::NiceMock<MockMeasurementRecorder>>());
        }

        // Create arrays using make_unique with aggregate initialization
        sources = std::make_unique<std::array<std::reference_wrapper<Device::IMeasurementSource>, NUM_SOURCES>>(
            std::array<std::reference_wrapper<Device::IMeasurementSource>, NUM_SOURCES>{{std::ref(*mockSources[0]),
                                                                                         std::ref(*mockSources[1]),
                                                                                         std::ref(*mockSources[2]),
                                                                                         std::ref(*mockSources[3]),
                                                                                         std::ref(*mockSources[4])}});

        recorders = std::make_unique<std::array<std::reference_wrapper<Device::IMeasurementRecorder>, NUM_RECORDERS>>(
            std::array<std::reference_wrapper<Device::IMeasurementRecorder>, NUM_RECORDERS>{{std::ref(*mockRecorders[0]),
                                                                                             std::ref(*mockRecorders[1]),
                                                                                             std::ref(*mockRecorders[2])}});

        coordinator = std::make_unique<BusinessLogic::MeasurementCoordinator<NUM_SOURCES, NUM_RECORDERS>>(*sources, *recorders);
    }

    std::vector<std::unique_ptr<MockMeasurementSource>> &getMockSources() { return mockSources; }
    std::vector<std::unique_ptr<MockMeasurementRecorder>> &getMockRecorders() { return mockRecorders; }
    BusinessLogic::MeasurementCoordinator<NUM_SOURCES, NUM_RECORDERS> *getCoordinator() { return coordinator.get(); }

private:
    std::vector<std::unique_ptr<MockMeasurementSource>> mockSources;
    std::vector<std::unique_ptr<MockMeasurementRecorder>> mockRecorders;
    std::unique_ptr<std::array<std::reference_wrapper<Device::IMeasurementSource>, NUM_SOURCES>> sources;
    std::unique_ptr<std::array<std::reference_wrapper<Device::IMeasurementRecorder>, NUM_RECORDERS>> recorders;
    std::unique_ptr<BusinessLogic::MeasurementCoordinator<NUM_SOURCES, NUM_RECORDERS>> coordinator;
};
