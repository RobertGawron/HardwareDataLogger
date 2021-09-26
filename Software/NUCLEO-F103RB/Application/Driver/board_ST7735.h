/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/* It's bad to place body of functions in .h file, but this is what uGFX lib wants. */

#ifndef BOARD_ST7735_H
#define BOARD_ST7735_H

#include "stm32f1xx_hal.h"
#include "board_ST7736_os.h"

#define ST7735_TYPE BOARD_TYPE_B


// TODO remove it
#define ST7735_SPI_PORT hspi1
extern SPI_HandleTypeDef ST7735_SPI_PORT;

#define ST7735_RES_Pin       GPIO_PIN_7
#define ST7735_RES_GPIO_Port GPIOC
#define ST7735_CS_Pin        GPIO_PIN_1
#define ST7735_CS_GPIO_Port  GPIOB
#define ST7735_DC_Pin        GPIO_PIN_8
#define ST7735_DC_GPIO_Port  GPIOA


static GFXINLINE void init_board(GDisplay *g) {
}

static GFXINLINE void post_init_board(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, gBool state) {
	(void) g;

	if (!state)
		HAL_GPIO_WritePin(ST7735_RES_GPIO_Port, ST7735_RES_Pin, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(ST7735_RES_GPIO_Port, ST7735_RES_Pin, GPIO_PIN_SET);
}

static GFXINLINE void set_backlight(GDisplay *g, gU8 percent) {
	(void) g;
	
}

static GFXINLINE void acquire_bus(GDisplay *g) {
	(void) g;
	 HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);
}

static GFXINLINE void release_bus(GDisplay *g) {
	(void) g;
    HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_SET);
}

static GFXINLINE void write_data(GDisplay *g, gU16 data) {
	(void) g;
	HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_SET);
	HAL_SPI_Transmit(&ST7735_SPI_PORT, &data, sizeof(data), HAL_MAX_DELAY);
}

static GFXINLINE void write_cmd(GDisplay *g, gU8 cmd) {
	HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&ST7735_SPI_PORT, &cmd, sizeof(cmd), HAL_MAX_DELAY);
}


static GFXINLINE void write_data_byte(GDisplay *g, gU8 data){
	HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_SET);
	HAL_SPI_Transmit(&ST7735_SPI_PORT, &data, 1, HAL_MAX_DELAY);
}


#endif
