
_wait:

;transiver.c,5 :: 		void wait(){
;transiver.c,6 :: 		while(!UART1_Tx_Idle())
L_wait0:
	CALL       _UART1_Tx_Idle+0
	MOVF       R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_wait1
;transiver.c,7 :: 		continue;
	GOTO       L_wait0
L_wait1:
;transiver.c,8 :: 		}
L_end_wait:
	RETURN
; end of _wait

_UartSend:

;transiver.c,14 :: 		void UartSend(char *dat, char len){
;transiver.c,15 :: 		for(i = 0; i < len; i++){
	CLRF       _i+0
	CLRF       _i+1
L_UartSend2:
	MOVLW      128
	XORWF      _i+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__UartSend13
	MOVF       FARG_UartSend_len+0, 0
	SUBWF      _i+0, 0
L__UartSend13:
	BTFSC      STATUS+0, 0
	GOTO       L_UartSend3
;transiver.c,16 :: 		UART1_Write(dat[i]);
	MOVF       _i+0, 0
	ADDWF      FARG_UartSend_dat+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;transiver.c,17 :: 		Delay_ms(10);
	MOVLW      65
	MOVWF      R12+0
	MOVLW      238
	MOVWF      R13+0
L_UartSend5:
	DECFSZ     R13+0, 1
	GOTO       L_UartSend5
	DECFSZ     R12+0, 1
	GOTO       L_UartSend5
	NOP
;transiver.c,15 :: 		for(i = 0; i < len; i++){
	INCF       _i+0, 1
	BTFSC      STATUS+0, 2
	INCF       _i+1, 1
;transiver.c,18 :: 		}
	GOTO       L_UartSend2
L_UartSend3:
;transiver.c,19 :: 		}
L_end_UartSend:
	RETURN
; end of _UartSend

_UartSendPacket:

;transiver.c,21 :: 		void UartSendPacket(char cmd, char *dat, char len){
;transiver.c,22 :: 		UART1_Write(0x13);
	MOVLW      19
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;transiver.c,24 :: 		switch(cmd){
	GOTO       L_UartSendPacket6
;transiver.c,25 :: 		case WRITE_BLOCK:
L_UartSendPacket8:
;transiver.c,26 :: 		UART1_Write(len);
	MOVF       FARG_UartSendPacket_len+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;transiver.c,27 :: 		UART1_Write(WRITE_BLOCK);
	MOVLW      1
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;transiver.c,28 :: 		UartSend(dat, len);
	MOVF       FARG_UartSendPacket_dat+0, 0
	MOVWF      FARG_UartSend_dat+0
	MOVF       FARG_UartSendPacket_len+0, 0
	MOVWF      FARG_UartSend_len+0
	CALL       _UartSend+0
;transiver.c,29 :: 		break;
	GOTO       L_UartSendPacket7
;transiver.c,31 :: 		case EXECUTE:
L_UartSendPacket9:
;transiver.c,32 :: 		UART1_Write(0x1);
	MOVLW      1
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;transiver.c,33 :: 		UART1_Write(EXECUTE);
	MOVLW      3
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;transiver.c,34 :: 		UART1_Write(0x2);
	MOVLW      2
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;transiver.c,35 :: 		break;
	GOTO       L_UartSendPacket7
;transiver.c,36 :: 		}
L_UartSendPacket6:
	MOVF       FARG_UartSendPacket_cmd+0, 0
	XORLW      1
	BTFSC      STATUS+0, 2
	GOTO       L_UartSendPacket8
	MOVF       FARG_UartSendPacket_cmd+0, 0
	XORLW      3
	BTFSC      STATUS+0, 2
	GOTO       L_UartSendPacket9
L_UartSendPacket7:
;transiver.c,38 :: 		UART1_Write(0x37);
	MOVLW      55
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;transiver.c,39 :: 		}
L_end_UartSendPacket:
	RETURN
; end of _UartSendPacket

_main:

;transiver.c,43 :: 		void main(){
;transiver.c,44 :: 		UART1_Init(9600);
	MOVLW      129
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;transiver.c,46 :: 		UartSendPacket(WRITE_BLOCK, code1, 10);
	MOVLW      1
	MOVWF      FARG_UartSendPacket_cmd+0
	MOVLW      _code1+0
	MOVWF      FARG_UartSendPacket_dat+0
	MOVLW      10
	MOVWF      FARG_UartSendPacket_len+0
	CALL       _UartSendPacket+0
;transiver.c,47 :: 		Delay_100ms();
	CALL       _Delay_100ms+0
;transiver.c,48 :: 		UartSendPacket(WRITE_BLOCK, code1 + 10, 6);
	MOVLW      1
	MOVWF      FARG_UartSendPacket_cmd+0
	MOVLW      _code1+10
	MOVWF      FARG_UartSendPacket_dat+0
	MOVLW      6
	MOVWF      FARG_UartSendPacket_len+0
	CALL       _UartSendPacket+0
;transiver.c,49 :: 		Delay_ms(1000);
	MOVLW      26
	MOVWF      R11+0
	MOVLW      94
	MOVWF      R12+0
	MOVLW      110
	MOVWF      R13+0
L_main10:
	DECFSZ     R13+0, 1
	GOTO       L_main10
	DECFSZ     R12+0, 1
	GOTO       L_main10
	DECFSZ     R11+0, 1
	GOTO       L_main10
	NOP
;transiver.c,50 :: 		UartSendPacket(EXECUTE, 0, 0);
	MOVLW      3
	MOVWF      FARG_UartSendPacket_cmd+0
	CLRF       FARG_UartSendPacket_dat+0
	CLRF       FARG_UartSendPacket_len+0
	CALL       _UartSendPacket+0
;transiver.c,51 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
