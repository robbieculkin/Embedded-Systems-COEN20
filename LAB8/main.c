#include <stdio.h>
#include <stdint.h>
#include "library.h"
#include "graphics.h"

float Poly(float, float [], int32_t) ;

float Sine(float x)
    {
    float coef[] = {0.0, 1.0/(1), 0.0, -1.0/(3*2*1), 0.0, 1.0/(5*4*3*2*1), 0.0, -1.0/(7*6*5*4*3*2*1)} ;
    return Poly(x, coef, sizeof(coef)/sizeof(*coef)) ;
    }

int main(void)
    {
    int angle, step, x, y ;
    float radians, result, quadrant ;

    InitializeHardware(HEADER, PROJECT_NAME) ;

    SetColor(COLOR_GREEN) ;

    y = YPIXELS/2 - 90  ;
    for (quadrant = 0; quadrant < 4; quadrant++)
       {
       for (step = 0; step < 90; step += 2)
            {
            angle = (quadrant == 0 || quadrant == 2) ? step : 90 - step ;
            radians = (3.14158 * angle) / 180 ;
            result = Sine(radians) ;
            if (quadrant >= 2) result = -result ;

            x = (XPIXELS/2) * (1.0 + result) ;
            DrawLine(XPIXELS/2, y, x, y) ;
            y++ ;
            }
       }

    while (1) ; // Never exit#else
    }
