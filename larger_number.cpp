#include <MKL25Z4.H>	
#include <stdio.h>

void UART0_init(void);
void delay(void);

 int main(void){
	UART0_init();
	while(1){
		while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'E';		
		while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'n';
		while(!(UART0->S1 & 0x80)){}			
				UART0->D = 't';
		while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'e';
		while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'r';
		while(!(UART0->S1 & 0x80)){}			
				UART0->D = ' ';
		while(!(UART0->S1 & 0x80)){}	
				UART0->D = 'a';
		while(!(UART0->S1 & 0x80)){}	
				UART0->D = '&';
		while(!(UART0->S1 & 0x80)){}	
				UART0->D = 'b';
		while(!(UART0->S1 & 0x80)){}	
				UART0->D = ':';
			
		while(!(UART0->S1 & 0x20)){}
		int a = UART0->D;
			
		while(!(UART0->S1 & 0x80)){}			
				UART0->D = ' ';
			
		while(!(UART0->S1 & 0x20)){}
		int b = UART0->D;
			
		delay();			
		while(!(UART0->S1 & 0x80)){}			
				UART0->D = '\n';
		while(!(UART0->S1 & 0x80)){}			
				UART0->D = '\n';
			
		if(a > b){
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = a + 1;
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = ' ';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'i';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 's';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = ' ';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'b';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'i';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'g';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = '\n';				
		}
		else if(a < b){
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = b;
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = ' ';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'i';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 's';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = ' ';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'b';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'i';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'g';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = '\n';				
		}else{			
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'b';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'o';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 't';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'h';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = ' ';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'a';	
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'r';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'e';	
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = ' ';			
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'e';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'q';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'u';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'a';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = 'l';
			while(!(UART0->S1 & 0x80)){}			
				UART0->D = '\n';		
			}
	}
}

void UART0_init(void){
	SIM->SCGC4 |= 0x0400; 
	SIM->SOPT2 |= 0x04000000;
	UART0->C2 = 0; 
	UART0->BDH = 0x00; 
	UART0->BDL = 0x16;
	UART0->C4 = 0x0F; 
	UART0->C1 = 0x00;
	UART0->C2 = 0x0C;
	SIM->SCGC5 |= 0x0200;
	PORTA->PCR[1] = 0x0200;
	PORTA->PCR[2] = 0x0200;
}

void delay(void)
{
    uint32_t i,j;
    for (i=0; i<1000; i++)
    {
        for (j=0; j<1000; j++);
    }
}
