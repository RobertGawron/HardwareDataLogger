#ifndef IDISPLAYBACKLIGHTDRIVER_H_
#define IDISPLAYBACKLIGHTDRIVER_H_

#include <stdint.h>

namespace Driver
{
	/// @brief handles backlight level of the LCD via PWM
	class IDisplayBacklightDriver
	{
	public:
		virtual ~IDisplayBacklightDriver() = default;

		virtual void init() = 0;
		virtual bool setBrightness(uint16_t value) = 0;
		virtual uint16_t getBrightness() = 0;
	};

}

#endif
