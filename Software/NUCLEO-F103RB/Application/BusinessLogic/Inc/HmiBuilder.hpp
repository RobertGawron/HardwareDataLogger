/**
 * @file HmiBuilder.hpp
 * @brief Defines the HmiBuilder class responsible for building and managing all HMI-related objects.
 */

#ifndef HmiBuilder_h
#define HmiBuilder_h

#include "BusinessLogic/Interfaces/IApplicationComponentBuilder.hpp"
#include "BusinessLogic/Interfaces/IHmiInputController.hpp"
#include "BusinessLogic/Interfaces/IHmiViewManager.hpp"
#include "BusinessLogic/Interfaces/IHmiFactory.hpp"

namespace BusinessLogic
{
    /**
     * @class HmiBuilder
     * @brief Responsible for building and handling all HMI-related objects (HMI, display, display backlight, keyboard).
     *
     * The HmiBuilder class constructs and manages all Human-Machine Interface (HMI) related components.
     * It uses platform-specific drivers (for display, brightness, keyboard, etc.) to create high-level HMI
     * abstractions and components. It relies on the drivers and devices provided by the HMI Factory.
     */
    class HmiBuilder : public IApplicationComponentBuilder
    {
    public:
        /**
         * @brief Constructs an HmiBuilder instance.
         *
         * Initializes the HmiBuilder with the provided HMI factory, which is used to obtain necessary
         * components for building the HMI.
         *
         * @param hmiFactory Reference to an IHmiFactory instance used to create HMI components.
         */
        explicit HmiBuilder(IHmiFactory &hmiFactory);

        /**
         * @brief Default destructor.
         *
         * The destructor is defaulted and ensures proper cleanup of any resources, though no specific resources
         * are managed by this default implementation.
         */
        virtual ~HmiBuilder() = default;

        /**
         * @brief Deleted copy constructor.
         *
         * Prevents copying of HmiBuilder instances to ensure that each instance is unique.
         */
        HmiBuilder(const HmiBuilder &) = delete;

        /**
         * @brief Deleted assignment operator.
         *
         * Prevents assignment of HmiBuilder instances to maintain unique object instances.
         * @return HmiBuilder& Reference to this object.
         */
        HmiBuilder &operator=(const HmiBuilder &) = delete;

        /**
         * @brief Initializes all HMI components.
         *
         * Performs setup and initialization of all HMI components managed by this builder.
         * Typically includes tasks like configuring and preparing components for use.
         *
         * @return true if initialization was successful, false otherwise.
         */
        virtual bool initialize() override;

        /**
         * @brief Starts all HMI components.
         *
         * Activates the HMI components and prepares them for operational use.
         * This may involve starting processes, enabling features, or other startup tasks.
         *
         * @return true if components started successfully, false otherwise.
         */
        virtual bool start() override;

        /**
         * @brief Stops all HMI components.
         *
         * Deactivates and halts the operation of HMI components.
         * This method ensures that all components are properly stopped and are no longer active.
         *
         * @return true if components stopped successfully, false otherwise.
         */
        virtual bool stop() override;

        /**
         * @brief Ticks the HMI components for periodic updates.
         *
         * Provides periodic updates to the HMI components.
         * This method is typically called in a regular update cycle to ensure that components are kept up-to-date.
         *
         * @return true if the tick operation was successful, false otherwise.
         */
        virtual bool tick() override;

    private:
        /**
         * @brief Reference to the IHmiDataModel instance used by this builder.
         *
         * The data model represents the underlying data structure of the HMI. It manages and provides
         * access to the data that the HMI components work with, ensuring consistency and integrity.
         */
        IHmiDataModel &hmiDataModel;

        /**
         * @brief Reference to the IHmiInputController instance used by this builder.
         *
         * The input controller handles user inputs and interactions with the HMI. It processes inputs and
         * translates them into actions or commands for the HMI system.
         */
        IHmiInputController &hmiInputController;

        /**
         * @brief Reference to the IHmiViewManager instance used by this builder.
         *
         * The view manager is responsible for managing and rendering the visual representation of the HMI.
         * It controls how data is presented to the user and manages the user interface elements.
         */
        IHmiViewManager &hmiViewManager;
    };
}

#endif // HmiBuilder_h