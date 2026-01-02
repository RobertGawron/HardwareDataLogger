/**
 * @file RecorderVariant.hpp
 * @brief Defines the RecorderVariant type for type-safe storage of different recorder types.
 */

#ifndef RECORDER_VARIANT_HPP
#define RECORDER_VARIANT_HPP

#include "Device/Inc/WiFiRecorder.hpp"
#include "Device/Inc/SdCardRecorder.hpp"

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
    using RecorderVariant = std::variant<
        std::reference_wrapper<Device::WiFiRecorder>,
        std::reference_wrapper<Device::SdCardRecorder>>;

} // namespace BusinessLogic

#endif // RECORDER_VARIANT_HPP