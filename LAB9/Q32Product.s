        .syntax		unified
        .cpu		cortex-m4
	.text
	.thumb_func
	.align		2

// Q32  Q32Product(Q32 a, Q32 b)

	.global		Q32Product
Q32Product:

	// The two parameters are passed to this function as follows:
	//
	// a<63..32> is in register R1// a<31..0> is in register R0
	// b<63..32> is in register R3// b<31..0> is in register R2
	//
	// Bits 63..32 of the product must be returned in register R1
	// Bits 31..0 of the product must be returned in register R0
	//
	// The value of all other registers must be preserved!

	PUSH		{R4,R5}

	// Start with 64-bit unsigned product

	UMULL		R5,R4,R0,R2		// LSW:R4 = MSHalf of LSW(A)xLSW(B)
	MUL		R5,R1,R3		// MSW:R5 = LSHalf of MSW(A)xMSW(B)
	UMLAL		R4,R5,R0,R3		// R5.R4 += 64 bits of LSW(A)xMSW(B)
	UMLAL		R4,R5,R1,R2		// R5.R4 += 64 bits of MSW(A)xLSW(B)

	// Apply correction terms to make signed

	AND		R2,R2,R1,ASR 31		// R2 = (a < 0) ? b<31..0> : 0
        SUB		R5,R5,R2		// R5 = R5 - ((a < 0) ? b<31..0> : 0)
        AND		R0,R0,R3,ASR 31		// R0 = (b < 0) ? a<31..0> : 0
	SUB		R1,R5,R0		// R1 = R5 - ((b < 0) ? a<31..0> : 0)
	MOV		R0,R4

	POP		{R4,R5}
	BX		LR			// Return to calling program.


        .end

