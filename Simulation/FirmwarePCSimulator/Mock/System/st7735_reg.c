#include "st7735_reg.h"

int32_t st7735_read_reg(st7735_ctx_t *ctx, uint8_t reg, uint8_t *pdata)
{
  (void)ctx;   // Mark ctx as unused
  (void)reg;   // Mark reg as unused
  (void)pdata; // Mark pdata as unused
  return 0;
}

int32_t st7735_write_reg(st7735_ctx_t *ctx, uint8_t reg, uint8_t *pdata, uint32_t length)
{
  (void)ctx;    // Mark ctx as unused
  (void)reg;    // Mark reg as unused
  (void)pdata;  // Mark pdata as unused
  (void)length; // Mark length as unused
  return 0;
}

int32_t st7735_send_data(st7735_ctx_t *ctx, uint8_t *pdata, uint32_t length)
{
  (void)ctx;    // Mark ctx as unused
  (void)pdata;  // Mark pdata as unused
  (void)length; // Mark length as unused
  return 0;
}

int32_t st7735_recv_data(st7735_ctx_t *ctx, uint8_t *pdata, uint32_t length)
{
  (void)ctx;    // Mark ctx as unused
  (void)pdata;  // Mark pdata as unused
  (void)length; // Mark length as unused
  return 0;
}
