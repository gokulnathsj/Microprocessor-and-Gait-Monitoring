SIM_SCGC5   EQU 0x40048038 ;SIM_SCGC5 address
PORTB_PCR18 EQU 0x4004A000 + 4 * 18 ;PORTB_PCR18 address 
PORTB_PCR19 EQU 0x4004A000 + 4 * 19 ;PORTB_PCR19 address 
PORTD_PCR1  EQU 0x4004C000 + 4 * 1 ;PORTD_PCR1 address
GPIOB_PSOR  EQU 0x400FF044 ;GPIOB_PSOR address 
GPIOB_PCOR  EQU 0x400FF048 ;GPIOB_PCOR address 
GPIOB_PTOR  EQU 0x400FF04C ;GPIOB_PTOR address 
GPIOB_PDDR  EQU 0x400FF054 ;GPIOB_PDDR address 
GPIOD_PSOR  EQU 0x400FF0C4 ;GPIOD_PSOR address 
GPIOD_PCOR  EQU 0x400FF0C8 ;GPIOD_PCOR address 
GPIOD_PDIR  EQU 0x400FF0D0 ;GPIOD_PDIR address
GPIOD_PDDR  EQU 0x400FF0D4 ;GPIOD_PDDR address
BLUE_MASK   EQU 0x00000002 
RED_MASK    EQU 0x00040000 
GREEN_MASK  EQU 0x00080000
	
	
DELAY_CNT EQU 0X00800000
		AREA asm_area, CODE, READONLY
		EXPORT __main
		ENTRY
__main	PROC
		BL init_gpio

loop	
		BL redtoggle 
		LDR R0, =DELAY_CNT 
		BL delay 
		BL redoff 
		LDR R0, =DELAY_CNT 
		BL delay 
		B loop
		
redon
		LDR R0,=GPIOB_PCOR 		;Load address of GPIOB_PCOR to R0 
		LDR R1,=RED_MASK 		;Load value to R1 
		STR R1,[R0] 			;Put value into GPIOB_PCOR 
		BX LR
		
redoff
		LDR R0,=GPIOB_PSOR 		;Load address of GPIOB_PSOR to R0 
		LDR R1,=RED_MASK 		;Load value to R1 
		STR R1,[R0] 			;Put value into GPIOB_PSOR 
		BX LR
		
redtoggle
		LDR R0,=GPIOB_PTOR 		;Load address of GPIOD_PTOR to R0 
		LDR R1,=RED_MASK 		;Load value to R1 
		STR R1,[R0] 			;Put value into GPIOD_PTOR
		BX LR
		
delay
		SUBS R0, #1 
		BNE delay 
		BX LR
init_gpio							; Turns on clocks for PORTB and PORTD 
		LDR R0,=SIM_SCGC5 			;Load address of SIM_SCGC5 to R0 
		LDR R1,[R0] 				;Get original value of SIM_SCGC5 
		LDR R2,=0x00001400 			;Load mask for bits to set to R2 
		ORRS R1,R2 					;Set bits with OR of orig val and mask 
		STR R1,[R0] 				;Put new value back into SIM_SCGC5
		
									; Setup PORTB Pin 18 to be GPIO 
		LDR R0,=PORTB_PCR18 		;Load address of PORTB_PCR18 to R0
		LDR R1,=0x00000100 			;Load new value to R1 (Enabling MUX for ;GPIO operation)
		STR R1,[R0] 				;Put value into PORTB_PCR18
		
		
									; Setup PORTB Pin 19 to be GPIO 
		LDR R0,=PORTB_PCR19 		;Load address of PORTB_PCR19 to R0 
		LDR R1,=0x00000100 			;Load new value to R1 (Enabling MUX for ;GPIO operation)
		STR R1,[R0]				    ;Put value into PORTB_PCR19

									; Setup PORTD Pin 1 to be GPIO 
		LDR R0,=PORTD_PCR1 			;Load address of PORTD_PCR1 to R0 
		LDR R1,=0x00000100 			;Load new value to R1 (Enabling MUX for ;GPIO operation)
		STR R1,[R0] 				;Put value into PORTD_PCR1
		
									;Setup R2 for mask for Green and Red LED control lines 
		LDR R2,= 0x000C0000			; Pin 18 and Pin 19 of PortB
		
									;Set bits in DDR register to enable outputs to drive LEDs 
		LDR R0,=GPIOB_PDDR 			;Load address of GPIOB_PDDR to R0
		LDR R1,[R0] 				;Get original value of GPIOB_PDDR 
		ORRS R1,R2 					;Set bits with OR of orig val and mask 
		STR R1,[R0] 				;Put new value back into GPIOB_PDDR
		
									;Turn off LEDs by setting control lines 
		LDR R0,=GPIOB_PSOR 			;Load address of GPIOB_PSOR to R0 
		LDR R1,[R0]				    ;Get original value of GPIOB_PSOR 
		ORRS R1,R2 					;Set bits with OR of orig val and mask 
		STR R1,[R0] 				;Put new value back into GPIOB_PSOR
		
									;Setup R2 for mask for Blue LED control line
		LDR R2,=0x00000002 			;Pin 1 of PortD

									;Set bits in DDR register to enable outputs to drive LEDs 
									;and ensure inputs are clear 
	    LDR R0,=GPIOD_PDDR 			;Load address of GPIOD_PDDR to R0 
		LDR R1,[R0] 				;Get original value of GPIOD_PDDR into R1 
		ORRS R1,R2 					;OR original value with mask to set bits 
		ANDS R1,R3 					;AND value with mask to clear bits 
		STR R1,[R0] 				;Put new value back into GPIOD_PDDR
	
									;Turn off LEDs by setting control lines
		LDR R0,=GPIOD_PSOR 			;Load address of GPIOD_PSOR to R0 
		LDR R1,[R0] 				;Get original value of GPIOD_PSOR into R1 
		ORRS R1,R2 					;OR original value with mask to set bits
		STR R1,[R0] 				;Put new value back into GPIOD_PSOR
		BX LR
		ENDP
		END