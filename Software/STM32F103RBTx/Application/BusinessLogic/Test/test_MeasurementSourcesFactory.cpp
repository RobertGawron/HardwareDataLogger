#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "BusinessLogic/Inc/MeasurementSourcesFactory.hpp"
#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "BusinessLogic/Inc/MeasurementDataStore.hpp"
#include "Driver/Interface/IPulseCounterDriver.hpp"
#include "Driver/Interface/IUartDriver.hpp"

#include <cstdint>

// ============================================================================
// STUB IMPLEMENTATIONS
// ============================================================================

namespace Device
{
    // PulseCounterMeasurementSource stubs
    PulseCounterMeasurementSource::PulseCounterMeasurementSource(MeasurementDeviceId id, Driver::IPulseCounterDriver &driver)
        : IMeasurementSource(id), pulseCounterDriver(driver) {}
    bool PulseCounterMeasurementSource::initialize() { return true; }
    bool PulseCounterMeasurementSource::start() { return true; }
    bool PulseCounterMeasurementSource::stop() { return true; }
    bool PulseCounterMeasurementSource::isMeasurementAvailable() { return true; }
    MeasurementType PulseCounterMeasurementSource::getMeasurement() { return MeasurementType{}; }

    // UartMeasurementSource stubs
    UartMeasurementSource::UartMeasurementSource(MeasurementDeviceId id, Driver::IUartDriver &_driver)
        : IMeasurementSource(id), driver(_driver) {}
    bool UartMeasurementSource::initialize() { return true; }
    bool UartMeasurementSource::start() { return true; }
    bool UartMeasurementSource::stop() { return true; }
    bool UartMeasurementSource::isMeasurementAvailable() { return true; }
    MeasurementType UartMeasurementSource::getMeasurement() { return MeasurementType{}; }
}

namespace BusinessLogic
{
    // Counter for tracking addObserver calls
    static std::uint8_t addObserverCallCount = 0u;
    static bool addObserverShouldFail = false;
    static std::int8_t addObserverFailAtCall = -1;

    // MeasurementCoordinator stubs with controllable behavior
    MeasurementCoordinator::MeasurementCoordinator(IMeasurementDataStore &store)
        : storage(store), observers{} {}

    bool MeasurementCoordinator::addObserver(Device::IMeasurementSource &)
    {
        addObserverCallCount++;
        if (addObserverShouldFail || (addObserverFailAtCall > 0 && addObserverCallCount == static_cast<std::uint8_t>(addObserverFailAtCall)))
        {
            return false;
        }
        return true;
    }

    bool MeasurementCoordinator::removeObserver(Device::IMeasurementSource &) { return true; }
    bool MeasurementCoordinator::initialize() { return true; }
    bool MeasurementCoordinator::tick() { return true; }

    // MeasurementDataStore stubs
    bool MeasurementDataStore::initialize() { return true; }
    bool MeasurementDataStore::start() { return true; }
    bool MeasurementDataStore::addObserver(Device::IMeasurementRecorder &) { return true; }
    bool MeasurementDataStore::removeObserver(Device::IMeasurementRecorder &) { return true; }
    bool MeasurementDataStore::notifyObservers(Device::MeasurementType) { return true; }
}

// ============================================================================
// MOCK CLASSES
// ============================================================================

namespace BusinessLogic
{
    class MockPulseCounterDriver : public Driver::IPulseCounterDriver
    {
    public:
        MOCK_METHOD(bool, onInitialize, (), (override));
        MOCK_METHOD(bool, onStart, (), (override));
        MOCK_METHOD(bool, onStop, (), (override));
        MOCK_METHOD(bool, onReset, (), (override));
        MOCK_METHOD(CounterSizeType, getMeasurement, (), (override));
        MOCK_METHOD(void, clearMeasurement, (), (override));
    };

    class MockUartDriver : public Driver::IUartDriver
    {
    public:
        MOCK_METHOD(bool, onInitialize, (), (override));
        MOCK_METHOD(bool, onStart, (), (override));
        MOCK_METHOD(bool, onStop, (), (override));
        MOCK_METHOD(bool, onReset, (), (override));
        MOCK_METHOD(Driver::UartExchangeStatus, transmit,
                    (std::uint8_t *, std::uint16_t, std::uint32_t), (override));
        MOCK_METHOD(Driver::UartExchangeStatus, receive,
                    (std::uint8_t *, std::uint16_t, std::uint32_t), (override));
    };

    // ============================================================================
    // TEST FIXTURE
    // ============================================================================

    class MeasurementSourcesFactoryTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // Reset global test state
            addObserverCallCount = 0u;
            addObserverShouldFail = false;
            addObserverFailAtCall = -1;

            // Create mock drivers
            mockPcDriver1 = std::make_unique<::testing::NiceMock<MockPulseCounterDriver>>();
            mockPcDriver2 = std::make_unique<::testing::NiceMock<MockPulseCounterDriver>>();
            mockPcDriver3 = std::make_unique<::testing::NiceMock<MockPulseCounterDriver>>();
            mockPcDriver4 = std::make_unique<::testing::NiceMock<MockPulseCounterDriver>>();
            mockUartDriver = std::make_unique<::testing::NiceMock<MockUartDriver>>();

