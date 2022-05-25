
_lcg0:

;keychecker.c,11 :: 		unsigned char lcg0(void) {
;keychecker.c,12 :: 		seed0=((974  * seed0) + 4095) % 53528;
	MOVLW      206
	MOVWF      R0+0
	MOVLW      3
	MOVWF      R0+1
	MOVF       _seed0+0, 0
	MOVWF      R4+0
	MOVF       _seed0+1, 0
	MOVWF      R4+1
	CALL       _Mul_16X16_U+0
	MOVLW      255
	ADDWF      R0+0, 1
	MOVLW      15
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVLW      24
	MOVWF      R4+0
	MOVLW      209
	MOVWF      R4+1
	CALL       _Div_16X16_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	MOVWF      _seed0+0
	MOVF       R0+1, 0
	MOVWF      _seed0+1
;keychecker.c,13 :: 		return seed0 & 0xff;
	MOVLW      255
	ANDWF      _seed0+0, 0
	MOVWF      R0+0
;keychecker.c,14 :: 		}
L_end_lcg0:
	RETURN
; end of _lcg0

_lcg1:

;keychecker.c,16 :: 		unsigned char lcg1(void) {
;keychecker.c,17 :: 		seed1=((2204  * seed1) + 2196) % 45634;
	MOVLW      156
	MOVWF      R0+0
	MOVLW      8
	MOVWF      R0+1
	MOVF       _seed1+0, 0
	MOVWF      R4+0
	MOVF       _seed1+1, 0
	MOVWF      R4+1
	CALL       _Mul_16X16_U+0
	MOVLW      148
	ADDWF      R0+0, 1
	MOVLW      8
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVLW      66
	MOVWF      R4+0
	MOVLW      178
	MOVWF      R4+1
	CALL       _Div_16X16_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	MOVWF      _seed1+0
	MOVF       R0+1, 0
	MOVWF      _seed1+1
;keychecker.c,18 :: 		return seed1 & 0xff;
	MOVLW      255
	ANDWF      _seed1+0, 0
	MOVWF      R0+0
;keychecker.c,19 :: 		}
L_end_lcg1:
	RETURN
; end of _lcg1

_lcg2:

;keychecker.c,21 :: 		unsigned char lcg2(void) {
;keychecker.c,22 :: 		seed2=((3642  * seed2) + 1047) % 27663;
	MOVLW      58
	MOVWF      R0+0
	MOVLW      14
	MOVWF      R0+1
	MOVF       _seed2+0, 0
	MOVWF      R4+0
	MOVF       _seed2+1, 0
	MOVWF      R4+1
	CALL       _Mul_16X16_U+0
	MOVLW      23
	ADDWF      R0+0, 1
	MOVLW      4
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVLW      15
	MOVWF      R4+0
	MOVLW      108
	MOVWF      R4+1
	CALL       _Div_16X16_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	MOVWF      _seed2+0
	MOVF       R0+1, 0
	MOVWF      _seed2+1
;keychecker.c,23 :: 		return seed2 & 0xff;
	MOVLW      255
	ANDWF      _seed2+0, 0
	MOVWF      R0+0
;keychecker.c,24 :: 		}
L_end_lcg2:
	RETURN
; end of _lcg2

_lcg3:

;keychecker.c,26 :: 		unsigned char lcg3(void) {
;keychecker.c,27 :: 		seed3=((4266  * seed3) + 2245) % 55961;
	MOVLW      170
	MOVWF      R0+0
	MOVLW      16
	MOVWF      R0+1
	MOVF       _seed3+0, 0
	MOVWF      R4+0
	MOVF       _seed3+1, 0
	MOVWF      R4+1
	CALL       _Mul_16X16_U+0
	MOVLW      197
	ADDWF      R0+0, 1
	MOVLW      8
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVLW      153
	MOVWF      R4+0
	MOVLW      218
	MOVWF      R4+1
	CALL       _Div_16X16_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	MOVWF      _seed3+0
	MOVF       R0+1, 0
	MOVWF      _seed3+1
;keychecker.c,28 :: 		return seed3 & 0xff;
	MOVLW      255
	ANDWF      _seed3+0, 0
	MOVWF      R0+0
;keychecker.c,29 :: 		}
L_end_lcg3:
	RETURN
; end of _lcg3

_main:

;keychecker.c,31 :: 		void main() {
;keychecker.c,32 :: 		UART1_Init(9600);
	MOVLW      129
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;keychecker.c,33 :: 		check_flag += 1;
	INCF       _check_flag+0, 1
;keychecker.c,34 :: 		for ( ii = 0; ii < 100; ii = ii + 1 )
	CLRF       _ii+0
	CLRF       _ii+1
L_main0:
	MOVLW      128
	XORWF      _ii+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main8
	MOVLW      100
	SUBWF      _ii+0, 0
L__main8:
	BTFSC      STATUS+0, 0
	GOTO       L_main1
;keychecker.c,36 :: 		lcg0();
	CALL       _lcg0+0
;keychecker.c,37 :: 		lcg1();
	CALL       _lcg1+0
;keychecker.c,38 :: 		lcg2();
	CALL       _lcg2+0
;keychecker.c,39 :: 		lcg3();
	CALL       _lcg3+0
;keychecker.c,34 :: 		for ( ii = 0; ii < 100; ii = ii + 1 )
	INCF       _ii+0, 1
	BTFSC      STATUS+0, 2
	INCF       _ii+1, 1
;keychecker.c,40 :: 		}
	GOTO       L_main0
L_main1:
;keychecker.c,41 :: 		UART1_Write(lcg0());
	CALL       _lcg0+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,42 :: 		UART1_Write(lcg1());
	CALL       _lcg1+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,43 :: 		UART1_Write(lcg2());
	CALL       _lcg2+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,44 :: 		UART1_Write(lcg3());
	CALL       _lcg3+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,45 :: 		UART1_Write(lcg2());
	CALL       _lcg2+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,46 :: 		UART1_Write(lcg1());
	CALL       _lcg1+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,47 :: 		UART1_Write(lcg0());
	CALL       _lcg0+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,48 :: 		UART1_Write(lcg0());
	CALL       _lcg0+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,49 :: 		UART1_Write(lcg1());
	CALL       _lcg1+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,50 :: 		UART1_Write(lcg2());
	CALL       _lcg2+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,51 :: 		UART1_Write(lcg3());
	CALL       _lcg3+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,52 :: 		UART1_Write(lcg3());
	CALL       _lcg3+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,53 :: 		UART1_Write(lcg2());
	CALL       _lcg2+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,54 :: 		UART1_Write(lcg1());
	CALL       _lcg1+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,55 :: 		UART1_Write(lcg0());
	CALL       _lcg0+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,56 :: 		UART1_Write(lcg1());
	CALL       _lcg1+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;keychecker.c,58 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
