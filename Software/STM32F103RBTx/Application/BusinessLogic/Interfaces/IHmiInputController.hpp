#ifndef IHmiInputController_h
#define IHmiInputController_h

#include "BusinessLogic/Interfaces/IApplicationComponentBuilder.hpp"
namespace BusinessLogic
{
    /**
     * @class IHmiInputController
     * @brief Interface for handling user input within the HMI system.
     *
     * The IHmiInputController interface defines the responsibilities of the input controller in the HMI system.
     * It handles user interactions, such as pressing keys, and is responsible for processing these inputs and
     * notifying the view when new data is available to display.
     *
     * In the Model-View-Controller (MVC) design pattern, the input controller acts as the "controller" component.
     * It manages user input and communicates changes to the view, which in turn updates the display based on the
     * latest data. The input controller ensures that user actions are correctly interpreted and handled.
     */
    class IHmiInputController : public IApplicationComponentBuilder
    {
    public:
        /**
         * @brief Default constructor.
         *
         * Initializes a new instance of the IHmiInputController interface.
         */
        IHmiInputController() = default;

        /**
         * @brief Default destructor.
         *
         * Ensures proper cleanup of derived classes. The destructor is defaulted and does not perform any specific
         * cleanup operations.
         */
        virtual ~IHmiInputController() = default;

        /**
         * @brief Deleted copy constructor.
         *
         * Prevents copying of IHmiInputController instances.
         */
        IHmiInputController(const IHmiInputController &) = delete;

        /**
         * @brief Deleted assignment operator.
         *
         * Prevents assignment of IHmiInputController instances.
         * @return IHmiInputController& Reference to this object.
         */
        IHmiInputController &operator=(const IHmiInputController &) = delete;

        virtual bool initialize() = 0;
        virtual bool start() = 0;
        virtual bool stop() = 0;
        virtual bool tick() = 0;
    };
}

#endif // IHmiInputController_h