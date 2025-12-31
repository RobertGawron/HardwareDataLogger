#ifndef CobsEncoder_hpp
#define CobsEncoder_hpp

#include <cstddef>
#include <cstdint>
#include <array>
#include <optional>

namespace Device
{
    class CobsEncoder
    {
    private:
        static constexpr std::size_t MAX_COBS_BLOCK_SIZE = 254U;
        static constexpr std::uint8_t COBS_DELIMITER = 0x00U;
        static constexpr std::uint8_t MAX_BLOCK_CODE = 0xFFU;
        static constexpr std::uint8_t INITIAL_CODE = 1U;

    public:
        /**
         * @brief COBS encoding with trailing delimiter byte (0x00)
         *
         * Encodes input data using Consistent Overhead Byte Stuffing (COBS) algorithm.
         * COBS removes all zero bytes from the data stream and adds framing.
         *
         * @tparam INPUT_SIZE Size of input array
         * @tparam OUTPUT_SIZE Size of output array
         * @param input Input data array
         * @param inputLength Number of bytes to encode from input
         * @param output Output data array
         * @return Number of bytes written to output, or std::nullopt on error
         */
        template <std::size_t INPUT_SIZE, std::size_t OUTPUT_SIZE>
        [[nodiscard]] static std::optional<std::size_t> encode(
            const std::array<std::uint8_t, INPUT_SIZE> &input,
            std::size_t inputLength,
            std::array<std::uint8_t, OUTPUT_SIZE> &output)
        {
            std::optional<std::size_t> result = std::nullopt;

            // Validate input length doesn't exceed input array size
            const bool isInputValid = (inputLength <= INPUT_SIZE);

            if (isInputValid)
            {
                // COBS encoding adds at most ceil(inputLength/254) + 1 overhead bytes
                // Plus 1 for the trailing delimiter (0x00)
                const std::size_t requiredSize = inputLength + (inputLength / MAX_COBS_BLOCK_SIZE) + 2U;
                const bool isOutputSufficient = (OUTPUT_SIZE >= requiredSize);

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
            }

            return result;
        }
    };
}

#endif // CobsEncoder_hpp
