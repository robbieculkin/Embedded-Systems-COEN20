#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "library.h"

extern Remainder2(int s32, int k);

int Remainder_c(int s32, int k){
    int power = 1 << k;
    return ((power - 1) & s32) - (power & (s32 >> 31));
}

int main(void){
    InitializeHardware(HEADER, PROJECT_NAME);

    int numbers[4][4]={{7, 2, 4, 3},{-7, 2, 4, -3},{13, 3, 8, 5},{-13, 3, 8, -5}};

    for (int i=0; i<4;i++)
            printf("s32=%d k=%d div=%d res=%d MY = %d\n", numbers[i][0], numbers[i][1], numbers[i][2], numbers[i][3], Remainder2(numbers[i][0], numbers[i][1]));
}

