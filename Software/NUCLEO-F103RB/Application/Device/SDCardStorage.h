#ifndef SDCARDSTORAGE_H_
#define SDCARDSTORAGE_H_

#include "IStorage.h"

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
