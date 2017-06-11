        .syntax     unified
	.cpu        cortex-m4
        .text
        .thumb_func
        .align       2

// int32_t minimum_asm(int32_t R0_data[], int32_t R1_count)

        .global     minimum_asm
        //R0 = array address
        //R1 = count
        //R2 = current data
        //R3 = current min
minimum_asm:
        //setup R3 and R2
        LDR         R3,[R0]
        MOV         R2,R3

loop:   // if(R2 < R3) R3 = R2
        CMP         R2,R3
        IT          LT
        MOVLT       R3,R2

        // move to the next variable in the array
        LDR         R2,[R0],4

        // evaluate the condition to decide whether to loop again
        SUB         R1,R1,1
        CMP         R1,0
        BNE         loop

        // setup the return value
        MOV         R0,R3
        BX          LR

        .end

