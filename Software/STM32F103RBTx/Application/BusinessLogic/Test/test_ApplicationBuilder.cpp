#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "BusinessLogic/Inc/ApplicationBuilder.hpp"
#include "BusinessLogic/Interface/IPlatformFactory.hpp"
#include "Driver/Interface/IPulseCounterDriver.hpp"
#include "Driver/Interface/IUartDriver.hpp"
#include "Driver/Interface/ISdCardDriver.hpp"

// ============================================================================
// U8X8/U8G2 LIBRARY STUBS
// ============================================================================

extern "C"
{
    // u8x8_8x8.c stubs
    uint16_t u8x8_ascii_next(u8x8_t *u8x8, uint8_t b) { return b; }
    uint16_t u8x8_utf8_next(u8x8_t *u8x8, uint8_t b) { return b; }
    void u8x8_utf8_init(u8x8_t *u8x8) {}
}

// ============================================================================
// DEVICE STUBS
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
    std::uint32_t CacheMeasurementRecorder::getLatestMeasurement(Device::MeasurementDeviceId) const { return 0; }

    // Display stubs - inherits from IDisplay which inherits from U8G2
    Display::Display(Driver::IDisplayDriver &driver)
        : IDisplay(), displayDriver(driver) {}
    bool Display::initialize() { return true; }

    // DisplayBrightnessRegulator stubs
    DisplayBrightnessRegulator::DisplayBrightnessRegulator(
        Driver::IAmbientLightSensorDriver &als,
        Driver::IDisplayBrightnessDriver &brightness)
        : ambientLightSensorDriver(als), displayBrightnessDriver(brightness) {}
    bool DisplayBrightnessRegulator::init() { return true; }
    void DisplayBrightnessRegulator::tick() {}
    std::uint8_t DisplayBrightnessRegulator::getBrightnessPercentage() const { return 50; }
    bool DisplayBrightnessRegulator::setBrightnessPercentage(std::uint8_t) { return true; }

    // Keyboard stubs
    Keyboard::Keyboard(Driver::IKeyboardDriver &driver) : keyboardDriver(driver) {}
    bool Keyboard::init() { return true; }
    bool Keyboard::tick() { return true; }
    KeyboardKeyActionState Keyboard::getKeyState(Driver::KeyboardKeyIdentifier) const { return KeyboardKeyActionState{}; }
}

// ============================================================================
// BUSINESS LOGIC STUBS
// ============================================================================

namespace BusinessLogic
{
    // HmiMeasurementModel stubs
    HmiMeasurementModel::HmiMeasurementModel(Device::IMeasurementReader &reader) : reader(reader) {}
    std::uint32_t HmiMeasurementModel::getLatestMeasurement(Device::MeasurementDeviceId) const { return 0; }

    // HmiMui stubs
    HmiMui::HmiMui(HmiMeasurementModel &model, Device::IDisplay &disp,
                   Device::IDisplayBrightnessRegulator &bright, Device::IKeyboard &kbd)
        : hmiMeasurementModel(model), display(disp), displayBrightnessRegulator(bright), keyboard(kbd), mui() {}
    bool HmiMui::initialize() { return true; }
    bool HmiMui::start() { return true; }
    bool HmiMui::tick() { return true; }

    // MeasurementSourcesFactory stubs
    MeasurementSourcesFactory::MeasurementSourcesFactory(
        Driver::IPulseCounterDriver &pcA,
        Driver::IPulseCounterDriver &pcB,
        Driver::IPulseCounterDriver &pcC,
        Driver::IPulseCounterDriver &pcD,
        Driver::IUartDriver &_uart)
        : pulseCounter{{Device::PulseCounterMeasurementSource(Device::MeasurementDeviceId::PULSE_COUNTER_1, pcA),
                        Device::PulseCounterMeasurementSource(Device::MeasurementDeviceId::PULSE_COUNTER_2, pcB),
                        Device::PulseCounterMeasurementSource(Device::MeasurementDeviceId::PULSE_COUNTER_3, pcC),
                        Device::PulseCounterMeasurementSource(Device::MeasurementDeviceId::PULSE_COUNTER_4, pcD)}},
          uart(_uart),
          uartMeasurementSource(Device::MeasurementDeviceId::DEVICE_UART_1, _uart) {}

