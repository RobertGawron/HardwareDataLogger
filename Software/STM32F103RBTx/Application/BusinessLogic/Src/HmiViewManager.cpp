#include "BusinessLogic/Inc/HmiViewManager.hpp"

// for test of muiminimal lib
#include "U8g2lib.h"
#include "MUIU8g2.h"
#include "Device/Inc/Display.hpp"

// for test of driver lib
#include <stdio.h>
#include "Driver/Inc/DisplayPixelColor.hpp"
#include "BusinessLogic/Interfaces/IPlatformFactory.hpp"

namespace BusinessLogic
{
    HmiViewManager::HmiViewManager(Driver::IDisplayDriver &_display)
        : display(_display)
    {
    }

    bool HmiViewManager::initialize()
    {
        volatile int x = 0;
        display.initialize();

        // for tests
        auto color = Driver::DisplayPixelColor::getColor(0x2f, 0xff, 0xff);
        // display.drawHorizontalLine(1, 1, 20, color);
        printf("hello drawHorizontalLine\n");

        Device::Display u8g2(display);

        u8g2.init();

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

        u8g2.begin(/* menu_select_pin= */ 5, /* menu_next_pin= */ 4, /* menu_prev_pin= */ 2, /* menu_up_pin= */ U8X8_PIN_NONE, /* menu_down_pin= */ U8X8_PIN_NONE, /* menu_home_pin= */ 3);

        printf("%s %d\n", __FILE__, __LINE__);

        mui.begin(u8g2, fds_data, muif_list, sizeof(muif_list) / sizeof(muif_t));
        mui.gotoForm(/* form_id= */ 1, /* initial_cursor_position= */ 0);
        u8g2.firstPage();
        u8g2.setCursor(0, 0);

        do
        {
            mui.draw();
        } while (u8g2.nextPage());

        return true;
    }
    bool HmiViewManager::start()
    {
        display.start();
        return true;
    }
    bool HmiViewManager::stop()
    {
        display.stop();
        return true;
    }

    bool HmiViewManager::tick()
    {

        return true;
    }

}
