#ifndef STORAGESCONTAINER_H_
#define STORAGESCONTAINER_H_

#include "SDCardStorage.h"
#include "UARTStorage.h"
#include "WifiStorage.h"

namespace Application
{

class StoragesContainer
{
public:
	StoragesContainer();
	virtual ~StoragesContainer();
	void tick();

private:
	Device::SDCardStorage mSDCardStorage;
	Device::UARTStorage mUARTStorage;
	Device::WifiStorage mWifiStorage;
};

}

#endif
