#include "BusinessLogic/Inc/HmiFactory.hpp"
#include "U8g2lib.h"
#include "MUIU8g2.h"

// for test of driver lib
#include <stdio.h>

namespace BusinessLogic
{
    HmiMui::HmiMui(Device::IDisplay &_display,
                   Device::IDisplayBrightnessRegulator &_displayBrightnessRegulator,
                   Device::IKeyboard &_keyboard) : display(_display),
                                                   displayBrightnessRegulator(_displayBrightnessRegulator),
                                                   keyboard(_keyboard),
                                                   IHmi(_display,
                                                        _displayBrightnessRegulator,
                                                        _keyboard)
    {
    }

    bool HmiMui::initialize()
    {

        volatile int x = 0;
        // display.initialize();

        // for tests
        auto color = Driver::DisplayPixelColor::getColor(0x2f, 0xff, 0xff);
        // display.drawHorizontalLine(1, 1, 20, color);
        printf("hello drawHorizontalLine\n");

        // Device::Display u8g2(display);

        display.initialize();

        MUIU8G2 mui;

        muif_t muif_list[] = {
            MUIF_U8G2_FONT_STYLE(0, u8g2_font_helvR08_tr), /* define style 0 */
            MUIF_U8G2_LABEL(),                             /* allow MUI_LABEL command */
            MUIF_BUTTON("BN", mui_u8g2_btn_exit_wm_fi)     /* define exit button */
        };

        fds_t fds_data[] =                       /* Don't use comma between the commands! */
            MUI_FORM(1)                          /* This will start the definition of form 1 */
            MUI_STYLE(0)                         /* select the font defined with style 0 */
            MUI_LABEL(5, 15, "Hello U8g2")       /* place text at postion x=5, y=15 */
            MUI_XYT("BN", 64, 30, " Select Me ") /* place a button at pos x=64, y=30 */
            ;

        printf("%s %d\n", __FILE__, __LINE__);

        display.begin(/* menu_select_pin= */ 5, /* menu_next_pin= */ 4, /* menu_prev_pin= */ 2, /* menu_up_pin= */ U8X8_PIN_NONE, /* menu_down_pin= */ U8X8_PIN_NONE, /* menu_home_pin= */ 3);

        printf("%s %d\n", __FILE__, __LINE__);

        mui.begin(display, fds_data, muif_list, sizeof(muif_list) / sizeof(muif_t));
        mui.gotoForm(/* form_id= */ 1, /* initial_cursor_position= */ 0);
        display.firstPage();
        display.setCursor(0, 0);

        do
        {
            mui.draw();
        } while (display.nextPage());

        return true;
    }

    bool HmiMui::start()
    {
        return true;
    }

    bool HmiMui::tick()
    {
        return true;
    }

}