            // Create data store
            dataStore = std::make_unique<MeasurementDataStore>();

            // Create factory
            factory = std::make_unique<MeasurementSourcesFactory>(
                *mockPcDriver1,
                *mockPcDriver2,
                *mockPcDriver3,
                *mockPcDriver4,
                *mockUartDriver);
        }

        void TearDown() override
        {
            factory.reset();
            mockPcDriver1.reset();
            mockPcDriver2.reset();
            mockPcDriver3.reset();
            mockPcDriver4.reset();
            mockUartDriver.reset();
            dataStore.reset();
        }

        // Getters
        MeasurementSourcesFactory &getFactory() { return *factory; }
        MeasurementDataStore &getDataStore() { return *dataStore; }

    private:
        std::unique_ptr<MockPulseCounterDriver> mockPcDriver1;
        std::unique_ptr<MockPulseCounterDriver> mockPcDriver2;
        std::unique_ptr<MockPulseCounterDriver> mockPcDriver3;
        std::unique_ptr<MockPulseCounterDriver> mockPcDriver4;
        std::unique_ptr<MockUartDriver> mockUartDriver;
        std::unique_ptr<MeasurementDataStore> dataStore;
        std::unique_ptr<MeasurementSourcesFactory> factory;
    };

    // ============================================================================
    // CONSTRUCTOR TESTS
    // ============================================================================

    TEST_F(MeasurementSourcesFactoryTest, Constructor_CreatesFactorySuccessfully)
    {
        EXPECT_NE(&getFactory(), nullptr);
    }

    // ============================================================================
    // INITIALIZE TESTS
    // ============================================================================

    TEST_F(MeasurementSourcesFactoryTest, Initialize_ReturnsTrue)
    {
        bool result = getFactory().initialize();
        EXPECT_TRUE(result);
    }

    // ============================================================================
    // REGISTER SOURCES TESTS
    // ============================================================================

    TEST_F(MeasurementSourcesFactoryTest, RegisterSources_AllSourcesRegistered_ReturnsTrue)
    {
        MeasurementCoordinator coordinator(getDataStore());

        bool result = getFactory().registerSources(coordinator);

        EXPECT_TRUE(result);
        EXPECT_EQ(addObserverCallCount, 5u); // 4 pulse counters + 1 UART
    }

    TEST_F(MeasurementSourcesFactoryTest, RegisterSources_FirstPulseCounterFails_ReturnsFalse)
    {
        MeasurementCoordinator coordinator(getDataStore());
        addObserverFailAtCall = 1; // Fail on first call

        bool result = getFactory().registerSources(coordinator);

        EXPECT_FALSE(result);
        EXPECT_EQ(addObserverCallCount, 1u); // Should stop after first failure
    }

    TEST_F(MeasurementSourcesFactoryTest, RegisterSources_SecondPulseCounterFails_ReturnsFalse)
    {
        MeasurementCoordinator coordinator(getDataStore());
        addObserverFailAtCall = 2; // Fail on second call

        bool result = getFactory().registerSources(coordinator);

        EXPECT_FALSE(result);
        EXPECT_EQ(addObserverCallCount, 2u); // Should stop after second failure
    }

    TEST_F(MeasurementSourcesFactoryTest, RegisterSources_ThirdPulseCounterFails_ReturnsFalse)
    {
        MeasurementCoordinator coordinator(getDataStore());
        addObserverFailAtCall = 3; // Fail on third call

        bool result = getFactory().registerSources(coordinator);

        EXPECT_FALSE(result);
        EXPECT_EQ(addObserverCallCount, 3u); // Should stop after third failure
    }

    TEST_F(MeasurementSourcesFactoryTest, RegisterSources_FourthPulseCounterFails_ReturnsFalse)
    {
        MeasurementCoordinator coordinator(getDataStore());
        addObserverFailAtCall = 4; // Fail on fourth call

        bool result = getFactory().registerSources(coordinator);

        EXPECT_FALSE(result);
        EXPECT_EQ(addObserverCallCount, 4u); // Should stop after fourth failure
    }

    TEST_F(MeasurementSourcesFactoryTest, RegisterSources_UartSourceFails_ReturnsFalse)
    {
        MeasurementCoordinator coordinator(getDataStore());
        addObserverFailAtCall = 5; // Fail on fifth call (UART)

        bool result = getFactory().registerSources(coordinator);

        EXPECT_FALSE(result);
        EXPECT_EQ(addObserverCallCount, 5u); // All 5 calls made, last one failed
    }

    TEST_F(MeasurementSourcesFactoryTest, RegisterSources_RegistersExactly5Sources)
    {
        MeasurementCoordinator coordinator(getDataStore());

        getFactory().registerSources(coordinator);

        // Verify exactly 5 sources are registered
        EXPECT_EQ(addObserverCallCount, 5u);
    }

} // namespace BusinessLogic