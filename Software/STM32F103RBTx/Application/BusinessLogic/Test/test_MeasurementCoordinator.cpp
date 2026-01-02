#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "Device/Interface/MeasurementSourceBase.hpp"
#include "Device/Interface/MeasurementRecorderBase.hpp"

#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

// Mock classes - must match actual interface signatures including noexcept
class MockMeasurementSource : public Device::IMeasurementSource
{
public:
    MockMeasurementSource() = default;

    MOCK_METHOD(bool, onInit, (), (override, noexcept));
    MOCK_METHOD(bool, onStart, (), (override, noexcept));
    MOCK_METHOD(bool, onStop, (), (override, noexcept));
    MOCK_METHOD(bool, isMeasurementAvailable, (), (const, override, noexcept));
    MOCK_METHOD(Device::MeasurementType, getMeasurement, (), (override, noexcept));
};

class MockMeasurementRecorder : public Device::IMeasurementRecorder
{
public:
    MOCK_METHOD(bool, onInit, (), (override, noexcept));
    MOCK_METHOD(bool, onStart, (), (override, noexcept));
    MOCK_METHOD(bool, onStop, (), (override, noexcept));
    MOCK_METHOD(bool, notify, (const Device::MeasurementType &), (override, noexcept));
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

        sources = std::make_unique<std::array<std::reference_wrapper<Device::IMeasurementSource>, 2>>(
            std::array<std::reference_wrapper<Device::IMeasurementSource>, 2>{{std::ref(*mockSource1),
                                                                               std::ref(*mockSource2)}});

