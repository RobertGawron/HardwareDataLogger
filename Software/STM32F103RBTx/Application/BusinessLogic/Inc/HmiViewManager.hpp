#ifndef HmiViewManager_h
#define HmiViewManager_h

#include "BusinessLogic/Interfaces/IHmiViewManager.hpp"
#include "Driver/Interfaces/IDisplayDriver.hpp"

namespace BusinessLogic
{
    /**
     * @class HmiViewManager
     * @brief Manages and displays different views in the HMI system.
     *
     * The HmiViewManager class is responsible for managing the current view and handling the transition between
     * different views within the HMI system. It interacts with the display driver to render the appropriate view
     * on the screen.
     *
     * In the Model-View-Controller (MVC) design pattern, the view is responsible for presenting data to the user.
     * It handles the visual representation and user interface aspects of the application. The view updates
     * based on changes in the model and provides a way for users to interact with the application. The view
     * itself does not handle data or business logic but relies on the controller to manage these aspects.
     */
    class HmiViewManager : public IHmiViewManager
    {
    public:
        /**
         * @brief Constructs an HmiViewManager instance.
         *
         * @param display Reference to a Driver::IDisplayDriver instance used for rendering views.
         */
        HmiViewManager(Driver::IDisplayDriver &display);

        /**
         * @brief Deleted default constructor.
         *
         * Prevents the creation of HmiViewManager instances without a display driver.
         */
        HmiViewManager() = delete;

        /**
         * @brief Default destructor.
         *
         * The destructor is defaulted and ensures proper cleanup of any resources, though no specific resources
         * are managed by this default implementation.
         */
        virtual ~HmiViewManager() = default;

        /**
         * @brief Deleted copy constructor.
         *
         * Prevents copying of HmiViewManager instances.
         */
        HmiViewManager(const HmiViewManager &) = delete;

        /**
         * @brief Deleted assignment operator.
         *
         * Prevents assignment of HmiViewManager instances.
         * @return HmiViewManager& Reference to this object.
         */
        HmiViewManager &operator=(const HmiViewManager &) = delete;

        virtual bool initialize() override;
        virtual bool start() override;
        virtual bool stop() override;
        virtual bool tick() override;

    protected:
        // we dont have a "device" clas for it because the lib used is a mix of "device" and "driver"
        Driver::IDisplayDriver &display;
    };
}

#endif // HmiViewManager_h