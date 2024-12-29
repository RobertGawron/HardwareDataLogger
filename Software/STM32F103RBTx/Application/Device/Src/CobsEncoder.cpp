#include "Device/Inc/CobsEncoder.hpp"

namespace Device
{
    std::size_t CobsEncoder::encode(const uint8_t *input, std::size_t length,
                                    uint8_t *output, std::size_t maxOutputLength)
    {
        if (length == 0)
        {
            if (maxOutputLength > 0)
            {
                output[0] = 0x01;
                return 1;
            }
            return 0;
        }

        std::size_t readIndex = 0;
        std::size_t writeIndex = 0;
        std::size_t codeIndex = 0;
        uint8_t code = 1;

        while (readIndex < length)
        {
            if (input[readIndex] == 0 || code == 0xFF)
            {
                if (writeIndex >= maxOutputLength)
                {
                    return 0;
                }
                output[codeIndex] = code;

                codeIndex = writeIndex;
                code = 1;
            }
            else
            {
                if (writeIndex >= maxOutputLength)
                {
                    return 0;
                }
                output[writeIndex] = input[readIndex];
                ++code;
            }
            ++readIndex;
            ++writeIndex;
        }

        if (codeIndex >= maxOutputLength)
        {
            return 0;
        }
        output[codeIndex] = code;

        return writeIndex;
    }

    std::size_t CobsEncoder::decode(const uint8_t *input, std::size_t length,
                                    uint8_t *output, std::size_t maxOutputLength)
    {
        if (length == 0)
        {
            return 0;
        }

        std::size_t readIndex = 0;
        std::size_t writeIndex = 0;

        while (readIndex < length)
        {
            uint8_t code = input[readIndex];
            if (code == 0)
            {
                return 0;
            }

            std::size_t blockLength = code - 1;
            std::size_t nextIndex = readIndex + code;

            if (nextIndex > length)
            {
                return 0;
            }

            for (std::size_t i = 1; i < code; ++i)
            {
                if (writeIndex >= maxOutputLength)
                {
                    return 0;
                }
                output[writeIndex] = input[readIndex + i];
                ++writeIndex;
            }

            if (code != 0xFF && nextIndex < length)
            {
                if (writeIndex >= maxOutputLength)
                {
                    return 0;
                }
                output[writeIndex] = 0;
                ++writeIndex;
            }

            readIndex = nextIndex;
        }

        return writeIndex;
    }
}
