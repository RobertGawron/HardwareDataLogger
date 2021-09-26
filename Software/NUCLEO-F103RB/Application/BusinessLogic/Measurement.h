#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

namespace BusinessLogic
{
class Measurement
{
public:
    Measurement();
    ~Measurement();
    int getValue();
private:
    int value;
};
}

#endif
