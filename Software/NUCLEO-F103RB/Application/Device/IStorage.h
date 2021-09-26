#ifndef ISTORAGE_H_
#define ISTORAGE_H_

class IStorage {
public:
	~IStorage() = default;

    void init();
    void deinit();
    void write();
};

#endif