    bool MeasurementSourcesFactory::initialize() { return true; }
    bool MeasurementSourcesFactory::registerSources(MeasurementCoordinator &) { return true; }

    // MeasurementStoresFactory stubs
    MeasurementStoresFactory::MeasurementStoresFactory(
        Device::CacheMeasurementRecorder &cache,
        Driver::IUartDriver &uart,
        Driver::ISdCardDriver &sd)
        : cacheRecorder(cache),
          wifiRecorder(uart),
          sdCardRecorder(sd) {}

    bool MeasurementStoresFactory::initialize() { return true; }
    bool MeasurementStoresFactory::registerStores(MeasurementDataStore &) { return true; }

    // MeasurementCoordinator stubs
    MeasurementCoordinator::MeasurementCoordinator(IMeasurementDataStore &store)
        : storage(store), observers{} {}
    bool MeasurementCoordinator::initialize() { return true; }
    bool MeasurementCoordinator::tick() { return true; }
    bool MeasurementCoordinator::addObserver(Device::IMeasurementSource &) { return true; }
    bool MeasurementCoordinator::removeObserver(Device::IMeasurementSource &) { return true; }

    // HmiFactory stubs
    HmiFactory::HmiFactory(Device::IMeasurementReader &reader, IPlatformFactory &factory)
        : hmiMeasurementModel(reader),
          display(factory.getDisplayDriver()),
          brightnessRegulator(factory.getAmbientLightSensorDriver(), factory.getDisplayBrightnessDriver()),
          keyboard(factory.getKeyboardDriver()),
          hmi(hmiMeasurementModel, display, brightnessRegulator, keyboard) {}

