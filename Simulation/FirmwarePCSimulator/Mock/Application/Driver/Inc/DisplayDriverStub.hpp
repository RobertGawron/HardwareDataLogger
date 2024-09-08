
#ifndef DisplayDriverStub_h
#define DisplayDriverStub_h

#include "Driver/Interfaces/IDisplayDriver.hpp"
#include "Driver/Inc/DisplayPixelColor.hpp"

namespace Driver
{

    class DisplayDriverStub : public Driver::IDisplayDriver
    {
    public:
        explicit DisplayDriverStub() = default;

        virtual ~DisplayDriverStub() = default;

        // Additional methods used in simulation
        virtual uint8_t getDisplayWidth() const;
        virtual uint8_t getDisplayHeight() const;
        virtual DisplayPixelColor getPixel(uint8_t x, uint8_t y) const;

        virtual bool drawPixel(uint16_t x, uint16_t y, uint16_t color) override;

        virtual bool writeString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor) override;

        virtual bool fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) override;

        virtual bool fillScreen(uint16_t color) override;

        virtual bool drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data) override;

        virtual void invertColors(bool invert) override;

    protected:
        bool onInitialize() override;
        bool onStart() override;
        bool onStop() override;
        bool onReset() override;

        // TODO think about it
        DisplayPixelColor displayPixels[10000][100000];
    };

}

#endif