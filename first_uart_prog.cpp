#include <MKL25Z4.H> 

void UART0_init(void);

int main (void) {
	UART0_init();
	while (1) { 
		while(!(UART0->S1 & 0x80)) { }
		UART0->D = 1;
		while(!(UART0->S1 & 0x80)) { }
		UART0->D = 'o';
		while(!(UART0->S1 & 0x80)) { }
		UART0->D = 'K';
		while(!(UART0->S1 & 0x80)) { }
		UART0->D = 'U';
		while(!(UART0->S1 & 0x80)) { }
		UART0->D = 'L';
		while(!(UART0->S1 & 0x80)) { }
		UART0->D = ' ';
	}
}
void UART0_init(void) {
	SIM->SCGC4 |= 0x0400;
	SIM->SOPT2 |= 0x04000000; 
	
	UART0->C2 = 0; 
	UART0->BDH = 0x00;
	UART0->BDL = 0x16; 
	UART0->C4 = 0x0F;
	UART0->C1 = 0x00; 
	UART0->C2 = 0x08;
	
	SIM->SCGC5 |= 0x0200; 
	PORTA->PCR[2] = 0x0200;
}
