        .syntax     unified
	.cpu        cortex-m4
        .text
        .thumb_func
        .align       2

// uint32_t  Remainder2(int32_t s32, int32_t k) ;

        .global     Remainder2
Remainder2: LDR         R2,=1
            LSL         R2,R2,R1            //1 << k
            SUB         R3,R2,1             //(1 << k) - 1
            AND         R3,R3,R0            //COMPUTE MODULUS
            AND         R2,R2,R0,ASR 31     //WANT ALL 1'S IF NEGATIVE
            SUB         R0,R3,R2            //(1 << k) - 1 - ((1<<K) & (s32 >> 31))
            BX          LR

        .end

