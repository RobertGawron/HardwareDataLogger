module;

#include <cstdint>

export module Driver.SdCardStatus;

// helper enum to avoid poluting higher layers with includes to sd card third party library
export namespace Driver
{
    enum class SdCardStatus : std::uint8_t
    {
        OK = 0,            /* (0) Succeeded */
        WRITE_ERROR,       /* (1) Write operation failed */
        INCOMPLETE_WRITE,  /* (2) Not all bytes were written */
        SYNC_ERROR,        /* (3) Failed to sync data to disk */
        INVALID_PARAMETER, /* (4) Given parameter is invalid */
        FILE_OPEN_ERROR,
        FILE_CLOSE_ERROR,
        FILE_ALREADY_OPEN,     /* Cannot open file - another file is already open */
        NO_FILE_OPEN,          /* Cannot close file - no file is open */
        FILESYSTEM_NOT_MOUNTED /* Filesystem is not mounted */

    };
}