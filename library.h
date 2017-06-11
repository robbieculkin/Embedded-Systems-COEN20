/* File: LIBRARY.H */

#ifndef __LIBRARY_H
#define __LIBRARY_H

#define	HEADER		"STM32F429I-DISCO"
#define	ERROR_FLAG	"ERR"

void		InitializeHardware(char *header, char *footer) ;
void		WaitForPushButton(void) ;
unsigned	PrintBits(int bin[]) ;
void		PrintByte(uint8_t byte) ;
void		ClearDisplay(void) ;
uint32_t	GetClockCycleCount(void) ;

#endif
