#ifndef ISTORAGE_H_
#define ISTORAGE_H_

class IStorage
{
public:
    virtual ~IStorage() = default;

    virtual void init();
    virtual void deinit();
    virtual void write();
};

#endif
