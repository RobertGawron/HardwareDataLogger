/**
 * @file SourceVariant.cppm
 * @brief Defines the SourceVariant type for type-safe storage of different recorder types.
 */
module;

#include <functional>
#include <variant>

export module Device.SourceVariant;

import Device.PulseCounterSource;
import Device.UartSource;

export namespace Device
{
    /**
     * @brief Type-safe variant that can hold references to any recorder type.
     *
     * This allows storing different recorder types in a single container
     * without runtime polymorphism overhead (no vtables).
     */
    using SourceVariant = std::variant<
        std::reference_wrapper<Device::PulseCounterSource>,
        std::reference_wrapper<Device::UartSource>>;

} // namespace Device