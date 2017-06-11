#include <stdio.h>
#include <stdint.h>
#include "library.h"

extern uint32_t  Add1(uint32_t x) ;

int main(void)
{
InitializeHardware(HEADER, PROJECT_NAME);
PrintTwo("numb=%d\n", 10) ;
return 0 ;
}
