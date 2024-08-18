#ifndef AMBIENTLIGHTSENSORDRIVER_H_
#define AMBIENTLIGHTSENSORDRIVER_H_

#include "IAmbientLightSensorDriver.hpp"
#include <stdint.h>

namespace Driver
{
	/// @brief check ambient light level based on ADC connected to a photodiode
	class AmbientLightSensorDriver : public IAmbientLightSensorDriver
	{
	public:
		AmbientLightSensorDriver() = default;
		virtual ~AmbientLightSensorDriver() = default;

		virtual bool init();
		virtual uint32_t getAmbientLightLevel();
	};

}

#endif
