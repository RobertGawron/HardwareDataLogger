#ifndef UARTSTORAGE_H_
#define UARTSTORAGE_H_

#include "IStorage.hpp"

namespace Device
{

    class UARTStorage
    {
    public:
        UARTStorage();
        virtual ~UARTStorage();

        void init();
        void deinit();
        void write();
    };

}

#endif
