#include "CobsEncoder.hpp"

#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace Device
{
    constexpr std::size_t MaxCobsBlockSize = 254;

    std::size_t CobsEncoder::encode(const std::uint8_t *input,
                                    std::size_t length,
                                    std::uint8_t *output,
                                    std::size_t maxOutputLength)
    {
        // Handle empty input separately
        if (length == 0)
        {
            if (maxOutputLength < 1)
                return 0;
            output[0] = 0x00;
            return 1;
        }

        // Calculate required buffer size
        std::size_t breaks = 0;
        for (std::size_t i = 0; i < length;)
        {
            // Find next zero or max block
            std::size_t chunk = 0;
            while (i + chunk < length && chunk < MaxCobsBlockSize && input[i + chunk] != 0)
            {
                ++chunk;
            }
            ++breaks;
            // Skip zero if found
            i += chunk + (i + chunk < length && input[i + chunk] == 0 ? 1 : 0);
        }

        const std::size_t required_length = length + breaks + 1;

        // Check buffer size
        if (maxOutputLength < required_length)
        {
            return 0;
        }

        // Initialize pointers
        uint8_t *out = output;
        uint8_t *code_ptr = out++; // First overhead byte position
        uint8_t code = 1;          // Current block length

        // Process input
        for (std::size_t i = 0; i < length; ++i)
        {
            if (input[i] == 0)
            {
                // Terminate current block
                *code_ptr = code;
                code_ptr = out++;
                code = 1;
            }
            else
            {
                // Copy non-zero byte
                *out++ = input[i];
                if (++code == 0xFF)
                {
                    // Terminate at max block size
                    *code_ptr = code;
                    code_ptr = out++;
                    code = 1;
                }
            }
        }

        // Finalize last block and add delimiter
        *code_ptr = code;
        *out++ = 0x00;

        return static_cast<std::size_t>(out - output);
    }

    std::size_t CobsEncoder::decode(uint8_t *input, std::size_t length)
    {
        if (input == nullptr || length < 1)
        {
            return 0;
        }

        // Validate frame ends with delimiter
        if (input[length - 1] != 0x00)
        {
            return 0;
        }

        const std::size_t frame_length = length - 1;
        if (frame_length == 0)
        {
            return 0; // Only delimiter present
        }

        std::size_t src_index = 0;
        std::size_t dst_index = 0;

        while (src_index < frame_length)
        {
            // Read overhead byte
            uint8_t code = input[src_index++];

            // Validate code
            if (code == 0 || src_index + code - 1 > frame_length)
            {
                return 0;
            }

            // Copy data bytes
            for (uint8_t i = 1; i < code; ++i)
            {
                input[dst_index++] = input[src_index++];
            }

            // Add zero unless at end of frame
            if (code != 0xFF && src_index < frame_length)
            {
                input[dst_index++] = 0;
            }
        }

        return dst_index;
    }
}