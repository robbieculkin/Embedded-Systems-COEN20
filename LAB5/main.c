#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include "library.h"

int32_t minimum_c(int32_t data[], int32_t count){ // example c-implementation
int32_t currMin=INT_MAX; for (int i=0;i<count;i++) if (data[i]<currMin) currMin=data[i]; return currMin;
} extern int32_t minimum_asm(int32_t R0_data[], int32_t R1_count); int main(void){
InitializeHardware(HEADER, PROJECT_NAME); int32_t data[]={2, 9, 18, 1, 16, 15, 9, 13, 12, 11, 10, 9,  8, 7, 6, 5, 4,
3, 2, 7};
printf("Minimum = %d\n", (int) minimum_asm(data, 20)) ;
}
