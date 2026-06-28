module;

#include <cstdint>

export module Driver.FileOpenMode;

export namespace Driver
{
    enum class FileOpenMode : std::uint8_t
    {
        OVERWRITE, // Create new or overwrite existing file
        APPEND     // Append to existing file, create if doesn't exist
    };

}