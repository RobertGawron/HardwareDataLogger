#ifndef IHmiFactory_h
#define IHmiFactory_h

#include "IKeyboard.hpp"
#include "IDisplayDriver.hpp"
#include "IDisplayBrightnessRegulator.hpp"
#include "IHmiDataModel.hpp"
#include "IHmiInputController.hpp"
#include "IHmiViewManager.hpp"

namespace BusinessLogic
{
    /**
     * @class IHmiFactory
     * @brief Interface for creating HMI-related components.
     *
     * The IHmiFactory interface defines methods for creating and retrieving various HMI-related components,
     * including the data model, input controller, and view manager. It serves as a factory for providing
     * these components, which are essential for the operation of the HMI system.
     *
     * In the context of the Model-View-Controller (MVC) design pattern, the factory provides the necessary
     * components to assemble and manage the MVC structure. The data model, view manager, and input controller
     * are integral parts of the HMI, and the factory ensures their proper instantiation and integration.
     */
    class IHmiFactory
    {
    public:
        /**
         * @brief Default constructor.
         *
         * Initializes a new instance of the IHmiFactory interface.
         */
        IHmiFactory() = default;

        /**
         * @brief Virtual destructor.
         *
         * Ensures proper cleanup of derived classes.
         */
        virtual ~IHmiFactory() = default;

        /**
         * @brief Retrieves the data model.
         *
         * This method returns a reference to the data model component of the HMI system. The data model
         * is responsible for managing and storing application data.
         *
         * @return IHmiDataModel& Reference to the data model.
         */
        virtual IHmiDataModel &getDataModel() = 0;

        /**
         * @brief Retrieves the input controller.
         *
         * This method returns a reference to the input controller component of the HMI system. The input
         * controller handles user interactions and communicates with the view to update its state.
         *
         * @return IHmiInputController& Reference to the input controller.
         */
        virtual IHmiInputController &getInputController() = 0;

        /**
         * @brief Retrieves the view manager.
         *
         * This method returns a reference to the view manager component of the HMI system. The view manager
         * is responsible for managing and switching between different views.
         *
         * @return IHmiViewManager& Reference to the view manager.
         */
        virtual IHmiViewManager &getHmiViewManager() = 0;

    protected:
        /**
         * @brief Retrieves the display driver.
         *
         * This method returns a reference to the display driver. The display driver is responsible for rendering
         * graphical content on the display.
         *
         * @return Driver::IDisplayDriver& Reference to the display driver.
         */
        virtual Driver::IDisplayDriver &getDisplay() = 0;

        /**
         * @brief Retrieves the display brightness regulator.
         *
         * This method returns a reference to the display brightness regulator. The brightness regulator manages
         * the brightness settings of the display.
         *
         * @return Device::IDisplayBrightnessRegulator& Reference to the display brightness regulator.
         */
        virtual Device::IDisplayBrightnessRegulator &getDisplayBrightnessRegulator() = 0;

        /**
         * @brief Retrieves the keyboard.
         *
         * This method returns a reference to the keyboard component. The keyboard component is responsible for
         * handling keyboard input.
         *
         * @return Device::IKeyboard& Reference to the keyboard.
         */
        virtual Device::IKeyboard &getKeyboard() = 0;
    };
}

#endif // IHmiFactory_h