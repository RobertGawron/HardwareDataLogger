#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>
#include <variant>

import BusinessLogic.MeasurementCoordinator;
import Device;

// Mock classes - must match actual interface signatures including noexcept
class MockMeasurementSource
{
public:
    MockMeasurementSource() = default;

    MOCK_METHOD(bool, init, (), (noexcept));
    MOCK_METHOD(bool, start, (), (noexcept));
    MOCK_METHOD(bool, stop, (), (noexcept));
    MOCK_METHOD(bool, isMeasurementAvailable, (), (const, noexcept));
    MOCK_METHOD(Device::MeasurementType, getMeasurement, (), (noexcept));
};

class MockMeasurementRecorder
{
public:
    MOCK_METHOD(bool, init, (), (noexcept));
    MOCK_METHOD(bool, start, (), (noexcept));
    MOCK_METHOD(bool, stop, (), (noexcept));
    MOCK_METHOD(bool, notify, (const Device::MeasurementType &), (noexcept));
};

// Test fixture
class MeasurementCoordinatorTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        mockSource1 = std::make_unique<testing::NiceMock<MockMeasurementSource>>();
        mockSource2 = std::make_unique<testing::NiceMock<MockMeasurementSource>>();
        mockRecorder1 = std::make_unique<testing::NiceMock<MockMeasurementRecorder>>();
        mockRecorder2 = std::make_unique<testing::NiceMock<MockMeasurementRecorder>>();

        sources = std::make_unique<std::array<Device::SourceVariant, 2>>(
            std::array<Device::SourceVariant, 2>{{std::ref(*mockSource1),
                                                  std::ref(*mockSource2)}});

        recorders = std::make_unique<std::array<Device::RecorderVariant, 2>>(
            std::array<Device::RecorderVariant, 2>{{std::ref(*mockRecorder1),
                                                    std::ref(*mockRecorder2)}});

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

    auto getMockSource1() -> MockMeasurementSource * { return mockSource1.get(); }
    auto getMockSource2() -> MockMeasurementSource * { return mockSource2.get(); }
    auto getMockRecorder1() -> MockMeasurementRecorder * { return mockRecorder1.get(); }
    auto getMockRecorder2() -> MockMeasurementRecorder * { return mockRecorder2.get(); }
    auto getCoordinator() -> BusinessLogic::MeasurementCoordinator<2, 2> * { return coordinator.get(); }

private:
    std::unique_ptr<MockMeasurementSource> mockSource1;
    std::unique_ptr<MockMeasurementSource> mockSource2;
    std::unique_ptr<MockMeasurementRecorder> mockRecorder1;
    std::unique_ptr<MockMeasurementRecorder> mockRecorder2;

    std::unique_ptr<std::array<Device::SourceVariant, 2>> sources;
    std::unique_ptr<std::array<Device::RecorderVariant, 2>> recorders;

    std::unique_ptr<BusinessLogic::MeasurementCoordinator<2, 2>> coordinator;
};

// ==================== init Tests ====================

TEST_F(MeasurementCoordinatorTest, init_AllSourcesSucceed_ReturnsTrue)
{
    EXPECT_CALL(*getMockSource1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), init()).WillOnce(testing::Return(true));

    const bool result = getCoordinator()->onInit();

    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, init_SourceFails_ReturnsFalse)
{
    EXPECT_CALL(*getMockSource1(), init()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockSource2(), init()).Times(0);

    const bool result = getCoordinator()->onInit();

    EXPECT_FALSE(result);
}

TEST_F(MeasurementCoordinatorTest, init_SourcesSucceedRecorderFails_ReturnsFalse)
{
    EXPECT_CALL(*getMockSource1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), init()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockRecorder2(), init()).Times(0);

    const bool result = getCoordinator()->onInit();

    EXPECT_FALSE(result);
}

// ==================== Start Tests ====================

