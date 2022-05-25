
_main:

;Test1.c,1 :: 		void main(){
;Test1.c,2 :: 		UART1_Init(9600);
	MOVLW      129
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;Test1.c,3 :: 		UART1_Write(0x13);
	MOVLW      19
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;Test1.c,4 :: 		UART1_Write(0x1);
	MOVLW      1
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;Test1.c,5 :: 		UART1_Write(0x5);
	MOVLW      5
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;Test1.c,6 :: 		UART1_Write(0x10);
	MOVLW      16
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;Test1.c,7 :: 		UART1_Write(0x11);
	MOVLW      17
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;Test1.c,8 :: 		UART1_Write(0x12);
	MOVLW      18
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;Test1.c,9 :: 		UART1_Write(0x13);
	MOVLW      19
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;Test1.c,10 :: 		UART1_Write(0x14);
	MOVLW      20
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;Test1.c,11 :: 		UART1_Write(0x37);
	MOVLW      55
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;Test1.c,12 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
