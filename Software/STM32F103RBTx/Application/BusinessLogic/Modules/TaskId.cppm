module;

#include <cstdint>

export module BusinessLogic.TaskId;

export namespace BusinessLogic
{
    enum class TaskId : std::uint8_t
    {
        MEASUREMENT = 0,
        KEYBOARD = 1,
        LAST_NOT_USED = 2
    };
}