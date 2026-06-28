/**
 * @file RecorderVariant.cppm
 * @brief Defines the RecorderVariant type for type-safe storage of different recorder types.
 */
module;

#include <functional>
#include <variant>

export module Device.RecorderVariant;

import Device.WiFiRecorder;
import Device.SdCardRecorder;

export namespace Device
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

} // namespace Device