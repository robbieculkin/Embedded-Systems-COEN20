#include <stdio.h>
#include <stdint.h>
#include "library.h"

extern int Modulus(int number, int divisor);

int Modulus2(int number, int divisor){
    return ((number%divisor)+divisor)%divisor;
}

int main(void){
	InitializeHardware(HEADER, PROJECT_NAME);
	int number[]=  {7, 6, -5, -4}, divisor[]= {5, 2,  3,  6}, result[]=  {2, 0,  1,  2};

    for (int i=0;i<4;i++){
        int my_modulus = Modulus(number[i], divisor[i]);
        printf("No=%d Div=%d my%%(%d) == %%(%d)->%s\n", number[i], divisor[i], my_modulus, result[i], (my_modulus==result[i]?"TRUE":"FALSE"));
    }

    return 0;
}
