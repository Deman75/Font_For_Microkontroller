/*******************************************************
*                    Font Generate                    *
*                  Font height 21                      
********************************************************/



/*********************Include****************************/

#include "stm32f4xx_hal.h"
#include <stdlib.h>
/*****************Defines******************************/
#define TimesNewRoman21_Height 21
#define TimesNewRoman21_Width 3  // Simbol Byte Width


uint8_t CharNweTimesNewRoman21 (uint16_t x, uint16_t y, unsigned char ch, uint16_t CharColor, uint16_t BkgColor);
void StringTimesNewRoman21 (uint16_t x, uint16_t y, char *string, uint16_t CharColor, uint16_t BkgColor);

