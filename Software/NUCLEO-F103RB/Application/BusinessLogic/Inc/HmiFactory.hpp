#ifndef HmiFactory_h
#define HmiFactory_h

#include "BusinessLogic/Interfaces/IHmiFactory.hpp"
#include "BusinessLogic/Interfaces/IPlatformFactory.hpp"

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
        /**
         * @brief Gets the data model component.
         *
         * Provides access to the IHmiDataModel instance used in the HMI system.
         *
         * @return Reference to the IHmiDataModel instance.
         */
        virtual IHmiDataModel &getDataModel() override;

        /**
         * @brief Gets the input controller component.
         *
         * Provides access to the IHmiInputController instance used in the HMI system.
         *
         * @return Reference to the IHmiInputController instance.
         */
        virtual IHmiInputController &getInputController() override;

        /**
         * @brief Gets the view manager component.
         *
         * Provides access to the IHmiViewManager instance used in the HMI system.
         *
         * @return Reference to the IHmiViewManager instance.
         */
        virtual IHmiViewManager &getHmiViewManager() override;

    protected:
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

    private:
        IPlatformFactory &platformFactory; /**< Reference to the platform factory used for creating platform-specific components. */
    };
}

#endif // HmiFactory_h