        recorders = std::make_unique<std::array<std::reference_wrapper<Device::IMeasurementRecorder>, 2>>(
            std::array<std::reference_wrapper<Device::IMeasurementRecorder>, 2>{{std::ref(*mockRecorder1),
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

    std::unique_ptr<std::array<std::reference_wrapper<Device::IMeasurementSource>, 2>> sources;
    std::unique_ptr<std::array<std::reference_wrapper<Device::IMeasurementRecorder>, 2>> recorders;

    std::unique_ptr<BusinessLogic::MeasurementCoordinator<2, 2>> coordinator;
};

// ==================== init Tests ====================

TEST_F(MeasurementCoordinatorTest, init_AllSourcesSucceed_ReturnsTrue)
{
    EXPECT_CALL(*getMockSource1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onInit()).WillOnce(testing::Return(true));

    const bool result = getCoordinator()->init();

    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, init_SourceFails_ReturnsFalse)
{
    EXPECT_CALL(*getMockSource1(), onInit()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockSource2(), onInit()).Times(0);

    const bool result = getCoordinator()->init();

    EXPECT_FALSE(result);
}

TEST_F(MeasurementCoordinatorTest, init_SourcesSucceedRecorderFails_ReturnsFalse)
{
    EXPECT_CALL(*getMockSource1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onInit()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockRecorder2(), onInit()).Times(0);

    const bool result = getCoordinator()->init();

    EXPECT_FALSE(result);
}

// ==================== Start Tests ====================

TEST_F(MeasurementCoordinatorTest, Start_AllSucceed_ReturnsTrue)
{
    // Initialize first (required for state machine)
    EXPECT_CALL(*getMockSource1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onInit()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->init());

    // Now test start
    EXPECT_CALL(*getMockSource1(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onStart()).WillOnce(testing::Return(true));

    const bool result = getCoordinator()->start();

    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, Start_SourceFails_ReturnsFalse)
{
    // Initialize first
    EXPECT_CALL(*getMockSource1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onInit()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->init());

    // Test start with source failure
    EXPECT_CALL(*getMockSource1(), onStart()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockSource2(), onStart()).Times(0);
    EXPECT_CALL(*getMockRecorder1(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onStart()).WillOnce(testing::Return(true));

    const bool result = getCoordinator()->start();

    EXPECT_FALSE(result);
}

TEST_F(MeasurementCoordinatorTest, Start_RecorderFails_ReturnsFalse)
{
    // Initialize first
    EXPECT_CALL(*getMockSource1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onInit()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->init());

    // Test start with recorder failure
    EXPECT_CALL(*getMockSource1(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onStart()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockRecorder2(), onStart()).Times(0);

    const bool result = getCoordinator()->start();

    EXPECT_FALSE(result);
}

// ==================== Stop Tests ====================

TEST_F(MeasurementCoordinatorTest, Stop_AllSucceed_ReturnsTrue)
{
    // Initialize and start first (required for state machine)
    EXPECT_CALL(*getMockSource1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onInit()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->init());

    EXPECT_CALL(*getMockSource1(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onStart()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->start());

    // Now test stop
    EXPECT_CALL(*getMockSource1(), onStop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onStop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onStop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onStop()).WillOnce(testing::Return(true));

    const bool result = getCoordinator()->stop();

    EXPECT_TRUE(result);
}

TEST_F(MeasurementCoordinatorTest, Stop_SourceFails_ReturnsFalse)
{
    // Initialize and start first
    EXPECT_CALL(*getMockSource1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onInit()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->init());

    EXPECT_CALL(*getMockSource1(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onStart()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->start());

    // Test stop with source failure
    EXPECT_CALL(*getMockSource1(), onStop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onStop()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockRecorder1(), onStop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onStop()).WillOnce(testing::Return(true));

    const bool result = getCoordinator()->stop();

    EXPECT_FALSE(result);
}

TEST_F(MeasurementCoordinatorTest, Stop_RecorderFails_ReturnsFalse)
{
    // Initialize and start first
    EXPECT_CALL(*getMockSource1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onInit()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onInit()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->init());

    EXPECT_CALL(*getMockSource1(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onStart()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onStart()).WillOnce(testing::Return(true));
    ASSERT_TRUE(getCoordinator()->start());

    // Test stop with recorder failure
    EXPECT_CALL(*getMockSource1(), onStop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockSource2(), onStop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder1(), onStop()).WillOnce(testing::Return(true));
    EXPECT_CALL(*getMockRecorder2(), onStop()).WillOnce(testing::Return(false));

    const bool result = getCoordinator()->stop();

    EXPECT_FALSE(result);
}

// ==================== Tick Tests ====================

TEST_F(MeasurementCoordinatorTest, Tick_NoMeasurementsAvailable_NoRecordersNotified)
{
    EXPECT_CALL(*getMockSource1(), isMeasurementAvailable()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockSource2(), isMeasurementAvailable()).WillOnce(testing::Return(false));
    EXPECT_CALL(*getMockRecorder1(), notify(testing::_)).Times(0);
    EXPECT_CALL(*getMockRecorder2(), notify(testing::_)).Times(0);

    const bool result = getCoordinator()->tick();

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

    const bool result = getCoordinator()->tick();

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

    const bool result = getCoordinator()->tick();

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
        for (std::size_t i{}; i < NUM_SOURCES; ++i)
        {
            mockSources.push_back(std::make_unique<testing::NiceMock<MockMeasurementSource>>());
        }

        for (std::size_t i{}; i < NUM_RECORDERS; ++i)
        {
            mockRecorders.push_back(std::make_unique<testing::NiceMock<MockMeasurementRecorder>>());
        }

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

    auto getMockSources() -> std::vector<std::unique_ptr<MockMeasurementSource>> & { return mockSources; }
    auto getMockRecorders() -> std::vector<std::unique_ptr<MockMeasurementRecorder>> & { return mockRecorders; }
    auto getCoordinator() -> BusinessLogic::MeasurementCoordinator<NUM_SOURCES, NUM_RECORDERS> * { return coordinator.get(); }

private:
    std::vector<std::unique_ptr<MockMeasurementSource>> mockSources;
    std::vector<std::unique_ptr<MockMeasurementRecorder>> mockRecorders;
    std::unique_ptr<std::array<std::reference_wrapper<Device::IMeasurementSource>, NUM_SOURCES>> sources;
    std::unique_ptr<std::array<std::reference_wrapper<Device::IMeasurementRecorder>, NUM_RECORDERS>> recorders;
    std::unique_ptr<BusinessLogic::MeasurementCoordinator<NUM_SOURCES, NUM_RECORDERS>> coordinator;
};