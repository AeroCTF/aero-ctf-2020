
_crc_ccitt_update:

;Modifer.c,8 :: 		void crc_ccitt_update (unsigned char dt)
;Modifer.c,10 :: 		crc = 0;
	CLRF       _crc+0
	CLRF       _crc+1
;Modifer.c,11 :: 		dt ^= crc&255;
	MOVLW      255
	ANDWF      _crc+0, 0
	MOVWF      R0+0
	MOVF       R0+0, 0
	XORWF      FARG_crc_ccitt_update_dt+0, 1
;Modifer.c,12 :: 		dt ^= dt << 4;
	MOVF       FARG_crc_ccitt_update_dt+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       R0+0, 0
	XORWF      FARG_crc_ccitt_update_dt+0, 1
;Modifer.c,13 :: 		crc = (((unsigned int)dt << 8) | ((crc>>8)&255));
	MOVF       FARG_crc_ccitt_update_dt+0, 0
	MOVWF      R1+0
	CLRF       R1+1
	MOVF       R1+0, 0
	MOVWF      R3+1
	CLRF       R3+0
	MOVF       _crc+1, 0
	MOVWF      R0+0
	CLRF       R0+1
	MOVLW      255
	ANDWF      R0+0, 1
	MOVLW      0
	ANDWF      R0+1, 1
	MOVF       R0+0, 0
	IORWF      R3+0, 0
	MOVWF      _crc+0
	MOVF       R3+1, 0
	IORWF      R0+1, 0
	MOVWF      _crc+1
;Modifer.c,14 :: 		crc ^= (unsigned char)(dt >> 4);
	MOVF       FARG_crc_ccitt_update_dt+0, 0
	MOVWF      R0+0
	RRF        R0+0, 1
	BCF        R0+0, 7
	RRF        R0+0, 1
	BCF        R0+0, 7
	RRF        R0+0, 1
	BCF        R0+0, 7
	RRF        R0+0, 1
	BCF        R0+0, 7
	MOVF       R0+0, 0
	XORWF      _crc+0, 1
	MOVLW      0
	XORWF      _crc+1, 1
;Modifer.c,15 :: 		crc ^= ((unsigned int)dt << 3);
	MOVF       FARG_crc_ccitt_update_dt+0, 0
	MOVWF      R3+0
	CLRF       R3+1
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       R0+0, 0
	XORWF      _crc+0, 1
	MOVF       R0+1, 0
	XORWF      _crc+1, 1
;Modifer.c,16 :: 		}
L_end_crc_ccitt_update:
	RETURN
; end of _crc_ccitt_update

_main:

