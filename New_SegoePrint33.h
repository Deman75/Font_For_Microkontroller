/*******************************************************
*                    Font Generate                    *
*                  Font height 33                      
********************************************************/



/*********************Include****************************/

#include "stm32f4xx_hal.h"
#include <stdlib.h>
/*****************Defines******************************/
#define SegoePrint33_Height 33
#define SegoePrint33_Width 4  // Simbol Byte Width


uint8_t CharNweSegoePrint33 (uint16_t x, uint16_t y, unsigned char ch, uint16_t CharColor, uint16_t BkgColor);
void StringSegoePrint33 (uint16_t x, uint16_t y, char *string, uint16_t CharColor, uint16_t BkgColor);

