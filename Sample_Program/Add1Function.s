        .syntax     unified
	.cpu        cortex-m4
        .text
        .thumb_func
        .align       2

// uint32_t  Add1(uint32_t x) ;

        .global     Add1
Add1:   ADD         R0,R0,1		// Return value of parameter plus 1
        BX          LR

        .end

