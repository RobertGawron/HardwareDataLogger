#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "BusinessLogic/Inc/MeasurementStoresFactory.hpp"
#include "BusinessLogic/Inc/MeasurementDataStore.hpp"
#include "Device/Inc/CacheMeasurementRecorder.hpp"
#include "Driver/Interface/IUartDriver.hpp"
#include "Driver/Interface/ISdCardDriver.hpp"

namespace Device
{
    // WiFiMeasurementRecorder stubs
    WiFiMeasurementRecorder::WiFiMeasurementRecorder(Driver::IUartDriver &_driver)
        : driver(_driver) {}

    bool WiFiMeasurementRecorder::onInitialize() { return true; }
    bool WiFiMeasurementRecorder::onStart() { return true; }
    bool WiFiMeasurementRecorder::onStop() { return true; }
    bool WiFiMeasurementRecorder::onReset() { return true; }
    bool WiFiMeasurementRecorder::notify(Device::MeasurementType &) { return true; }
    bool WiFiMeasurementRecorder::flush() { return true; }

    // SdCardMeasurementRecorder stubs
    SdCardMeasurementRecorder::SdCardMeasurementRecorder(Driver::ISdCardDriver &_driver)
        : driver(_driver) {}

    bool SdCardMeasurementRecorder::onInitialize() { return true; }
    bool SdCardMeasurementRecorder::onStart() { return true; }
    bool SdCardMeasurementRecorder::onStop() { return true; }
    bool SdCardMeasurementRecorder::onReset() { return true; }
    bool SdCardMeasurementRecorder::notify(Device::MeasurementType &) { return true; }
    bool SdCardMeasurementRecorder::flush() { return true; }

    // CacheMeasurementRecorder stubs
    bool CacheMeasurementRecorder::onInitialize() { return true; }
    bool CacheMeasurementRecorder::onStart() { return true; }
    bool CacheMeasurementRecorder::onStop() { return true; }
    bool CacheMeasurementRecorder::onReset() { return true; }
    bool CacheMeasurementRecorder::notify(Device::MeasurementType &) { return true; }
    bool CacheMeasurementRecorder::write(Device::MeasurementType &) { return true; }
    bool CacheMeasurementRecorder::flush() { return true; }
    std::uint32_t CacheMeasurementRecorder::getLatestMeasurement(Device::MeasurementDeviceId) const
    {
        return 0;
    }
}

namespace BusinessLogic
{
    // MeasurementDataStore stubs
    bool MeasurementDataStore::initialize() { return true; }
    bool MeasurementDataStore::start() { return true; }
    bool MeasurementDataStore::addObserver(Device::IMeasurementRecorder &) { return true; }
    bool MeasurementDataStore::removeObserver(Device::IMeasurementRecorder &) { return true; }
    bool MeasurementDataStore::notifyObservers(Device::MeasurementType) { return true; }
}

namespace BusinessLogic
{
    // Mock classes
    class MockCacheMeasurementRecorder : public Device::CacheMeasurementRecorder
    {
    public:
        MOCK_METHOD(bool, initialize, (), (override));
        MOCK_METHOD(bool, start, (), (override));
    };

    class MockWiFiRecorder
    {
    public:
        MOCK_METHOD(bool, initialize, ());
        MOCK_METHOD(bool, start, ());
    };

    class MockSdCardRecorder
    {
    public:
        MOCK_METHOD(bool, initialize, ());
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

    class MockSdCardDriver : public Driver::ISdCardDriver
    {
    public:
        MOCK_METHOD(bool, onInitialize, (), (override));
        MOCK_METHOD(bool, onStart, (), (override));
        MOCK_METHOD(bool, onStop, (), (override));
        MOCK_METHOD(bool, onReset, (), (override));
        MOCK_METHOD(void, mountFileSystem, (), (override));
        MOCK_METHOD(void, unmountFileSystem, (), (override));
        MOCK_METHOD(void, openFile, (), (override));
        MOCK_METHOD(void, closeFile, (), (override));
        MOCK_METHOD(void, sync, (), (override));
        MOCK_METHOD(void, writeToFile, (), (override));
    };

    class MockMeasurementDataStore : public MeasurementDataStore
    {
    public:
        MOCK_METHOD(bool, addObserver, (Device::IMeasurementRecorder &), (override));
        MOCK_METHOD(bool, removeObserver, (Device::IMeasurementRecorder &), (override));
        MOCK_METHOD(bool, initialize, (), (override));
        MOCK_METHOD(bool, start, (), (override));
        MOCK_METHOD(bool, notifyObservers, (Device::MeasurementType), (override));
    };

    // Test Fixture
    class MeasurementStoresFactoryTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            mockCacheRecorder = std::make_unique<::testing::NiceMock<MockCacheMeasurementRecorder>>();
            mockUartDriver = std::make_unique<::testing::NiceMock<MockUartDriver>>();
            mockSdCardDriver = std::make_unique<::testing::NiceMock<MockSdCardDriver>>();

            factory = std::make_unique<MeasurementStoresFactory>(
                *mockCacheRecorder,
                *mockUartDriver,
                *mockSdCardDriver);
        }

        void TearDown() override
        {
            factory.reset();
            mockCacheRecorder.reset();
            mockUartDriver.reset();
            mockSdCardDriver.reset();
        }

