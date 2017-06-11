        .syntax     unified
	.cpu        cortex-m4
        .text
        .thumb_func
        .align       2

        .global     pWord
pWord:  MLA         R1,R1,R2,R3 //R1*R2+R3, save it in R1. This is the offset from the original address, given rows & columns
        LSL         R1,R1,2     //R1*2^2, save it in R1. Multiplying by 4 because 32 bit ints are 4 memory locations apart
        ADD         R0,R0,R1    //R0+R1, save it in R0. Add the offset to the original address
        BX          LR          //return

        .end

