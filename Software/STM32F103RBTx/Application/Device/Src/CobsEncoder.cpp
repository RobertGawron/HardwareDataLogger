#include "Device/Inc/CobsEncoder.hpp"

#include <cstddef>
#include <cstdint>

namespace Device
{
    constexpr std::size_t MaxCobsBlockSize = 254;

    // COBS variant that includes a trailing delimiter byte (0x00)
    std::size_t CobsEncoder::encode(const std::uint8_t *input,
                                    std::size_t length,
                                    std::uint8_t *output,
                                    std::size_t maxOutputLength)
    {
        // COBS encoding adds at most ceil(length/254) + 1 overhead bytes
        // Plus 1 for the trailing delimiter (0x00)
        const std::size_t requiredSize = length + (length / MaxCobsBlockSize) + 2;

        if (output == nullptr || input == nullptr)
        {
            return 0; // Invalid pointers
        }

        if (maxOutputLength < requiredSize)
        {
            return 0; // Insufficient output buffer
        }

        std::size_t codeIndex = 0;   // Index of the current code byte
        std::size_t outputIndex = 1; // Start writing data after first code byte
        std::uint8_t code = 1;       // Distance to next zero (or end of block)

        for (std::size_t inputIndex = 0; inputIndex < length; ++inputIndex)
        {
            if (input[inputIndex] == 0)
            {
                // Write the code byte and start a new block
                output[codeIndex] = code;
                codeIndex = outputIndex;
                ++outputIndex;
                code = 1;
            }
            else
            {
                // Copy non-zero byte
                output[outputIndex] = input[inputIndex];
                ++outputIndex;
                ++code;

                // If we've written 254 bytes, start a new block
                if (code == 0xFF)
                {
                    output[codeIndex] = code;
                    codeIndex = outputIndex;
                    ++outputIndex;
                    code = 1;
                }
            }
        }

        // Write the final code byte
        output[codeIndex] = code;

        // Add trailing delimiter (0x00) for framing
        output[outputIndex] = 0x00;
        ++outputIndex;

        return outputIndex;
    }
}