    bool HmiFactory::initialize() { return true; }
    bool HmiFactory::start() { return true; }
    bool HmiFactory::tick() { return true; }

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
    class MockPlatformFactory : public IPlatformFactory
    {
    public:
        MOCK_METHOD(Driver::IPulseCounterDriver &, getPulseCounterDriver,
                    (Driver::PulseCounterId), (override));
        MOCK_METHOD(Driver::IUartDriver &, getUartDriver,
                    (Driver::UartId), (override));
        MOCK_METHOD(Driver::ISdCardDriver &, getSdCardDriver, (), (override));
        MOCK_METHOD(Driver::IAmbientLightSensorDriver &, getAmbientLightSensorDriver, (), (override));
        MOCK_METHOD(Driver::IDisplayBrightnessDriver &, getDisplayBrightnessDriver, (), (override));
        MOCK_METHOD(Driver::IDisplayDriver &, getDisplayDriver, (), (override));
        MOCK_METHOD(Driver::IKeyboardDriver &, getKeyboardDriver, (), (override));
    };

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
        MOCK_METHOD(Driver::UartStatus, transmit,
                    (std::uint8_t *, std::uint16_t, std::uint32_t), (override));
        MOCK_METHOD(Driver::UartStatus, receive,
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

    class MockAmbientLightSensorDriver : public Driver::IAmbientLightSensorDriver
    {
    public:
        MOCK_METHOD(bool, onInitialize, (), (override));
        MOCK_METHOD(bool, onStart, (), (override));
        MOCK_METHOD(bool, onStop, (), (override));
        MOCK_METHOD(bool, onReset, (), (override));
        MOCK_METHOD(std::uint32_t, getAmbientLightLevel, (), (const, override));
    };

    class MockDisplayBrightnessDriver : public Driver::IDisplayBrightnessDriver
    {
    public:
        MOCK_METHOD(bool, onInitialize, (), (override));
        MOCK_METHOD(bool, onStart, (), (override));
        MOCK_METHOD(bool, onStop, (), (override));
        MOCK_METHOD(bool, onReset, (), (override));
        MOCK_METHOD(bool, setBrightness, (Driver::IDisplayBrightnessDriver::BrightnessPercentage), (override));
    };

    class MockDisplayDriver : public Driver::IDisplayDriver
    {
    public:
        MOCK_METHOD(bool, onInitialize, (), (override));
        MOCK_METHOD(bool, onStart, (), (override));
        MOCK_METHOD(bool, onStop, (), (override));
        MOCK_METHOD(bool, onReset, (), (override));
        MOCK_METHOD(Status, displayOn, (), (override));
        MOCK_METHOD(Status, displayOff, (), (override));
        MOCK_METHOD(Status, setOrientation, (Orientation), (override));
        MOCK_METHOD(Status, getOrientation, (Orientation &), (const, override));
        MOCK_METHOD(Status, setCursor, (std::uint8_t, std::uint8_t), (override));
        MOCK_METHOD(Status, drawBitmap, (std::uint8_t, std::uint8_t, std::uint8_t &), (override));
        MOCK_METHOD(Status, fillRGBRectangle, (std::uint8_t, std::uint8_t, std::uint8_t &, std::uint8_t, std::uint8_t), (override));
        MOCK_METHOD(Status, drawHorizontalLine, (std::uint8_t, std::uint8_t, std::uint8_t, Driver::DisplayPixelColor::PixelColor), (override));
        MOCK_METHOD(Status, drawVerticalLine, (std::uint8_t, std::uint8_t, std::uint8_t, Driver::DisplayPixelColor::PixelColor), (override));
        MOCK_METHOD(Status, fillRectangle, (std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t, Driver::DisplayPixelColor::PixelColor), (override));
        MOCK_METHOD(Status, setPixel, (std::uint8_t, std::uint8_t, Driver::DisplayPixelColor::PixelColor), (override));
        MOCK_METHOD(Status, getPixel, (std::uint8_t, std::uint8_t, Driver::DisplayPixelColor::PixelColor &), (const, override));
        MOCK_METHOD(Status, getXSize, (std::uint8_t &), (const, override));
        MOCK_METHOD(Status, getYSize, (std::uint8_t &), (const, override));
    };

    class MockKeyboardDriver : public Driver::IKeyboardDriver
    {
    public:
        MOCK_METHOD(bool, onInitialize, (), (override));
        MOCK_METHOD(bool, onStart, (), (override));
        MOCK_METHOD(bool, onStop, (), (override));
        MOCK_METHOD(bool, onReset, (), (override));
        MOCK_METHOD(bool, tick, (), (override));
        MOCK_METHOD(Driver::KeyboardKeyState, getKeyState, (Driver::KeyboardKeyIdentifier), (const, override));
    };

    // ============================================================================
    // TEST FIXTURE
    // ============================================================================

    class ApplicationBuilderTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // Create mock drivers
            mockPulseCounterBncA = std::make_unique<::testing::NiceMock<MockPulseCounterDriver>>();
            mockPulseCounterBncB = std::make_unique<::testing::NiceMock<MockPulseCounterDriver>>();
            mockPulseCounterBncC = std::make_unique<::testing::NiceMock<MockPulseCounterDriver>>();
            mockPulseCounterBncD = std::make_unique<::testing::NiceMock<MockPulseCounterDriver>>();
            mockUartMEASUREMENT_RECEIVER = std::make_unique<::testing::NiceMock<MockUartDriver>>();
            mockUartWiFi = std::make_unique<::testing::NiceMock<MockUartDriver>>();
            mockSdCardDriver = std::make_unique<::testing::NiceMock<MockSdCardDriver>>();
            mockAmbientLightSensor = std::make_unique<::testing::NiceMock<MockAmbientLightSensorDriver>>();
            mockDisplayBrightness = std::make_unique<::testing::NiceMock<MockDisplayBrightnessDriver>>();
            mockDisplayDriver = std::make_unique<::testing::NiceMock<MockDisplayDriver>>();
            mockKeyboardDriver = std::make_unique<::testing::NiceMock<MockKeyboardDriver>>();

            // Create mock platform factory
            mockPlatformFactory = std::make_unique<::testing::NiceMock<MockPlatformFactory>>();

            // Setup platform factory expectations
            setupPlatformFactoryExpectations();

            // Create application builder
            applicationBuilder = std::make_unique<ApplicationBuilder>(*mockPlatformFactory);
        }

        void TearDown() override
        {
            applicationBuilder.reset();
            mockPlatformFactory.reset();
            mockPulseCounterBncA.reset();
            mockPulseCounterBncB.reset();
            mockPulseCounterBncC.reset();
            mockPulseCounterBncD.reset();
            mockUartMEASUREMENT_RECEIVER.reset();
            mockUartWiFi.reset();
            mockSdCardDriver.reset();
            mockAmbientLightSensor.reset();
            mockDisplayBrightness.reset();
            mockDisplayDriver.reset();
            mockKeyboardDriver.reset();
        }

