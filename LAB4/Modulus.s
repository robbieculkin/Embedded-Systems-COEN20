        .syntax     unified
	.cpu        cortex-m4
        .text
        .thumb_func
        .align       2


        .global     Modulus
Modulus:SDIV        R3,R0,R1		// Find Quotient
        MLS         R3,R3,R1,R0     // Dividend - (Quotient * Divisor) = Remainder
        ADD         R2,R3,R1        // Remainder + Divisor

        // Now I will treat the value stored in R3 as the new dividend
        SDIV        R3,R2,R1		// Find Quotient
        MLS         R3,R3,R1,R2     // Dividend - (Quotient * Divisor) = Remainder
        MOV         R0,R3           // Put answer in the return slot
        BX          LR

        .end

