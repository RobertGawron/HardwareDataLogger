#ifndef ST7735DisplayDISPLAY_H_
#define ST7735DisplayDISPLAY_H_

#include "IDisplay.hpp"
#include "fonts.h"
namespace Driver
{

	class ST7735DisplayDriver : public Device::IDisplay
	{
	public:
		using DisplayFont = FontDef;

		ST7735DisplayDriver() = default;
		virtual ~ST7735DisplayDriver() = default;

		bool init();

		bool drawPixel(uint16_t x, uint16_t y, uint16_t color);
		bool writeString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor);
		bool fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
		bool fillScreen(uint16_t color);
		bool drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data);
		void invertColors(bool invert);
	};

}

#endif
