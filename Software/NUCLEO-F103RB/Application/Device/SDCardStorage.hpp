#ifndef SDCARDSTORAGE_H_
#define SDCARDSTORAGE_H_

#include "IStorage.hpp"

namespace Device
{

    class SDCardStorage
    {
    public:
        SDCardStorage();
        virtual ~SDCardStorage();

        void init();
        void deinit();
        void write();
    };

}

#endif
