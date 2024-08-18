#ifndef ST7735DISPLAYBACKLIGHTDRIVER_H_
#define ST7735DISPLAYBACKLIGHTDRIVER_H_

#include <stdint.h>
#include "IDisplayBacklightDriver.hpp"

namespace Driver
{

	class ST7735DisplayBacklightDriver : public IDisplayBacklightDriver
	{
	public:
		ST7735DisplayBacklightDriver() = default;
		virtual ~ST7735DisplayBacklightDriver() = default;

		virtual void init();
		virtual bool setBrightness(uint16_t value);
		virtual uint16_t getBrightness();

	private:
		uint16_t brightness;
	};

}

#endif
