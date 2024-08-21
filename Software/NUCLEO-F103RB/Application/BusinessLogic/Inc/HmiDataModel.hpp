#ifndef HmiDataModel_h
#define HmiDataModel_h

#include <cstdint>
#include "IHmiDataModel.hpp"
#include "DisplayBrightnessRegulator.hpp"

namespace BusinessLogic
{
    /**
     * @class HmiDataModel
     * @brief The data model class for managing application data in the HMI system.
     *
     * The HmiDataModel class represents the "Model" component in the Model-View-Controller (MVC) paradigm.
     * It encapsulates the application data and business logic, providing methods to access and manipulate
     * this data. The data model is responsible for maintaining the state of the application and notifying
     * the view when changes occur.
     *
     * In MVC, the data model serves as the central component that interacts with the data and business rules.
     * It is independent of the user interface and provides a way to update and retrieve data as needed by
     * the view and controller.
     */
    class HmiDataModel : public IHmiDataModel
    {
    public:
        HmiDataModel(Device::DisplayBrightnessRegulator &brightnessRegulator);

        HmiDataModel() = delete;

        /**
         * @brief Default destructor for HmiDataModel.
         */
        virtual ~HmiDataModel() = default;

        /**
         * @brief Deleted copy constructor for HmiDataModel.
         *
         * Prevents copying of HmiDataModel instances.
         */
        HmiDataModel(const HmiDataModel &) = delete;

        /**
         * @brief Deleted assignment operator for HmiDataModel.
         *
         * Prevents assignment of HmiDataModel instances.
         * @return HmiDataModel& Reference to this object.
         */
        HmiDataModel &operator=(const HmiDataModel &) = delete;

        virtual bool initialize() override;
        virtual bool start() override;
        virtual bool stop() override;
        virtual bool tick() override;

    private:
        Device::DisplayBrightnessRegulator &brightnessRegulator;
    };

}

#endif // HmiDataModel_h