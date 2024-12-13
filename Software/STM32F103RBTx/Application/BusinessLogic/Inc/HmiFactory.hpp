#ifndef HmiFactory_h
#define HmiFactory_h

#include "BusinessLogic/Interfaces/IPlatformFactory.hpp"
#include "BusinessLogic/Interfaces/IHmiFactory.hpp"

#include "BusinessLogic/Inc/HmiMui.hpp"
#include "Device/Inc/Display.hpp"
#include "Device/Inc/Keyboard.hpp"

// #include "BusinessLogic/Interfaces/IHmi.hpp"

namespace BusinessLogic
{
    /**
     * @class HmiFactory
     * @brief Factory class for creating HMI-related objects.
     *
     * The HmiFactory class is responsible for creating all Human-Machine Interface (HMI) related components.
     * It collaborates with the HmiBuilder to construct and provide instances of various components required
     * for the HMI system. This includes components such as data models, input controllers, view managers,
     * and platform-specific drivers.
     *
     * The factory pattern is used to centralize the creation logic of these components and manage their
     * lifecycle. This class is an implementation of the IHmiFactory interface and provides high-level methods
     * for obtaining the required components.
     */
    class HmiFactory : public IHmiFactory
    {
    public:
        /**
         * @brief Constructs an HmiFactory instance.
         *
         * @param platformFactory Reference to an IPlatformFactory instance used for creating platform-specific
         *                        components and drivers.
         */
        HmiFactory(IPlatformFactory &platformFactory);

        /**
         * @brief Deleted default constructor.
         *
         * Prevents the creation of HmiFactory instances without a platformFactory.
         */
        HmiFactory() = delete;
        virtual ~HmiFactory() = default;

        virtual bool initialize() override;

        virtual bool start() override;

        virtual bool tick() override;

    private:
#if 0 
        /**
         * @brief Gets the display driver component.
         *
         * Provides access to the Driver::IDisplayDriver instance used for interacting with the display hardware.
         *
         * @return Reference to the Driver::IDisplayDriver instance.
         */
        virtual Driver::IDisplayDriver &getDisplay() override;

        /**
         * @brief Gets the display brightness regulator component.
         *
         * Provides access to the Device::IDisplayBrightnessRegulator instance used for managing the display's
         * brightness settings.
         *
         * @return Reference to the Device::IDisplayBrightnessRegulator instance.
         */
        virtual Device::IDisplayBrightnessRegulator &getDisplayBrightnessRegulator() override;

        /**
         * @brief Gets the keyboard component.
         *
         * Provides access to the Device::IKeyboard instance used for handling keyboard input.
         *
         * @return Reference to the Device::IKeyboard instance.
         */
        virtual Device::IKeyboard &getKeyboard() override;
#endif
        HmiMui hmi;
        Device::Display display;
        Device::Keyboard keyboard;
        Device::DisplayBrightnessRegulator brightnessRegulator;
        // IPlatformFactory &platformFactory; /**< Reference to the platform factory used for creating platform-specific components. */
    };
}

#endif // HmiFactory_h