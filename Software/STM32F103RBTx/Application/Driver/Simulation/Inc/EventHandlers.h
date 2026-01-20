#ifndef EVENT_HANDLERS_H
#define EVENT_HANDLERS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /*
        typedef uint8_t HAL_StatusTypeDef;
        enum : uint8_t
        {
            HAL_OK = 0x00U,
            HAL_ERROR = 0x01U,
            HAL_BUSY = 0x02U,
            HAL_TIMEOUT = 0x03U
        };
    */

    typedef enum
    {
        HAL_OK = 0x00U,
        HAL_ERROR = 0x01U,
        HAL_BUSY = 0x02U,
        HAL_TIMEOUT = 0x03U
    } HAL_StatusTypeDef;

    typedef uint8_t SdCardStatus_t;
    typedef uint8_t FileOpenMode_t;
    typedef uint8_t UartId_t;

    typedef int (*SerialTxCallback)(uint8_t, const uint8_t *, uint16_t, uint32_t);

    typedef uint8_t (*SdCardOpenCallback)(const char *, uint8_t);
    typedef uint8_t (*SdCardWriteCallback)(const uint8_t *, uint16_t);
    typedef uint8_t (*SdCardCloseCallback)(void);

    typedef bool (*SdCardInitializeCallback)(void);
    typedef bool (*SdCardStartCallback)(void);
    typedef bool (*SdCardStopCallback)(void);
    typedef bool (*SdCardResetCallback)(void);

    void LibWrapper_RegisterSerialTxCallback(SerialTxCallback callback);
    void LibWrapper_RegisterSdCardOpenCallback(SdCardOpenCallback callback);
    void LibWrapper_RegisterSdCardWriteCallback(SdCardWriteCallback callback);
    void LibWrapper_RegisterSdCardCloseCallback(SdCardCloseCallback callback);
    void LibWrapper_RegisterSdCardInitializeCallback(SdCardInitializeCallback callback);
    void LibWrapper_RegisterSdCardStartCallback(SdCardStartCallback callback);
    void LibWrapper_RegisterSdCardStopCallback(SdCardStopCallback callback);
    void LibWrapper_RegisterSdCardResetCallback(SdCardResetCallback callback);

    HAL_StatusTypeDef serialTx(UartId_t uartId, const uint8_t *data, uint16_t size, uint32_t timeout);
    SdCardStatus_t sdCardOpen(const char *filename, FileOpenMode_t mode);
    SdCardStatus_t sdCardWrite(const uint8_t *data, uint16_t size);
    SdCardStatus_t sdCardClose(void);
    bool sdCardInitialize(void);
    bool sdCardStart(void);
    bool sdCardStop(void);
    bool sdCardReset(void);

#ifdef __cplusplus
}
#endif

#endif