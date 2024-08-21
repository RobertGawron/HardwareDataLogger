#ifndef HmiInputController_h
#define HmiInputController_h

#include "IHmiInputController.hpp"
#include "IKeyboard.hpp"

namespace BusinessLogic
{
    /**
     * @class HmiInputController
     * @brief Handles user interaction and input for the HMI system.
     *
     * The HmiInputController class is responsible for managing user input, such as key presses, and
     * notifying the view when new data is available for display. It acts as the controller in the Model-View-Controller
     * (MVC) paradigm, coordinating between the user input and the view.
     *
     * In the MVC design pattern, the controller is responsible for handling user input, updating the model, and
     * triggering updates to the view. It ensures that user interactions are appropriately processed and communicated
     * to the other components of the HMI system.
     */
    class HmiInputController : public IHmiInputController
    {
    public:
        /**
         * @brief Constructs an HmiInputController instance.
         *
         * @param keyboard Reference to a Device::IKeyboard instance used to receive user input.
         */
        HmiInputController(Device::IKeyboard &keyboard);

        /**
         * @brief Deleted default constructor.
         *
         * Prevents the creation of HmiInputController instances without a keyboard.
         */
        HmiInputController() = delete;

        /**
         * @brief Default destructor.
         *
         * The destructor is defaulted and ensures proper cleanup of any resources, though no specific resources
         * are managed by this default implementation.
         */
        virtual ~HmiInputController() = default;

        /**
         * @brief Deleted copy constructor.
         *
         * Prevents copying of HmiInputController instances.
         */
        HmiInputController(const HmiInputController &) = delete;

        /**
         * @brief Deleted assignment operator.
         *
         * Prevents assignment of HmiInputController instances.
         * @return HmiInputController& Reference to this object.
         */
        HmiInputController &operator=(const HmiInputController &) = delete;
        virtual bool initialize() override;
        virtual bool start() override;
        virtual bool stop() override;
        virtual bool tick() override;

    private:
        Device::IKeyboard &keyboard; /**< Reference to the keyboard instance used for handling user input. */
    };

}

#endif // HmiInputController_h