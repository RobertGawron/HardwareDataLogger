#ifndef IHmiDataModel_h
#define IHmiDataModel_h

#include "BusinessLogic/Interfaces/IApplicationComponentBuilder.hpp"

#include <cstdint>

namespace BusinessLogic
{
    /**
     * @class IHmiDataModel
     * @brief Interface for the data model in the HMI system.
     *
     * The IHmiDataModel class serves as the interface for the data model component of the HMI system. The data model
     * is responsible for managing and storing the application data. It provides the data needed by the view and
     * updates the view when the data changes.
     *
     * In the Model-View-Controller (MVC) design pattern, the model is the component that handles the data and
     * business logic of the application. It manages the data, responds to requests for information, and notifies
     * the view when data changes. The model does not handle any user interface concerns but provides the data
     * needed for the view to present to the user.
     */
    class IHmiDataModel : public IApplicationComponentBuilder
    {
    public:
        IHmiDataModel() = default;

        /**
         * @brief Default destructor.
         *
         * The destructor is defaulted and ensures proper cleanup of any resources, though no specific resources
         * are managed by this default implementation.
         */
        virtual ~IHmiDataModel() = default;

        /**
         * @brief Deleted copy constructor.
         *
         * Prevents copying of IHmiDataModel instances.
         */
        IHmiDataModel(const IHmiDataModel &) = delete;

        /**
         * @brief Deleted assignment operator.
         *
         * Prevents assignment of IHmiDataModel instances.
         * @return IHmiDataModel& Reference to this object.
         */
        IHmiDataModel &operator=(const IHmiDataModel &) = delete;

        virtual bool initialize() = 0;
        virtual bool start() = 0;
        virtual bool stop() = 0;
        virtual bool tick() = 0;
    };
}

#endif
