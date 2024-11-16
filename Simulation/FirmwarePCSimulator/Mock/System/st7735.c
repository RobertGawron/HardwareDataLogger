#include "st7735.h"

int32_t ST7735_RegisterBusIO(ST7735_Object_t *pObj, ST7735_IO_t *pIO)
{
  return 0;
}

int32_t ST7735_Init(ST7735_Object_t *pObj, uint32_t ColorCoding, uint32_t Orientation)
{
  return 0;
}

int32_t ST7735_DeInit(ST7735_Object_t *pObj)
{
  (void)(pObj);

  return ST7735_OK;
}

int32_t ST7735_ReadID(ST7735_Object_t *pObj, uint32_t *Id)
{
  return ST7735_OK;
}

int32_t ST7735_DisplayOn(ST7735_Object_t *pObj)
{
  return ST7735_OK;
}

int32_t ST7735_DisplayOff(ST7735_Object_t *pObj)
{
  return ST7735_OK;
}

int32_t ST7735_SetBrightness(ST7735_Object_t *pObj, uint32_t Brightness)
{
  /* Feature not supported */
  return ST7735_ERROR;
}

int32_t ST7735_GetBrightness(ST7735_Object_t *pObj, uint32_t *Brightness)
{
  (void)(pObj);
  (void)(Brightness);

  /* Feature not supported */
  return ST7735_ERROR;
}

int32_t ST7735_SetOrientation(ST7735_Object_t *pObj, uint32_t Orientation)
{
  return ST7735_OK;
}

int32_t ST7735_GetOrientation(ST7735_Object_t *pObj, uint32_t *Orientation)
{
  return ST7735_OK;
}

int32_t ST7735_SetCursor(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos)
{
  return ST7735_OK;
}

int32_t ST7735_DrawBitmap(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint8_t *pBmp)
{
  int32_t ret = ST7735_OK;
  return ret;
}

int32_t ST7735_FillRGBRect(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint8_t *pData, uint32_t Width, uint32_t Height)
{
  int32_t ret = ST7735_OK;
  return ret;
}

int32_t ST7735_DrawHLine(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint32_t Color)
{
  int32_t ret = ST7735_OK;
  return ret;
}

int32_t ST7735_DrawVLine(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint32_t Color)
{
  int32_t ret = ST7735_OK;
  return ret;
}

int32_t ST7735_FillRect(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height, uint32_t Color)
{
  int32_t ret = ST7735_OK;
  return ret;
}

int32_t ST7735_SetPixel(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t Color)
{
  int32_t ret = ST7735_OK;
  return ret;
}

int32_t ST7735_GetPixel(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint32_t *Color)
{
  return ST7735_OK;
}

int32_t ST7735_GetXSize(ST7735_Object_t *pObj, uint32_t *XSize)
{
  (void)pObj;
  return ST7735_OK;
}

int32_t ST7735_GetYSize(ST7735_Object_t *pObj, uint32_t *YSize)
{
  (void)pObj;
  return ST7735_OK;
}
