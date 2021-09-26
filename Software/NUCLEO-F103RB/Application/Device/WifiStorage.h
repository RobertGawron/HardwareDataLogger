#ifndef WIFISTORAGE_H_
#define WIFISTORAGE_H_

#include "IStorage.h"

namespace Device
{

class WifiStorage : public IStorage
{
public:
	WifiStorage();
	virtual ~WifiStorage();

	void init();
	void deinit();
	void write();
};

}

#endif
