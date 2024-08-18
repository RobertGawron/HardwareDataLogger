#ifndef IDISPLAY_H_
#define IDISPLAY_H_

#include <stdint.h>

namespace Device
{

    class IDisplay
    {
    public:
        virtual ~IDisplay() = default;

        virtual bool init() = 0;
    };

}

#endif
