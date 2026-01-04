module;

#include <cstdint>

export module Driver.PulseCounterId;

export namespace Driver
{

    /**
     * @enum PulseCounterId
     * @brief Enum class to identify the pulse counters connected to the BNC connectors.
     *
     * This enum is used to specify which pulse counter corresponds to which BNC connector.
     */
    enum class PulseCounterId : std::uint8_t
    {
        /**
         * @brief Pulse counter from the first BNC connector.
         */
        bncA = 0U,

        /**
         * @brief Pulse counter from the second BNC connector.
         */
        bncB = 1U,

        /**
         * @brief Pulse counter from the third BNC connector.
         */
        bncC = 2U,

        /**
         * @brief Pulse counter from the fourth BNC connector.
         */
        bncD = 3U,

        /**
         * @brief Used to calculate the size of the enum. Not used in logic.
         */
        LastNotUsed = 4U
    };

}