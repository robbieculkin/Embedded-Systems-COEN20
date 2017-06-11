#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "library.h"

static char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"} ;

static int GetMonth(char *month) ;
extern uint32_t UBFX(uint32_t word, uint32_t lsb, uint32_t width) ;
extern uint32_t BFI(uint32_t word, uint32_t value, uint32_t lsb, uint32_t width) ;

int main(void)
    {
    int year, month, date, hour, minute, second, plus1, secby2, yrminus1900 ;
    char month_abbr[4], datestr[20], timestr[20] ;
    uint32_t clock  = 0xFFFFFFFF ;

    InitializeHardware(HEADER, PROJECT_NAME) ;

    sscanf(__DATE__, "%s %d %d", month_abbr, &date, &year) ;
    sscanf(__TIME__, "%d:%d:%d", &hour, &minute, &second) ;

    yrminus1900 = year - 1900 ;
    month  = GetMonth(month_abbr) ;
    secby2 = second / 2 ;
    plus1  = second % 2 ;

    // Encode and pack the data into 32 bits
    clock = BFI(clock, secby2,       0, 5) ;
    clock = BFI(clock, minute,       5, 6) ;
    clock = BFI(clock, hour,        11, 5) ;
    clock = BFI(clock, date,        16, 5) ;
    clock = BFI(clock, month,       21, 4) ;
    clock = BFI(clock, yrminus1900, 25, 7) ;

    // Unpack the data into the components
    yrminus1900   = UBFX(clock, 25, 7) ;
    month         = UBFX(clock, 21, 4) ;
    date          = UBFX(clock, 16, 5) ;
    hour          = UBFX(clock, 11, 5) ;
    minute        = UBFX(clock,  5, 6) ;
    secby2        = UBFX(clock,  0, 5) ;

    // Recreate original string format
    sprintf(datestr, "%s %2d %d", months[month], date, yrminus1900 + 1900) ;
    sprintf(timestr, "%02d:%02d:%02d", hour, minute, 2*secby2 + plus1) ;

    printf("Original     Unpacked     Correct?\n") ;
    printf("-----------  -----------  --------\n") ;
    printf("%-11s  %-11s  %s\n", __DATE__, datestr, !strcmp(datestr, __DATE__) ? "YES" : "NO") ;
    printf("%-11s  %-11s  %s\n", __TIME__, timestr, !strcmp(timestr, __TIME__) ? "YES" : "NO") ;
    printf("\n") ;
    printf("Packed format\n") ;
    printf("-------------\n") ;
    printf("%08X (hex)\n", (unsigned) clock) ;
    printf("\n") ;
    printf("BitField   Bits   Value\n") ;
    printf("--------   ----   -----\n") ;
    printf("%-9s  %2d-%-2d   %3d\n", "year-1900", 31, 25, yrminus1900) ;
    printf("%-9s  %2d-%-2d   %3d\n", "month-1",   24, 21, month) ;
    printf("%-9s  %2d-%-2d   %3d\n", "date",      20, 16, date) ;
    printf("%-9s  %2d-%-2d   %3d\n", "hour",      15, 11, hour) ;
    printf("%-9s  %2d-%-2d   %3d\n", "minute",    10,  5, minute) ;
    printf("%-9s  %2d-%-2d   %3d\n", "second/2",   4,  0, secby2) ;

    while (1) ;
    return 0 ;
    }

static int GetMonth(char *month)
    {
    int m ;

    for (m = 0; m < 12; m++)
        {
        if (strcmp(month, months[m]) == 0) return m ;
        }

    printf("Unrecognized month: %s\n", month) ;
    while (1) ;
    }

