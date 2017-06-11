#include <stdio.h>
#include <stdint.h>
#include "library.h"
#include "graphics.h"

#define ENTRIES(a) (sizeof(a)/sizeof(a[0]))

typedef int64_t Q32 ;

extern Q32     Q32Poly(Q32, Q32 [], int32_t) ;
extern Q32     Q32Product(Q32, Q32) ;

static Q32     Q32Ratio(int32_t, int32_t) ;
static Q32     Q32Sine(Q32) ;
static Q32     FloatToQ32(float) ;
static float   Q32ToFloat(Q32) ;
static int     Degrees(int, int, int) ;

int main(void)
    {
    int y, quadrant ;
    int ymin = 48 ;
    int ymax = YPIXELS - 16 ;

    InitializeHardware(HEADER, PROJECT_NAME) ;
    SetColor(COLOR_GREEN) ;

    for (y = ymin; y < ymax; y++)
        {
        float fltrad, fltsin ;
        Q32 q32rad, q32sin ;
        int x, degrees ;

        degrees  = Degrees(y, ymin, ymax) ;     // returns 0 - 359
        quadrant = degrees / 90 ;
        degrees  = degrees % 90 ;
        if ((quadrant % 2) != 0) degrees = 90 - degrees ;

        fltrad  = (3.14158 * degrees) / 180 ;

        q32rad  = FloatToQ32(fltrad) ;
        q32sin  = Q32Sine(q32rad) ;
        fltsin  = Q32ToFloat(q32sin) ;

        if ((quadrant/2) & 1) fltsin = -fltsin ;

        x = (XPIXELS/2) * (1.0 + fltsin) ;
        DrawLine(XPIXELS/2, y, x, y) ;
        }

    while (1) ;
    }

static int Degrees(int y, int ymin, int ymax)
    {
    return (int) (360 * ((float) (y - ymin)) / ((float) (ymax - ymin))) ;
    }

static Q32 Q32Ratio(int32_t top, int32_t btm)
    {
    int32_t rounding = (((top ^ btm) >= 0) ? btm : -btm) / 2 ;
    return (((Q32) top << 32) + rounding) / btm ;
    }

static Q32 FloatToQ32(float x)
    {
    return (Q32) (x * ((float) Q32Ratio(1, 1))) ;
    }

static float Q32ToFloat(Q32 x)
    {
    return ((float) x) / ((float) Q32Ratio(1, 1)) ;
    }

static Q32 Q32Sine(Q32 x)
    {
    static int top[8] = {0, 1,   0,    -1,       0,         1,           0,            -1} ;
    static int btm[8] = {1, 1, 2*1, 3*2*1, 4*3*2*1, 5*4*3*2*1, 6*5*4*3*2*1, 7*6*5*4*3*2*1} ;
    static int initialized = 0 ;
    static Q32 coef[8] ;

    if (!initialized)
        {
        int k ;

        for (k = 0; k < ENTRIES(coef); k++)
            {
            coef[k] = Q32Ratio(top[k], btm[k]) ;
            }
        initialized = 1 ;
        }

    return Q32Poly(x, coef, ENTRIES(coef)) ;
    }