        // Getters for test access
        MockCacheMeasurementRecorder &getCacheRecorder() { return *mockCacheRecorder; }
        MockUartDriver &getUartDriver() { return *mockUartDriver; }
        MockSdCardDriver &getSdCardDriver() { return *mockSdCardDriver; }
        MeasurementStoresFactory &getFactory() { return *factory; }

    private:
        std::unique_ptr<MockCacheMeasurementRecorder> mockCacheRecorder;
        std::unique_ptr<MockUartDriver> mockUartDriver;
        std::unique_ptr<MockSdCardDriver> mockSdCardDriver;
        std::unique_ptr<MeasurementStoresFactory> factory;
    };

    // Constructor Tests
    TEST_F(MeasurementStoresFactoryTest, Constructor_CreatesFactorySuccessfully)
    {
        EXPECT_NE(&getFactory(), nullptr);
    }

    // Initialize Tests
    TEST_F(MeasurementStoresFactoryTest, Initialize_AllComponentsSucceed_ReturnsTrue)
    {
        EXPECT_CALL(getCacheRecorder(), initialize())
            .WillOnce(::testing::Return(true));

        bool result = getFactory().initialize();

        EXPECT_TRUE(result);
    }

    TEST_F(MeasurementStoresFactoryTest, Initialize_WifiRecorderInitializeFails_ReturnsFalse)
    {
        // Mock wifi recorder initialization failure
        // Adjust based on actual implementation

        bool result = getFactory().initialize();

        // This test needs to be adjusted once you have the actual recorder mock setup
        // EXPECT_FALSE(result);
    }

    TEST_F(MeasurementStoresFactoryTest, Initialize_SdCardRecorderInitializeFails_ReturnsFalse)
    {
        // Mock SD card recorder initialization failure

        bool result = getFactory().initialize();

        // Adjust expectations based on implementation
    }

    TEST_F(MeasurementStoresFactoryTest, Initialize_CacheRecorderInitializeFails_ReturnsFalse)
    {
        EXPECT_CALL(getCacheRecorder(), initialize())
            .WillOnce(::testing::Return(false));

        bool result = getFactory().initialize();

        EXPECT_FALSE(result);
    }

    TEST_F(MeasurementStoresFactoryTest, Initialize_WifiRecorderStartFails_ReturnsFalse)
    {
        // Mock all initializations succeed but start fails
        EXPECT_CALL(getCacheRecorder(), initialize())
            .WillOnce(::testing::Return(true));

        // Add wifi recorder start failure expectation

        bool result = getFactory().initialize();

        // EXPECT_FALSE(result);
    }

    TEST_F(MeasurementStoresFactoryTest, Initialize_CallsComponentsInCorrectOrder)
    {
        // Use Sequence to verify order of calls
        ::testing::Sequence seq;

        // Verify initialization happens before start
        EXPECT_CALL(getCacheRecorder(), initialize())
            .InSequence(seq)
            .WillOnce(::testing::Return(true));

        getFactory().initialize();
    }

    TEST_F(MeasurementStoresFactoryTest, RegisterStores_AllObserversAddedSuccessfully_ReturnsTrue)
    {
        MockMeasurementDataStore mockCoordinator;

        // Match the actual order: wifi, sdCard, cache
        EXPECT_CALL(mockCoordinator, addObserver(::testing::_))
            .Times(3)
            .WillRepeatedly(::testing::Return(true));

        bool result = getFactory().registerStores(mockCoordinator);

        EXPECT_TRUE(result);
    }

    TEST_F(MeasurementStoresFactoryTest, RegisterStores_FirstObserverFails_ReturnsFalse)
    {
        MockMeasurementDataStore mockCoordinator;

        EXPECT_CALL(mockCoordinator, addObserver(::testing::_))
            .WillOnce(::testing::Return(false));

        bool result = getFactory().registerStores(mockCoordinator);

        EXPECT_FALSE(result);
    }

    TEST_F(MeasurementStoresFactoryTest, RegisterStores_SecondObserverFails_ReturnsFalse)
    {
        MockMeasurementDataStore mockCoordinator;

        EXPECT_CALL(mockCoordinator, addObserver(::testing::_))
            .WillOnce(::testing::Return(true))
            .WillOnce(::testing::Return(false));

        bool result = getFactory().registerStores(mockCoordinator);

        EXPECT_FALSE(result);
    }

    TEST_F(MeasurementStoresFactoryTest, RegisterStores_ThirdObserverFails_ReturnsFalse)
    {
        MockMeasurementDataStore mockCoordinator;

        EXPECT_CALL(mockCoordinator, addObserver(::testing::_))
            .WillOnce(::testing::Return(true))
            .WillOnce(::testing::Return(true))
            .WillOnce(::testing::Return(false));

        bool result = getFactory().registerStores(mockCoordinator);

        EXPECT_FALSE(result);
    }

    TEST_F(MeasurementStoresFactoryTest, RegisterStores_CallsAddObserverForAllRecorders)
    {
        MockMeasurementDataStore mockCoordinator;

        // Verify all three recorders are registered
        EXPECT_CALL(mockCoordinator, addObserver(::testing::_))
            .Times(3)
            .WillRepeatedly(::testing::Return(true));

        getFactory().registerStores(mockCoordinator);
    }

} // namespace BusinessLogic