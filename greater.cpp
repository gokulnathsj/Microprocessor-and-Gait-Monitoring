#include <MKL25Z4.H>

void UART0_init(void);
void LED_init(void); 
void LED_set(char value);
void delay(void);

int main (void) { 
	char c;
	UART0_init(); 
	LED_init();
	while (1) { 
		while(!(UART0->S1 & 0x20)) { } 
		c = UART0->D; 
		LED_set(c); 
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
	UART0->C2 = 0x04;
	SIM->SCGC5 |= 0x0200;
	PORTA->PCR[1] = 0x0200;
}


void LED_init(void) {
	SIM->SCGC5 |= 0x00001400;
	PORTB->PCR[18] = 0x100; 
	PTB->PDDR |= 0x40000;
	PTB->PSOR = 0x40000; 
	PORTB->PCR[19] = 0x100; 
	PTB->PDDR |= 0x80000; 
	PTB->PSOR = 0x80000;
	PORTD->PCR[1] = 0x100; 
	PTD->PDDR |= 0x00000002; 
	PTD->PSOR = 0x00000002;
}

void LED_set(char value){
	if (value =='g') {
		PTB->PCOR = 0x80000;
		delay();
		PTB->PSOR = 0x80000;		
	}		
	else if(value == 'r'){
		PTB->PCOR = 0x40000;
		delay();
		PTB->PSOR = 0x40000;
	}
	else{
		PTD->PCOR = 0x00000002;
		delay();
		PTD->PSOR = 0x00000002;
	}
	
}

void delay(void)
{
    uint32_t i,j;
    for (i=0; i<1000; i++)
    {
        for (j=0; j<1000; j++);
    }
}