;Modifer.c,18 :: 		void main() {
;Modifer.c,19 :: 		error = Soft_UART_Init(&PORTB, 1, 2,9600, 0);
	MOVLW      PORTB+0
	MOVWF      FARG_Soft_UART_Init_port+0
	MOVLW      1
	MOVWF      FARG_Soft_UART_Init_rx_pin+0
	MOVLW      2
	MOVWF      FARG_Soft_UART_Init_tx_pin+0
	MOVLW      128
	MOVWF      FARG_Soft_UART_Init_baud_rate+0
	MOVLW      37
	MOVWF      FARG_Soft_UART_Init_baud_rate+1
	CLRF       FARG_Soft_UART_Init_baud_rate+2
	CLRF       FARG_Soft_UART_Init_baud_rate+3
	CLRF       FARG_Soft_UART_Init_inverted+0
	CALL       _Soft_UART_Init+0
	MOVF       R0+0, 0
	MOVWF      _error+0
;Modifer.c,20 :: 		for(i = 0; i < 38; i++){
	CLRF       _i+0
L_main0:
	MOVLW      128
	XORWF      _i+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      38
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_main1
;Modifer.c,21 :: 		do{
L_main3:
;Modifer.c,22 :: 		dat[i] = Soft_UART_Read(&error);
	MOVF       _i+0, 0
	ADDLW      _dat+0
	MOVWF      FLOC__main+0
	MOVLW      _error+0
	MOVWF      FARG_Soft_UART_Read_error+0
	CALL       _Soft_UART_Read+0
	MOVF       FLOC__main+0, 0
	MOVWF      FSR
	MOVF       R0+0, 0
	MOVWF      INDF+0
;Modifer.c,23 :: 		Soft_UART_Write(dat[i]);
	MOVF       _i+0, 0
	ADDLW      _dat+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_Soft_UART_Write_udata+0
	CALL       _Soft_UART_Write+0
;Modifer.c,24 :: 		}while (error);
	MOVF       _error+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_main3
;Modifer.c,20 :: 		for(i = 0; i < 38; i++){
	INCF       _i+0, 1
;Modifer.c,26 :: 		}
	GOTO       L_main0
L_main1:
;Modifer.c,28 :: 		for(i = 0; i < 32; i++){
	CLRF       _i+0
L_main6:
	MOVLW      128
	XORWF      _i+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      32
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_main7
;Modifer.c,29 :: 		crc_ccitt_update(dat[i+5]);
	MOVLW      5
	ADDWF      _i+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      _i+0, 7
	MOVLW      255
	MOVWF      R0+1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVF       R0+0, 0
	ADDLW      _dat+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_crc_ccitt_update_dt+0
	CALL       _crc_ccitt_update+0
;Modifer.c,30 :: 		if(crc == (flag[i]^key[i]))
	MOVLW      2
	MOVWF      R0+0
	MOVF       _i+0, 0
	MOVWF      R4+0
	CALL       _Mul_8X8_U+0
	MOVF       R0+0, 0
	ADDLW      _flag+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      R0+0
	INCF       FSR, 1
	MOVF       INDF+0, 0
	MOVWF      R0+1
	MOVF       _i+0, 0
	ADDLW      _key+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORWF      R0+0, 0
	MOVWF      R2+0
	MOVF       R0+1, 0
	MOVWF      R2+1
	MOVLW      0
	XORWF      R2+1, 1
	MOVF       _crc+1, 0
	XORWF      R2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main13
	MOVF       R2+0, 0
	XORWF      _crc+0, 0
L__main13:
	BTFSS      STATUS+0, 2
	GOTO       L_main9
;Modifer.c,31 :: 		continue;
	GOTO       L_main8
L_main9:
;Modifer.c,33 :: 		return;
	GOTO       L_end_main
;Modifer.c,34 :: 		}
L_main8:
;Modifer.c,28 :: 		for(i = 0; i < 32; i++){
	INCF       _i+0, 1
;Modifer.c,34 :: 		}
	GOTO       L_main6
L_main7:
;Modifer.c,36 :: 		Soft_UART_Write('R');
	MOVLW      82
	MOVWF      FARG_Soft_UART_Write_udata+0
	CALL       _Soft_UART_Write+0
;Modifer.c,37 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;Modifer.c,38 :: 		Soft_UART_Write('e');
	MOVLW      101
	MOVWF      FARG_Soft_UART_Write_udata+0
	CALL       _Soft_UART_Write+0
;Modifer.c,39 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;Modifer.c,40 :: 		Soft_UART_Write('s');
	MOVLW      115
	MOVWF      FARG_Soft_UART_Write_udata+0
	CALL       _Soft_UART_Write+0
;Modifer.c,41 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;Modifer.c,42 :: 		Soft_UART_Write('p');
	MOVLW      112
	MOVWF      FARG_Soft_UART_Write_udata+0
	CALL       _Soft_UART_Write+0
;Modifer.c,43 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;Modifer.c,44 :: 		Soft_UART_Write('e');
	MOVLW      101
	MOVWF      FARG_Soft_UART_Write_udata+0
	CALL       _Soft_UART_Write+0
;Modifer.c,45 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;Modifer.c,46 :: 		Soft_UART_Write('c');
	MOVLW      99
	MOVWF      FARG_Soft_UART_Write_udata+0
	CALL       _Soft_UART_Write+0
;Modifer.c,47 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;Modifer.c,48 :: 		Soft_UART_Write('t');
	MOVLW      116
	MOVWF      FARG_Soft_UART_Write_udata+0
	CALL       _Soft_UART_Write+0
;Modifer.c,50 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
