/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/* this file contans operating-system methods needed by uGFX lib.  */
/* It's bad idea to place body of a functions in .h file, but this is what uGFX lib wants. */

#ifndef BOARD_ST7735_OS_H
#define BOARD_ST7735_OS_H

#include "stm32f1xx_hal.h"

uint_least32_t gfxSystemTicks(void)
{
	return HAL_GetTick();
}

uint_least32_t	 gfxMillisecondsToTicks(uint_least32_t ms)
{
	return ms;
}

#endif