TEST_F(MeasurementCoordinatorTest, Start_AllSucceed_ReturnsTrue)
{
    // Initialize first (required for state machine)
    EXPECT_CALL(*getMockSource1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), init()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->onInit());

    // Now test start
    EXPECT_CALL(*getMockSource1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), start()).WillOnce(testing::Return(true));

    const bool result = getCoordinator()->onStart();

    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, Start_SourceFails_ReturnsFalse)
{
    // Initialize first
    EXPECT_CALL(*getMockSource1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), init()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->onInit());

    // Test start with source failure
    EXPECT_CALL(*getMockSource1(), start()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockSource2(), start()).Times(0);
    EXPECT_CALL(*getMockRecorder1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), start()).WillOnce(testing::Return(true));

    const bool result = getCoordinator()->onStart();

    EXPECT_FALSE(result);
}

TEST_F(MeasurementCoordinatorTest, Start_RecorderFails_ReturnsFalse)
{
    // Initialize first
    EXPECT_CALL(*getMockSource1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), init()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->onInit());

    // Test start with recorder failure
    EXPECT_CALL(*getMockSource1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), start()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockRecorder2(), start()).Times(0);

    const bool result = getCoordinator()->onStart();

    EXPECT_FALSE(result);
}

// ==================== Stop Tests ====================

TEST_F(MeasurementCoordinatorTest, Stop_AllSucceed_ReturnsTrue)
{
    // Initialize and start first (required for state machine)
    EXPECT_CALL(*getMockSource1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), init()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->onInit());

    EXPECT_CALL(*getMockSource1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), start()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->onStart());

    // Now test stop
    EXPECT_CALL(*getMockSource1(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), stop()).WillOnce(testing::Return(true));

    const bool result = getCoordinator()->onStop();

    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, Stop_SourceFails_ReturnsFalse)
{
    // Initialize and start first
    EXPECT_CALL(*getMockSource1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), init()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->onInit());

    EXPECT_CALL(*getMockSource1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), start()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->onStart());

    // Test stop with source failure
    EXPECT_CALL(*getMockSource1(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), stop()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockRecorder1(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), stop()).WillOnce(testing::Return(true));

    const bool result = getCoordinator()->onStop();

    EXPECT_FALSE(result);
}

TEST_F(MeasurementCoordinatorTest, Stop_RecorderFails_ReturnsFalse)
{
    // Initialize and start first
    EXPECT_CALL(*getMockSource1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), init()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), init()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->onInit());

    EXPECT_CALL(*getMockSource1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), start()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), start()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->onStart());

    // Test stop with recorder failure
    EXPECT_CALL(*getMockSource1(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), stop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), stop()).WillOnce(testing::Return(false));

    const bool result = getCoordinator()->onStop();

    EXPECT_FALSE(result);
}

// ==================== Tick Tests ====================

