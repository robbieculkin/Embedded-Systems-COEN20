        .syntax     unified
	.cpu        cortex-m4
        .text
        .thumb_func
        .align       2

// uint32_t UBFX(uint32_t word, uint32_t lsb, uint32_t width) ;

        .global     UBFX
UBFX:   PUSH    {R4}

        //MAKE MASK
        LDR     R3,=1
        LSL     R3,R3,R1        //1<<LSB
        ADD     R2,R2,R1        //(lsb+width)
        LDR     R4,=1
        LSL     R4,R4,R2        //1<<(lsb+width)
        SUB     R3,R4,R3        //1<<(lsb+width) - 1<<LSB

        //EXTRACT WITH AND
        AND     R3,R3,R0
        LSR     R0,R3,R1

        POP     {R4}
        BX      LR

// uint32_t BFI(uint32_t word, uint32_t value, uint32_t lsb, uint32_t width) ;

        .global     BFI
BFI:    PUSH    {R4,R5,R6}

        //MAKE MASK
        LDR     R4,=1
        LSL     R4,R4,R2        //1<<LSB
        LDR     R6,=1
        ADD     R3,R3,R2
        LSL     R6,R6,R3        //1<<(lsb+width)
        SUB     R4,R6,R4        //1<<(lsb+width) - 1<<LSB, MAKING A MASK

        //CLEAR THE FIELD
        MVN     R4,R4
        AND     R0,R0,R4

        //INSERT
        LSL     R5,R1,R2
        ORR     R0,R0,R5


        POP     {R4,R5,R6}
        BX      LR


        .end
