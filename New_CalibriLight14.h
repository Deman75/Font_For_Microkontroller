/*******************************************************
*                    Font Generate                    *
*                  Font height 14                      
********************************************************/



/*********************Include****************************/

#include "stm32f4xx_hal.h"
#include <stdlib.h>
/*****************Defines******************************/
#define CalibriLight14_Height 14
#define CalibriLight14_Width 2  // Simbol Byte Width


uint8_t CharNweCalibriLight14 (uint16_t x, uint16_t y, unsigned char ch, uint16_t CharColor, uint16_t BkgColor);
void StringCalibriLight14 (uint16_t x, uint16_t y, char *string, uint16_t CharColor, uint16_t BkgColor);

