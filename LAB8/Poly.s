        .syntax     unified
	.cpu        cortex-m4
        .text
        .thumb_func
        .align       2

//extern float  Poly(float x, float coef[], uint32_t terms)
//                        S0        R0               R1
        zero:       .float 0.0
        one:        .float 1.0
        .global     Poly
Poly:   VLDR        S2,zero     //START AT 0
        VLDR        S3,one

        MOV         R3,R1
loop:   VLDMIA      R0!,{S1}    // load the coef

        VMLA.F32    S2,S1,S3    // S2 = S1*S3+S2
        VMUL.F32    S3,S0,S3    // X^i
                                //while r3 > 0, loop
        SUB         R3,R3,1
        CMP         R3,0
        BNE         loop

        VMOV        S0,S2
        BX          LR

        .end

