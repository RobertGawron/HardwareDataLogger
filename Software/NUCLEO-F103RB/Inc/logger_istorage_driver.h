#ifndef LOGGER_ISTORAGE_DRIVER_H_
#define LOGGER_ISTORAGE_DRIVER_H_

typedef struct LoggerIStorageDriver_t LoggerIStorageDriver_t;

struct LoggerIStorageDriver_t
{
    void (*init)(LoggerIStorageDriver_t* self);
    void (*deinit)(LoggerIStorageDriver_t* self);
};

#endif
