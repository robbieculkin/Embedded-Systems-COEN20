        .syntax     unified
	.cpu        cortex-m4
        .text
        .thumb_func
        .align       2

// void  PrintTwo(char* str, int num) ;

        .global     PrintTwo
PrintTwo:
        // Move whatever was in R4 and R5 onto the stack
        PUSH    {R4,R5,LR}

        // Preserve contents of R0 (the string) and R1(the number) in R4 and R5
        MOV     R4,R0
        MOV     R5,R1
        //Call printf
        BL      printf

        // Add 1 to the number to be printed
        ADD     R5,R5,1

        // Set up parameters by moving them from R4 and R5 back to R0 and R1
        MOV     R0,R4
        MOV     R1,R5
        //Call printf
        BL      printf
        // Put whatever was in R4 and R5 before the fcn ran back
        POP     {R4,R5,LR}
        //return
        BX         LR

        .end

