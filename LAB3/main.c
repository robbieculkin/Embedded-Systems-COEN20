#include <stdio.h>
#include <stdint.h>
#include "library.h"

extern int *pWord(void *arrayBaseAdr, int numberOfColumns, int currentRow, int currentCol);

// C example implementation - translate this to ARM assembler pWord(...)
int *pWord2(void *arrayBaseAdr, int numberOfColumns, int currentRow, int currentCol){
    return arrayBaseAdr+((numberOfColumns*currentRow+currentCol)*4);
}

int main(void){
    InitializeHardware(HEADER, PROJECT_NAME);

    int a32[4][2] ;  // 4 rows of 2 columns each
    int b32[2][4] ;  // 2 rows of 4 columns each

    int value=10; // arbitrary value to start from
    for (int i=0;i<4;i++){
        for (int j=0;j<2;j++){
            a32[i][j]=value++; // assign arbitrary value to the array
            int* addrCalc = pWord(a32, 2, i, j);
            printf("&a32[%d][%d]=%d [%s] %d\n", i, j, (int)addrCalc, (addrCalc==&a32[i][j])?"OK":"FAIL", *addrCalc);
        }
    }

    for (int i=0;i<2;i++){
        for (int j=0;j<4;j++){
            b32[i][j]=value++; // assign arbitrary value to the array
            int* addrCalc = pWord(b32, 4, i, j);
            printf("&b32[%d][%d]=%d [%s] %d\n", i, j, (int)addrCalc, (addrCalc==&b32[i][j])?"OK":"FAIL", *addrCalc) ;
        }
    }
}
