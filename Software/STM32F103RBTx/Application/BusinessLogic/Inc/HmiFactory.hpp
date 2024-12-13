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

        HmiFactory(const HmiFactory &) = delete;

        HmiFactory &operator=(const HmiFactory &) = delete;

        virtual bool initialize() override;

        virtual bool start() override;

        virtual bool tick() override;

    private:
        HmiMui hmi;
        Device::Display display;
        Device::Keyboard keyboard;
        Device::DisplayBrightnessRegulator brightnessRegulator;
    };
}

#endif // HmiFactory_h