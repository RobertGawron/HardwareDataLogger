#ifndef Display_h
#define Display_h
#include "Device/Interfaces/IDisplay.hpp"
#include "Driver/Interfaces/IDisplayDriver.hpp"

namespace Device
{
    class Display : public IDisplay
    {
    public:
        explicit Display(Driver::IDisplayDriver &displayDriver);

        virtual bool initialize() override;
        uint8_t u8x8DSt7735Impl(u8x8_t *u8x8, uint8_t msg, uint8_t argInt, void *argPtr);

    private:
        void u8g2_Setup_st7735(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb);

        // uint8_t u8x8_byte_rtthread_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

        Driver::IDisplayDriver &displayDriver;
    };

};

#endif