#ifndef IHmiView_h
#define IHmiView_h

#include "BusinessLogic/Inc/HmiDataModel.hpp"
#include "Driver/Interfaces/IDisplayDriver.hpp"

namespace BusinessLogic
{
    /**
     * @class IHmiView
     * @brief Abstract base class for all HMI views.
     *
     * The IHmiView class defines a common interface for all views (layouts) in the HMI system.
     * It provides methods for updating the display and initializing the view. Concrete implementations
     * of this class represent different visual layouts or screens that are presented to the user.
     *
     * In the Model-View-Controller (MVC) paradigm, the view is responsible for rendering data from
     * the model onto the display. It receives updates from the controller and presents the data in a
     * user-friendly manner.
     */
    class IHmiView
    {
    public:
        IHmiView() = default;
        /**
         * @brief Virtual destructor.
         *
         * Ensures proper cleanup of derived classes. The destructor is virtual to support polymorphic deletion.
         */
        virtual ~IHmiView() = default;

        /**
         * @brief Updates the display with the latest data from the model.
         *
         * This method is called to refresh the view based on the current state of the data model.
         *
         * @param model The data model containing the information to be displayed.
         */
        virtual void updateDisplay(const HmiDataModel &model) = 0;

        /**
         * @brief Initializes the view.
         *
         * This method sets up the view and prepares it for rendering data. It is typically called
         * before the view is first displayed.
         */
        virtual void init() = 0;
    };

}

#endif // IHmiView_h