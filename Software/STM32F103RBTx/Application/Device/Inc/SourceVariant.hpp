/**
 * @file SourceVariant.hpp
 * @brief Defines the SourceVariant type for type-safe storage of different recorder types.
 */

#ifndef SOURCE_VARIANT_HPP
#define SOURCE_VARIANT_HPP

#include "Device/Inc/PulseCounterSource.hpp"
#include "Device/Inc/UartSource.hpp"

#include <functional>
#include <variant>

namespace Device
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

} // namespace BusinessLogic

#endif // SOURCE_VARIANT_HPP