        void setupPlatformFactoryExpectations()
        {
            using ::testing::ReturnRef;

            ON_CALL(*mockPlatformFactory, getPulseCounterDriver(Driver::PulseCounterId::bncA))
                .WillByDefault(ReturnRef(*mockPulseCounterBncA));
            ON_CALL(*mockPlatformFactory, getPulseCounterDriver(Driver::PulseCounterId::bncB))
                .WillByDefault(ReturnRef(*mockPulseCounterBncB));
            ON_CALL(*mockPlatformFactory, getPulseCounterDriver(Driver::PulseCounterId::bncC))
                .WillByDefault(ReturnRef(*mockPulseCounterBncC));
            ON_CALL(*mockPlatformFactory, getPulseCounterDriver(Driver::PulseCounterId::bncD))
                .WillByDefault(ReturnRef(*mockPulseCounterBncD));
            ON_CALL(*mockPlatformFactory, getUartDriver(Driver::UartId::MEASUREMENT_RECEIVER))
                .WillByDefault(ReturnRef(*mockUartMEASUREMENT_RECEIVER));
            ON_CALL(*mockPlatformFactory, getUartDriver(Driver::UartId::TRANSMIT_VIA_WIFI))
                .WillByDefault(ReturnRef(*mockUartWiFi));
            ON_CALL(*mockPlatformFactory, getSdCardDriver())
                .WillByDefault(ReturnRef(*mockSdCardDriver));
            ON_CALL(*mockPlatformFactory, getAmbientLightSensorDriver())
                .WillByDefault(ReturnRef(*mockAmbientLightSensor));
            ON_CALL(*mockPlatformFactory, getDisplayBrightnessDriver())
                .WillByDefault(ReturnRef(*mockDisplayBrightness));
            ON_CALL(*mockPlatformFactory, getDisplayDriver())
                .WillByDefault(ReturnRef(*mockDisplayDriver));
            ON_CALL(*mockPlatformFactory, getKeyboardDriver())
                .WillByDefault(ReturnRef(*mockKeyboardDriver));
        }

        // Getters
        ApplicationBuilder &getBuilder() { return *applicationBuilder; }

    private:
        std::unique_ptr<MockPlatformFactory> mockPlatformFactory;
        std::unique_ptr<MockPulseCounterDriver> mockPulseCounterBncA;
        std::unique_ptr<MockPulseCounterDriver> mockPulseCounterBncB;
        std::unique_ptr<MockPulseCounterDriver> mockPulseCounterBncC;
        std::unique_ptr<MockPulseCounterDriver> mockPulseCounterBncD;
        std::unique_ptr<MockUartDriver> mockUartMEASUREMENT_RECEIVER;
        std::unique_ptr<MockUartDriver> mockUartWiFi;
        std::unique_ptr<MockSdCardDriver> mockSdCardDriver;
        std::unique_ptr<MockAmbientLightSensorDriver> mockAmbientLightSensor;
        std::unique_ptr<MockDisplayBrightnessDriver> mockDisplayBrightness;
        std::unique_ptr<MockDisplayDriver> mockDisplayDriver;
        std::unique_ptr<MockKeyboardDriver> mockKeyboardDriver;
        std::unique_ptr<ApplicationBuilder> applicationBuilder;
    };

    // ============================================================================
    // TESTS
    // ============================================================================

    TEST_F(ApplicationBuilderTest, Constructor_CreatesBuilderSuccessfully)
    {
        EXPECT_NE(&getBuilder(), nullptr);
    }

    TEST_F(ApplicationBuilderTest, Initialize_AllComponentsSucceed_ReturnsTrue)
    {
        bool result = getBuilder().initialize();
        EXPECT_TRUE(result);
    }

    TEST_F(ApplicationBuilderTest, Start_AllComponentsSucceed_ReturnsTrue)
    {
        bool result = getBuilder().start();
        EXPECT_TRUE(result);
    }

    TEST_F(ApplicationBuilderTest, Stop_AlwaysReturnsTrue)
    {
        bool result = getBuilder().stop();
        EXPECT_TRUE(result);
    }

    TEST_F(ApplicationBuilderTest, Tick_AllComponentsSucceed_ReturnsTrue)
    {
        bool result = getBuilder().tick();
        EXPECT_TRUE(result);
    }

} // namespace BusinessLogic