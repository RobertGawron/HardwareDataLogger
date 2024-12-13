#ifndef PulseCounterIdentifier_h
#define PulseCounterIdentifier_h

#include <stdint.h>

namespace Driver
{

    /**
     * @enum PulseCounterIdentifier
     * @brief Enum class to identify the pulse counters connected to the BNC connectors.
     *
     * This enum is used to specify which pulse counter corresponds to which BNC connector.
     */
    enum class PulseCounterIdentifier : uint8_t
    {
        /**
         * @brief Pulse counter from the first BNC connector.
         */
        bncA = 0u,

        /**
         * @brief Pulse counter from the second BNC connector.
         */
        bncB = 1u,

        /**
         * @brief Pulse counter from the third BNC connector.
         */
        bncC = 2u,

        /**
         * @brief Pulse counter from the fourth BNC connector.
         */
        bncD = 3u,

        /**
         * @brief Used to calculate the size of the enum. Not used in logic.
         */
        LastNotUsed = 4u
    };

}

#endif // PulseCounterIdentifier_h