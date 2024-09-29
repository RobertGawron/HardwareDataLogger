#ifndef IHmiViewManager_h
#define IHmiViewManager_h

#include "BusinessLogic/Interfaces/IApplicationComponentBuilder.hpp"
#include "Driver/Interfaces/IDisplayDriver.hpp"

namespace BusinessLogic
{
    /**
     * @class IHmiViewManager
     * @brief Manages and controls the HMI views.
     *
     * The IHmiViewManager class defines an interface for managing the display of different views in the HMI system.
     * It handles the logic for switching between views and determining which view should be currently displayed.
     *
     * In the Model-View-Controller (MVC) paradigm, the view manager is responsible for coordinating which view is
     * shown to the user. It typically interacts with the view components and the display driver to ensure the correct
     * visual representation of the application state.
     */
    class IHmiViewManager : public IApplicationComponentBuilder
    {
    public:
        /**
         * @brief Default constructor.
         *
         * Initializes an instance of IHmiViewManager. The default constructor is provided for compatibility and
         * does not perform any specific initialization.
         */
        IHmiViewManager() = default;

        /**
         * @brief Default destructor.
         *
         * Ensures proper cleanup of derived classes. The destructor is virtual to support polymorphic deletion.
         */
        virtual ~IHmiViewManager() = default;

        /**
         * @brief Deleted copy constructor.
         *
         * Prevents copying of IHmiViewManager instances.
         */
        IHmiViewManager(const IHmiViewManager &) = delete;

        /**
         * @brief Deleted assignment operator.
         *
         * Prevents assignment of IHmiViewManager instances.
         * @return IHmiViewManager& Reference to this object.
         */
        IHmiViewManager &operator=(const IHmiViewManager &) = delete;

        virtual bool initialize() = 0;
        virtual bool start() = 0;
        virtual bool stop() = 0;
        virtual bool tick() = 0;
    };
}

#endif // IHmiViewManager_h