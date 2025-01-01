#include "CobsEncoder.hpp"
#include <cstdint>

namespace Device
{
    std::size_t CobsEncoder::encode(const std::uint8_t *input,
                                    std::size_t length,
                                    std::uint8_t *output,
                                    std::size_t maxOutputLength)
    {
        if (input == nullptr || output == nullptr || length == 0 || maxOutputLength < length + 1)
        {
            return 0; // Invalid input or insufficient output buffer size
        }

        std::size_t writeIndex = 0; // Position to write in the output
        std::size_t readIndex = 0;  // Position to read in the input
        std::size_t codeIndex = 0;  // Position of the code byte in the output
        std::uint8_t code = 1;      // Initialize the code byte

        output[writeIndex++] = 0; // Placeholder for the code byte

        while (readIndex < length)
        {
            if (input[readIndex] == 0)
            {
                // Write the code byte to its position
                output[codeIndex] = code;

                // Update the code byte's position and reset code
                codeIndex = writeIndex++;
                code = 1;
            }
            else
            {
                // Copy non-zero byte to the output
                output[writeIndex++] = input[readIndex];
                code++;

                // If code reaches the max value (255), write it and reset
                if (code == 0xFF)
                {
                    output[codeIndex] = code;
                    codeIndex = writeIndex++;
                    code = 1;
                }
            }

            readIndex++;
        }

        // Write the final code byte
        output[codeIndex] = code;

        // Return the total number of bytes written
        return writeIndex;
    }

    std::size_t CobsEncoder::decode(const uint8_t *input, std::size_t length,
                                    uint8_t *output, std::size_t maxOutputLength)
    {
        if (input == nullptr || output == nullptr || length == 0 || maxOutputLength < length - 1)
        {
            return 0; // Invalid input or insufficient output buffer size
        }

        std::size_t readIndex = 0;  // Position to read in the input
        std::size_t writeIndex = 0; // Position to write in the output

        while (readIndex < length)
        {
            std::uint8_t code = input[readIndex++];

            if (code == 0 || readIndex + code - 1 > length)
            {
                return 0; // Malformed input
            }

            for (std::uint8_t i = 1; i < code; ++i)
            {
                if (writeIndex >= maxOutputLength)
                {
                    return 0; // Output buffer overflow
                }

                output[writeIndex++] = input[readIndex++];
            }

            if (code < 0xFF && writeIndex < maxOutputLength)
            {
                // Insert a zero if the code is less than 0xFF
                output[writeIndex++] = 0;
            }
        }

        // Return the total number of bytes written
        return writeIndex;
    }
}
