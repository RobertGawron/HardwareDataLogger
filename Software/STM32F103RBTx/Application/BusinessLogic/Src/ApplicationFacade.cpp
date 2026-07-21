module;

#include <array>
#include <cstddef>
#include <functional>
#include <utility>

module BusinessLogic.ApplicationFacade;

import BusinessLogic.ApplicationComponent;
import BusinessLogic.MeasurementCoordinator;
import BusinessLogic.SlotTableScheduler;
import BusinessLogic.TaskId;
import BusinessLogic.TickDelegate;

import Device;

import Driver.PlatformFactory;

namespace BusinessLogic
{
    static_assert(std::to_underlying(TaskId::MEASUREMENT) == 0U,
                  "TaskId is used as an index into TaskCallTable, MEASUREMENT must map to index 0.");

    static_assert(std::to_underlying(TaskId::KEYBOARD) == 1U,
                  "TaskId is used as an index into TaskCallTable, KEYBOARD must map to index 1.");

    static_assert(std::to_underlying(TaskId::LAST_NOT_USED) == 2U,
                  "LAST_NOT_USED must equal the number of valid TaskId entries (TaskCallTable size).");

    ApplicationFacade::ApplicationFacade(Driver::PlatformFactory &drivers) noexcept
        : measurementSubsystem{drivers},

          display{drivers.display},
          brightness{drivers.lightSensor, drivers.displayBrightness},
          keyboard{drivers.keyboard},

          taskCallTable{TickDelegate(measurementSubsystem),
                        TickDelegate(keyboard)},

          scheduler{Scheduler::Config{slotTable, taskCallTable, 2U}}
    {
        static_assert(taskCallTable.size() == std::to_underlying(TaskId::LAST_NOT_USED),
                      "TaskCallTable size must match the number of TaskId entries.");

        static_assert(Scheduler::validateSlotTable(slotTable),
                      "slotTable is invalid: taskIdCount exceeds maxTasksPerSlot and/or contains invalid TaskId values.");
    }

    auto ApplicationFacade::onInit() noexcept -> bool
    {
        const bool statusMeasurement = measurementSubsystem.init();
        const bool statusDisplay = display.init();
        const bool statusBrightness = brightness.init();
        const bool statusKeyboard = keyboard.init();

        const bool status = (statusMeasurement &&
                             statusDisplay &&
                             statusBrightness &&
                             statusKeyboard);

        return status;
    }

    auto ApplicationFacade::onStart() noexcept -> bool
    {
        const bool statusMeasurement = measurementSubsystem.start();
        const bool statusDisplay = display.start();
        const bool statusBrightness = brightness.start();
        const bool statusKeyboard = keyboard.start();
        const bool statusScheduler = scheduler.start();

        const bool status = (statusMeasurement &&
                             statusDisplay &&
                             statusBrightness &&
                             statusKeyboard &&
                             statusScheduler);

        //        return status;
        return true;
    }

    auto ApplicationFacade::onStop() noexcept -> bool
    {
        const bool statusMeasurement = measurementSubsystem.stop();
        const bool statusDisplay = display.stop();
        const bool statusBrightness = brightness.stop();
        const bool statusKeyboard = keyboard.stop();

        const bool status = (statusMeasurement &&
                             statusDisplay &&
                             statusBrightness &&
                             statusKeyboard);
        return status;
    }

    auto ApplicationFacade::onTick() noexcept -> bool
    {
        const bool result = scheduler.runPending();
        return result;
    }

    auto ApplicationFacade::onTimeSlot() noexcept -> void
    {
        scheduler.notifyTimeSlotIsr();
    }

} // namespace BusinessLogic