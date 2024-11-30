#ifndef IDisplay_h
#define IDisplay_h
#include "U8g2lib.h"
#include "u8g2.h"

namespace Device
{
    class IDisplay : public U8G2
    {
    public:
        // todo
        IDisplay() : U8G2() {};

        bool init();
    };

};

#endif