TEST_F(MeasurementCoordinatorTest, Tick_NoMeasurementsAvailable_NoRecordersNotified)
{
    EXPECT_CALL(*getMockSource1(), isMeasurementAvailable()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockSource2(), isMeasurementAvailable()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockRecorder1(), notify(testing::_)).Times(0);
    EXPECT_CALL(*getMockRecorder2(), notify(testing::_)).Times(0);

    const bool result = getCoordinator()->onTick();

    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, Tick_OneMeasurementAvailable_AllRecordersNotified)
{
    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_1,
        .data = std::uint32_t{100U}};

    EXPECT_CALL(*getMockSource1(), isMeasurementAvailable()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource1(), getMeasurement())
        .WillOnce(testing::Invoke([measurement]()
                                  { return measurement; }));
    EXPECT_CALL(*getMockSource2(), isMeasurementAvailable()).WillOnce(testing::Return(false));

    EXPECT_CALL(*getMockRecorder1(), notify(testing::_)).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), notify(testing::_)).WillOnce(testing::Return(true));

    const bool result = getCoordinator()->onTick();

    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, Tick_BothMeasurementsAvailable_AllRecordersNotifiedTwice)
{
    const auto measurement1 = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_1,
        .data = std::uint32_t{100U}};
    const auto measurement2 = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_2,
        .data = std::uint32_t{200U}};

    EXPECT_CALL(*getMockSource1(), isMeasurementAvailable()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource1(), getMeasurement())
        .WillOnce(testing::Invoke([measurement1]()
                                  { return measurement1; }));
    EXPECT_CALL(*getMockSource2(), isMeasurementAvailable()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), getMeasurement())
        .WillOnce(testing::Invoke([measurement2]()
                                  { return measurement2; }));

    EXPECT_CALL(*getMockRecorder1(), notify(testing::_)).Times(2).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), notify(testing::_)).Times(2).WillRepeatedly(testing::Return(true));

    const bool result = getCoordinator()->onTick();

    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, MultipleTicks_HandlesMultipleCycles)
{
    constexpr std::uint32_t TEST_MEASUREMENT_VALUE = 100U;
    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_1,
        .data = std::uint32_t{TEST_MEASUREMENT_VALUE}};

    EXPECT_CALL(*getMockSource1(), isMeasurementAvailable())
        .WillOnce(testing::Return(true))
        .WillOnce(testing::Return(false))
        .WillOnce(testing::Return(true));

    EXPECT_CALL(*getMockSource1(), getMeasurement())
        .Times(2)
        .WillRepeatedly(testing::Invoke([measurement]()
                                        { return measurement; }));

    EXPECT_CALL(*getMockSource2(), isMeasurementAvailable())
        .Times(3)
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(*getMockRecorder1(), notify(testing::_))
        .Times(2)
        .WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), notify(testing::_))
        .Times(2)
        .WillRepeatedly(testing::Return(true));

    EXPECT_TRUE(getCoordinator()->onTick());
    EXPECT_TRUE(getCoordinator()->onTick());
    EXPECT_TRUE(getCoordinator()->onTick());
}

// ==================== Test with Many Sources/Recorders ====================

class MeasurementCoordinatorLargeTest : public ::testing::Test
{
protected:
    static constexpr std::size_t NUM_SOURCES = 5U;
    static constexpr std::size_t NUM_RECORDERS = 3U;

    void SetUp() override
    {
        for (std::size_t i{}; i < NUM_SOURCES; ++i)
        {
            mockSources.push_back(std::make_unique<testing::NiceMock<MockMeasurementSource>>());
        }

        for (std::size_t i{}; i < NUM_RECORDERS; ++i)
        {
            mockRecorders.push_back(std::make_unique<testing::NiceMock<MockMeasurementRecorder>>());
        }

        sources = std::make_unique<std::array<Device::SourceVariant, NUM_SOURCES>>(
            std::array<Device::SourceVariant, NUM_SOURCES>{{std::ref(*mockSources[0]),
                                                            std::ref(*mockSources[1]),
                                                            std::ref(*mockSources[2]),
                                                            std::ref(*mockSources[3]),
                                                            std::ref(*mockSources[4])}});

        recorders = std::make_unique<std::array<Device::RecorderVariant, NUM_RECORDERS>>(
            std::array<Device::RecorderVariant, NUM_RECORDERS>{{std::ref(*mockRecorders[0]),
                                                                std::ref(*mockRecorders[1]),
                                                                std::ref(*mockRecorders[2])}});

        coordinator = std::make_unique<BusinessLogic::MeasurementCoordinator<NUM_SOURCES, NUM_RECORDERS>>(*sources, *recorders);
    }

    auto getMockSources() -> std::vector<std::unique_ptr<MockMeasurementSource>> & { return mockSources; }
    auto getMockRecorders() -> std::vector<std::unique_ptr<MockMeasurementRecorder>> & { return mockRecorders; }
    auto getCoordinator() -> BusinessLogic::MeasurementCoordinator<NUM_SOURCES, NUM_RECORDERS> * { return coordinator.get(); }

private:
    std::vector<std::unique_ptr<MockMeasurementSource>> mockSources;
    std::vector<std::unique_ptr<MockMeasurementRecorder>> mockRecorders;
    std::unique_ptr<std::array<Device::SourceVariant, NUM_SOURCES>> sources;
    std::unique_ptr<std::array<Device::RecorderVariant, NUM_RECORDERS>> recorders;
    std::unique_ptr<BusinessLogic::MeasurementCoordinator<NUM_SOURCES, NUM_RECORDERS>> coordinator;
};