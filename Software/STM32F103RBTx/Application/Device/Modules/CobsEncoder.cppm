module;

#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>

export module Device.CobsEncoder;

export namespace Device
{
    class CobsEncoder final
    {
    public:
        /**
         * @brief COBS encoding with trailing delimiter byte (0x00)
         *
         * Encodes input data using Consistent Overhead Byte Stuffing (COBS) algorithm.
         * COBS removes all zero bytes from the data stream and adds framing.
         *
         * @param input Input data span
         * @param output Output data span (must be large enough for encoded data)
         * @return Number of bytes written to output, or std::nullopt on error
         */
        [[nodiscard]] static constexpr std::optional<std::size_t> encode(
            std::span<const std::uint8_t> input,
            std::span<std::uint8_t> output) noexcept
        {
            std::optional<std::size_t> result = std::nullopt;
            const std::size_t inputLength = input.size();

            // COBS encoding adds at most ceil(inputLength/254) + 1 overhead bytes
            // Plus 1 for the trailing delimiter (0x00)
            const std::size_t requiredSize = inputLength + (inputLength / MAX_COBS_BLOCK_SIZE) + 2U;
            const bool isOutputSufficient = (output.size() >= requiredSize);

            if (isOutputSufficient)
            {
                std::size_t codeIndex = 0U;       // Index of the current code byte
                std::size_t outputIndex = 1U;     // Start writing data after first code byte
                std::uint8_t code = INITIAL_CODE; // Distance to next zero (or end of block)

                for (std::size_t inputIndex = 0U; inputIndex < inputLength; ++inputIndex)
                {
                    const std::uint8_t currentByte = input[inputIndex];

                    if (currentByte == COBS_DELIMITER)
                    {
                        // Write the code byte and start a new block
                        output[codeIndex] = code;
                        codeIndex = outputIndex;
                        ++outputIndex;
                        code = INITIAL_CODE;
                    }
                    else
                    {
                        // Copy non-zero byte
                        output[outputIndex] = currentByte;
                        ++outputIndex;
                        ++code;

                        // If we've written 254 bytes, start a new block
                        if (code == MAX_BLOCK_CODE)
                        {
                            output[codeIndex] = code;
                            codeIndex = outputIndex;
                            ++outputIndex;
                            code = INITIAL_CODE;
                        }
                    }
                }

                // Write the final code byte
                output[codeIndex] = code;

                // Add trailing delimiter (0x00) for framing
                output[outputIndex] = COBS_DELIMITER;
                ++outputIndex;

                result = outputIndex;
            }

            return result;
        }

        /**
         * @brief Calculates the maximum size needed for COBS-encoded output.
         *
         * @param inputSize Size of the input data
         * @return Maximum size needed for encoded output (including delimiter)
         */
        [[nodiscard]] static constexpr std::size_t getMaxEncodedSize(const std::size_t inputSize) noexcept
        {
            return inputSize + (inputSize / MAX_COBS_BLOCK_SIZE) + 2U;
        }

        CobsEncoder() = delete;
        ~CobsEncoder() = delete;
        CobsEncoder(const CobsEncoder &) = delete;
        CobsEncoder &operator=(const CobsEncoder &) = delete;
        CobsEncoder(CobsEncoder &&) = delete;
        CobsEncoder &operator=(CobsEncoder &&) = delete;

    private:
        static constexpr std::size_t MAX_COBS_BLOCK_SIZE = 254U;
        static constexpr std::uint8_t COBS_DELIMITER = 0x00U;
        static constexpr std::uint8_t MAX_BLOCK_CODE = 0xFFU;
        static constexpr std::uint8_t INITIAL_CODE = 1U;
    };
}