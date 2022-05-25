
_lcg0:

;RC4.c,32 :: 		unsigned char lcg0(void) {
;RC4.c,33 :: 		seed0=((974  * seed0) + 4095) % 53528;
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
;RC4.c,34 :: 		return seed0 & 0xff;
	MOVLW      255
	ANDWF      _seed0+0, 0
	MOVWF      R0+0
;RC4.c,35 :: 		}
L_end_lcg0:
	RETURN
; end of _lcg0

_lcg1:

;RC4.c,37 :: 		unsigned char lcg1(void) {
;RC4.c,38 :: 		seed1=((2204  * seed1) + 2196) % 45634;
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
;RC4.c,39 :: 		return seed1 & 0xff;
	MOVLW      255
	ANDWF      _seed1+0, 0
	MOVWF      R0+0
;RC4.c,40 :: 		}
L_end_lcg1:
	RETURN
; end of _lcg1

_lcg2:

;RC4.c,42 :: 		unsigned char lcg2(void) {
;RC4.c,43 :: 		seed2=((3642  * seed2) + 1047) % 27663;
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
;RC4.c,44 :: 		return seed2 & 0xff;
	MOVLW      255
	ANDWF      _seed2+0, 0
	MOVWF      R0+0
;RC4.c,45 :: 		}
L_end_lcg2:
	RETURN
; end of _lcg2

_lcg3:

;RC4.c,47 :: 		unsigned char lcg3(void) {
;RC4.c,48 :: 		seed3=((4266  * seed3) + 2245) % 55961;
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
;RC4.c,49 :: 		return seed3 & 0xff;
	MOVLW      255
	ANDWF      _seed3+0, 0
	MOVWF      R0+0
;RC4.c,50 :: 		}
L_end_lcg3:
	RETURN
; end of _lcg3

_S_swap:

;RC4.c,52 :: 		void S_swap( unsigned char a, unsigned char b )
;RC4.c,54 :: 		tmp = SS[a];
	MOVF       FARG_S_swap_a+0, 0
	ADDLW      _SS+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      _tmp+0
;RC4.c,55 :: 		SS[a] = SS[b];
	MOVF       FARG_S_swap_a+0, 0
	ADDLW      _SS+0
	MOVWF      R1+0
	MOVF       FARG_S_swap_b+0, 0
	ADDLW      _SS+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
	MOVWF      FSR
	MOVF       R0+0, 0
	MOVWF      INDF+0
;RC4.c,56 :: 		SS[b] = tmp;
	MOVF       FARG_S_swap_b+0, 0
	ADDLW      _SS+0
	MOVWF      FSR
	MOVF       _tmp+0, 0
	MOVWF      INDF+0
;RC4.c,57 :: 		}
L_end_S_swap:
	RETURN
; end of _S_swap

_KSA:

;RC4.c,59 :: 		int KSA()
;RC4.c,61 :: 		j = 0;
	CLRF       _j+0
	CLRF       _j+1
;RC4.c,63 :: 		for(i = 0; i < N; i++)
	CLRF       _i+0
	CLRF       _i+1
L_KSA0:
	MOVLW      0
	SUBWF      _i+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__KSA49
	MOVLW      64
	SUBWF      _i+0, 0
L__KSA49:
	BTFSC      STATUS+0, 0
	GOTO       L_KSA1
;RC4.c,64 :: 		SS[i] = i;
	MOVF       _i+0, 0
	ADDLW      _SS+0
	MOVWF      FSR
	MOVF       _i+0, 0
	MOVWF      INDF+0
;RC4.c,63 :: 		for(i = 0; i < N; i++)
	INCF       _i+0, 1
	BTFSC      STATUS+0, 2
	INCF       _i+1, 1
;RC4.c,64 :: 		SS[i] = i;
	GOTO       L_KSA0
L_KSA1:
;RC4.c,66 :: 		for(i = 0; i < N; i++) {
	CLRF       _i+0
	CLRF       _i+1
L_KSA3:
	MOVLW      0
	SUBWF      _i+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__KSA50
	MOVLW      64
	SUBWF      _i+0, 0
L__KSA50:
	BTFSC      STATUS+0, 0
	GOTO       L_KSA4
;RC4.c,67 :: 		j = (j + SS[i] + key[i % KEY_LEN]) % N;
	MOVF       _i+0, 0
	ADDLW      _SS+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	ADDWF      _j+0, 0
	MOVWF      FLOC__KSA+0
	MOVF       _j+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	MOVWF      FLOC__KSA+1
	MOVLW      17
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	MOVF       _i+0, 0
	MOVWF      R0+0
	MOVF       _i+1, 0
	MOVWF      R0+1
	CALL       _Div_16X16_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	ADDLW      _key+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	ADDWF      FLOC__KSA+0, 0
	MOVWF      R0+0
	MOVF       FLOC__KSA+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	MOVWF      R0+1
	MOVLW      64
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Div_16X16_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	MOVWF      _j+0
	MOVF       R0+1, 0
	MOVWF      _j+1
;RC4.c,68 :: 		S_swap(i, j);
	MOVF       _i+0, 0
	MOVWF      FARG_S_swap_a+0
	MOVF       _j+0, 0
	MOVWF      FARG_S_swap_b+0
	CALL       _S_swap+0
;RC4.c,66 :: 		for(i = 0; i < N; i++) {
	INCF       _i+0, 1
	BTFSC      STATUS+0, 2
	INCF       _i+1, 1
;RC4.c,69 :: 		}
	GOTO       L_KSA3
L_KSA4:
;RC4.c,71 :: 		return 0;
	CLRF       R0+0
	CLRF       R0+1
;RC4.c,72 :: 		}
L_end_KSA:
	RETURN
; end of _KSA

_PRGA:

;RC4.c,74 :: 		int PRGA()
;RC4.c,76 :: 		i = 0;
	CLRF       _i+0
	CLRF       _i+1
;RC4.c,77 :: 		j = 0;
	CLRF       _j+0
	CLRF       _j+1
;RC4.c,79 :: 		for ( n = 0; n < FLAG_LEN; n++ )
	CLRF       _n+0
	CLRF       _n+1
L_PRGA6:
	MOVLW      128
	XORWF      _n+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__PRGA52
	MOVLW      20
	SUBWF      _n+0, 0
L__PRGA52:
	BTFSC      STATUS+0, 0
	GOTO       L_PRGA7
;RC4.c,81 :: 		i = ( i + 1 ) % N;
	MOVF       _i+0, 0
	ADDLW      1
	MOVWF      R0+0
	MOVLW      0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      _i+1, 0
	MOVWF      R0+1
	MOVLW      64
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Div_16X16_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	MOVWF      _i+0
	MOVF       R0+1, 0
	MOVWF      _i+1
;RC4.c,82 :: 		j = ( j + SS[ i ] ) % N;
	MOVF       _i+0, 0
	ADDLW      _SS+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	ADDWF      _j+0, 0
	MOVWF      R0+0
	MOVF       _j+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	MOVWF      R0+1
	MOVLW      64
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Div_16X16_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	MOVWF      _j+0
	MOVF       R0+1, 0
	MOVWF      _j+1
;RC4.c,84 :: 		S_swap( i, j );
	MOVF       _i+0, 0
	MOVWF      FARG_S_swap_a+0
	MOVF       _j+0, 0
	MOVWF      FARG_S_swap_b+0
	CALL       _S_swap+0
;RC4.c,85 :: 		rnd = SS[ ( SS[ i ] + SS[ j ] ) % N ];
	MOVF       _i+0, 0
	ADDLW      _SS+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      R0+0
	MOVF       _j+0, 0
	ADDLW      _SS+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	ADDWF      R0+0, 1
	CLRF       R0+1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      64
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Div_16x16_S+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	ADDLW      _SS+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      _rnd+0
	CLRF       _rnd+1
	MOVLW      0
	MOVWF      _rnd+1
;RC4.c,87 :: 		flag[ n ] = rnd ^ flag[ n ];
	MOVF       _n+0, 0
	ADDLW      _flag+0
	MOVWF      R1+0
	MOVF       _n+0, 0
	ADDLW      _flag+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORWF      _rnd+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
	MOVWF      FSR
	MOVF       R0+0, 0
	MOVWF      INDF+0
;RC4.c,79 :: 		for ( n = 0; n < FLAG_LEN; n++ )
	INCF       _n+0, 1
	BTFSC      STATUS+0, 2
	INCF       _n+1, 1
;RC4.c,88 :: 		}
	GOTO       L_PRGA6
L_PRGA7:
;RC4.c,90 :: 		return 0;
	CLRF       R0+0
	CLRF       R0+1
;RC4.c,91 :: 		}
L_end_PRGA:
	RETURN
; end of _PRGA

_RC_4:

;RC4.c,93 :: 		int RC_4( )
;RC4.c,95 :: 		KSA( );
	CALL       _KSA+0
;RC4.c,97 :: 		PRGA( );
	CALL       _PRGA+0
;RC4.c,99 :: 		return 0;
	CLRF       R0+0
	CLRF       R0+1
;RC4.c,100 :: 		}
L_end_RC_4:
	RETURN
; end of _RC_4

_main:

;RC4.c,106 :: 		void main()
;RC4.c,108 :: 		i = 0xe;
	MOVLW      14
	MOVWF      _i+0
	MOVLW      0
	MOVWF      _i+1
;RC4.c,109 :: 		UART1_Init(9600);
	MOVLW      129
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;RC4.c,111 :: 		if( 0 == sendFlag ){
	MOVLW      0
	XORWF      _sendFlag+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_main9
;RC4.c,112 :: 		j = 0;
	CLRF       _j+0
	CLRF       _j+1
;RC4.c,113 :: 		while( j < 4 ){
L_main10:
	MOVLW      0
	SUBWF      _j+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main55
	MOVLW      4
	SUBWF      _j+0, 0
L__main55:
	BTFSC      STATUS+0, 0
	GOTO       L_main11
;RC4.c,114 :: 		dat = FLASH_Read( 0 );
	CLRF       FARG_FLASH_Read_address+0
	CLRF       FARG_FLASH_Read_address+1
	CALL       _FLASH_Read+0
	MOVF       R0+0, 0
	MOVWF      _dat+0
	MOVF       R0+1, 0
	MOVWF      _dat+1
;RC4.c,115 :: 		addrItm[2 + j*2]     = dat&0xff;
	MOVF       _j+0, 0
	MOVWF      R0+0
	MOVF       _j+1, 0
	MOVWF      R0+1
	MOVLW      2
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Mul_16X16_U+0
	MOVLW      2
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVF       R0+0, 0
	ADDLW      _addrItm+0
	MOVWF      FSR
	MOVLW      255
	ANDWF      _dat+0, 0
	MOVWF      R0+0
	MOVF       R0+0, 0
	MOVWF      INDF+0
;RC4.c,116 :: 		addrItm[2 + j*2 + 1] = dat >> 8;
	MOVF       _j+0, 0
	MOVWF      R0+0
	MOVF       _j+1, 0
	MOVWF      R0+1
	MOVLW      2
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Mul_16X16_U+0
	MOVLW      2
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	INCF       R0+0, 1
	BTFSC      STATUS+0, 2
	INCF       R0+1, 1
	MOVF       R0+0, 0
	ADDLW      _addrItm+0
	MOVWF      FSR
	MOVF       _dat+1, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      _dat+1, 7
	MOVLW      255
	MOVWF      R0+1
	MOVF       R0+0, 0
	MOVWF      INDF+0
;RC4.c,117 :: 		j = j + 1;
	INCF       _j+0, 1
	BTFSC      STATUS+0, 2
	INCF       _j+1, 1
;RC4.c,118 :: 		}
	GOTO       L_main10
L_main11:
;RC4.c,119 :: 		UART1_Write(0x13);
	MOVLW      19
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,120 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,121 :: 		UART1_Write(0x0A);
	MOVLW      10
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,122 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,123 :: 		UART1_Write(0x01);
	MOVLW      1
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,124 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,125 :: 		UART1_Write(0x00);
	CLRF       FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,126 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,127 :: 		UART1_Write(0x0d);
	MOVLW      13
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,128 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,129 :: 		ii = 0;
	CLRF       _ii+0
	CLRF       _ii+1
;RC4.c,130 :: 		while ( ii < 8 )
L_main12:
	MOVLW      128
	XORWF      _ii+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main56
	MOVLW      8
	SUBWF      _ii+0, 0
L__main56:
	BTFSC      STATUS+0, 0
	GOTO       L_main13
;RC4.c,132 :: 		UART1_Write(addrItm[ ii+2 ]);
	MOVLW      2
	ADDWF      _ii+0, 0
	MOVWF      R0+0
	MOVF       _ii+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	MOVWF      R0+1
	MOVF       R0+0, 0
	ADDLW      _addrItm+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,133 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,134 :: 		ii = ii + 1;
	INCF       _ii+0, 1
	BTFSC      STATUS+0, 2
	INCF       _ii+1, 1
;RC4.c,135 :: 		}
	GOTO       L_main12
L_main13:
;RC4.c,137 :: 		UART1_Write(0x37);
	MOVLW      55
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,138 :: 		Delay_ms(100);
	MOVLW      3
	MOVWF      R11+0
	MOVLW      138
	MOVWF      R12+0
	MOVLW      85
	MOVWF      R13+0
L_main14:
	DECFSZ     R13+0, 1
	GOTO       L_main14
	DECFSZ     R12+0, 1
	GOTO       L_main14
	DECFSZ     R11+0, 1
	GOTO       L_main14
	NOP
	NOP
;RC4.c,140 :: 		while ( i < 0x4e7 ) {
L_main15:
	MOVLW      4
	SUBWF      _i+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main57
	MOVLW      231
	SUBWF      _i+0, 0
L__main57:
	BTFSC      STATUS+0, 0
	GOTO       L_main16
;RC4.c,142 :: 		j = 0;
	CLRF       _j+0
	CLRF       _j+1
;RC4.c,143 :: 		while( j < 4 ){
L_main17:
	MOVLW      0
	SUBWF      _j+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main58
	MOVLW      4
	SUBWF      _j+0, 0
L__main58:
	BTFSC      STATUS+0, 0
	GOTO       L_main18
;RC4.c,144 :: 		dat = FLASH_Read( i+j );
	MOVF       _j+0, 0
	ADDWF      _i+0, 0
	MOVWF      FARG_FLASH_Read_address+0
	MOVF       _i+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      _j+1, 0
	MOVWF      FARG_FLASH_Read_address+1
	CALL       _FLASH_Read+0
	MOVF       R0+0, 0
	MOVWF      _dat+0
	MOVF       R0+1, 0
	MOVWF      _dat+1
;RC4.c,145 :: 		addrItm[2 + j*2]     = dat&0xff;
	MOVF       _j+0, 0
	MOVWF      R0+0
	MOVF       _j+1, 0
	MOVWF      R0+1
	MOVLW      2
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Mul_16X16_U+0
	MOVLW      2
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVF       R0+0, 0
	ADDLW      _addrItm+0
	MOVWF      FSR
	MOVLW      255
	ANDWF      _dat+0, 0
	MOVWF      R0+0
	MOVF       R0+0, 0
	MOVWF      INDF+0
;RC4.c,146 :: 		addrItm[2 + j*2 + 1] = dat >> 8;
	MOVF       _j+0, 0
	MOVWF      R0+0
	MOVF       _j+1, 0
	MOVWF      R0+1
	MOVLW      2
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Mul_16X16_U+0
	MOVLW      2
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	INCF       R0+0, 1
	BTFSC      STATUS+0, 2
	INCF       R0+1, 1
	MOVF       R0+0, 0
	ADDLW      _addrItm+0
	MOVWF      FSR
	MOVF       _dat+1, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      _dat+1, 7
	MOVLW      255
	MOVWF      R0+1
	MOVF       R0+0, 0
	MOVWF      INDF+0
;RC4.c,147 :: 		j = j + 1;
	INCF       _j+0, 1
	BTFSC      STATUS+0, 2
	INCF       _j+1, 1
;RC4.c,148 :: 		}
	GOTO       L_main17
L_main18:
;RC4.c,149 :: 		addrItm[0] = i >> 8;
	MOVF       _i+1, 0
	MOVWF      R0+0
	CLRF       R0+1
	MOVF       R0+0, 0
	MOVWF      _addrItm+0
;RC4.c,150 :: 		addrItm[1] = i&0xff;
	MOVLW      255
	ANDWF      _i+0, 0
	MOVWF      _addrItm+1
;RC4.c,155 :: 		UART1_Write(0x13);
	MOVLW      19
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,156 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,157 :: 		UART1_Write(0x0A);
	MOVLW      10
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,158 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,159 :: 		UART1_Write(0x01);
	MOVLW      1
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,160 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,161 :: 		ii = 0;
	CLRF       _ii+0
	CLRF       _ii+1
;RC4.c,162 :: 		while ( ii < 10 )
L_main19:
	MOVLW      128
	XORWF      _ii+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main59
	MOVLW      10
	SUBWF      _ii+0, 0
L__main59:
	BTFSC      STATUS+0, 0
	GOTO       L_main20
;RC4.c,164 :: 		UART1_Write(addrItm[ ii ]);
	MOVF       _ii+0, 0
	ADDLW      _addrItm+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,165 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,166 :: 		ii = ii + 1;
	INCF       _ii+0, 1
	BTFSC      STATUS+0, 2
	INCF       _ii+1, 1
;RC4.c,167 :: 		}
	GOTO       L_main19
L_main20:
;RC4.c,169 :: 		UART1_Write(0x37);
	MOVLW      55
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,170 :: 		Delay_ms(100);
	MOVLW      3
	MOVWF      R11+0
	MOVLW      138
	MOVWF      R12+0
	MOVLW      85
	MOVWF      R13+0
L_main21:
	DECFSZ     R13+0, 1
	GOTO       L_main21
	DECFSZ     R12+0, 1
	GOTO       L_main21
	DECFSZ     R11+0, 1
	GOTO       L_main21
	NOP
	NOP
;RC4.c,172 :: 		i = i + 4;
	MOVLW      4
	ADDWF      _i+0, 1
	BTFSC      STATUS+0, 0
	INCF       _i+1, 1
;RC4.c,173 :: 		}
	GOTO       L_main15
L_main16:
;RC4.c,175 :: 		UART1_Write(0x13);
	MOVLW      19
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,176 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,177 :: 		UART1_Write(0x01);
	MOVLW      1
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,178 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,179 :: 		UART1_Write(0x03);
	MOVLW      3
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,180 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,181 :: 		UART1_Write(0x01);
	MOVLW      1
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,182 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,183 :: 		UART1_Write(0x37);
	MOVLW      55
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;RC4.c,184 :: 		Delay_10ms();
	CALL       _Delay_10ms+0
;RC4.c,185 :: 		}
L_main9:
;RC4.c,186 :: 		check_flag = 0;
	CLRF       _check_flag+0
;RC4.c,188 :: 		if ( key[0] == 'C' )
	MOVF       _key+0, 0
	XORLW      67
	BTFSS      STATUS+0, 2
	GOTO       L_main22
;RC4.c,190 :: 		check_flag += 1;
	INCF       _check_flag+0, 1
;RC4.c,191 :: 		for ( ii = 0; ii < 100; ii = ii + 1 )
	CLRF       _ii+0
	CLRF       _ii+1
L_main23:
	MOVLW      128
	XORWF      _ii+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main60
	MOVLW      100
	SUBWF      _ii+0, 0
L__main60:
	BTFSC      STATUS+0, 0
	GOTO       L_main24
;RC4.c,193 :: 		lcg0();
	CALL       _lcg0+0
;RC4.c,194 :: 		lcg1();
	CALL       _lcg1+0
;RC4.c,195 :: 		lcg2();
	CALL       _lcg2+0
;RC4.c,196 :: 		lcg3();
	CALL       _lcg3+0
;RC4.c,191 :: 		for ( ii = 0; ii < 100; ii = ii + 1 )
	INCF       _ii+0, 1
	BTFSC      STATUS+0, 2
	INCF       _ii+1, 1
;RC4.c,197 :: 		}
	GOTO       L_main23
L_main24:
;RC4.c,198 :: 		if ( (key[ 1 ] ^ lcg0()) == 119 ) check_flag+=1;
	CALL       _lcg0+0
	MOVF       R0+0, 0
	XORWF      _key+1, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      119
	BTFSS      STATUS+0, 2
	GOTO       L_main26
	INCF       _check_flag+0, 1
L_main26:
;RC4.c,199 :: 		if ( (key[ 2 ] ^ lcg1()) == 101 ) check_flag+=1;
	CALL       _lcg1+0
	MOVF       R0+0, 0
	XORWF      _key+2, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      101
	BTFSS      STATUS+0, 2
	GOTO       L_main27
	INCF       _check_flag+0, 1
L_main27:
;RC4.c,200 :: 		if ( (key[ 3 ] ^ lcg2()) == 131 ) check_flag+=1;
	CALL       _lcg2+0
	MOVF       R0+0, 0
	XORWF      _key+3, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      131
	BTFSS      STATUS+0, 2
	GOTO       L_main28
	INCF       _check_flag+0, 1
L_main28:
;RC4.c,201 :: 		if ( (key[ 4 ] ^ lcg3()) == 58 ) check_flag+=1;
	CALL       _lcg3+0
	MOVF       R0+0, 0
	XORWF      _key+4, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      58
	BTFSS      STATUS+0, 2
	GOTO       L_main29
	INCF       _check_flag+0, 1
L_main29:
;RC4.c,202 :: 		if ( (key[ 5 ] ^ lcg2()) == 212 ) check_flag+=1;
	CALL       _lcg2+0
	MOVF       R0+0, 0
	XORWF      _key+5, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      212
	BTFSS      STATUS+0, 2
	GOTO       L_main30
	INCF       _check_flag+0, 1
L_main30:
;RC4.c,203 :: 		if ( (key[ 6 ] ^ lcg1()) == 106 ) check_flag+=1;
	CALL       _lcg1+0
	MOVF       R0+0, 0
	XORWF      _key+6, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      106
	BTFSS      STATUS+0, 2
	GOTO       L_main31
	INCF       _check_flag+0, 1
L_main31:
;RC4.c,204 :: 		if ( (key[ 7 ] ^ lcg0()) == 103 ) check_flag+=1;
	CALL       _lcg0+0
	MOVF       R0+0, 0
	XORWF      _key+7, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      103
	BTFSS      STATUS+0, 2
	GOTO       L_main32
	INCF       _check_flag+0, 1
L_main32:
;RC4.c,205 :: 		if ( (key[ 8 ] ^ lcg0()) == 96 ) check_flag+=1;
	CALL       _lcg0+0
	MOVF       R0+0, 0
	XORWF      _key+8, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      96
	BTFSS      STATUS+0, 2
	GOTO       L_main33
	INCF       _check_flag+0, 1
L_main33:
;RC4.c,206 :: 		if ( (key[ 9 ] ^ lcg1()) == 174 ) check_flag+=1;
	CALL       _lcg1+0
	MOVF       R0+0, 0
	XORWF      _key+9, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      174
	BTFSS      STATUS+0, 2
	GOTO       L_main34
	INCF       _check_flag+0, 1
L_main34:
;RC4.c,207 :: 		if ( (key[ 10 ] ^ lcg2()) == 43 ) check_flag+=1;
	CALL       _lcg2+0
	MOVF       R0+0, 0
	XORWF      _key+10, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      43
	BTFSS      STATUS+0, 2
	GOTO       L_main35
	INCF       _check_flag+0, 1
L_main35:
;RC4.c,208 :: 		if ( (key[ 11 ] ^ lcg3()) == 38 ) check_flag+=1;
	CALL       _lcg3+0
	MOVF       R0+0, 0
	XORWF      _key+11, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      38
	BTFSS      STATUS+0, 2
	GOTO       L_main36
	INCF       _check_flag+0, 1
L_main36:
;RC4.c,209 :: 		if ( (key[ 12 ] ^ lcg3()) == 53 ) check_flag+=1;
	CALL       _lcg3+0
	MOVF       R0+0, 0
	XORWF      _key+12, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      53
	BTFSS      STATUS+0, 2
	GOTO       L_main37
	INCF       _check_flag+0, 1
L_main37:
;RC4.c,210 :: 		if ( (key[ 13 ] ^ lcg2()) == 106 ) check_flag+=1;
	CALL       _lcg2+0
	MOVF       R0+0, 0
	XORWF      _key+13, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      106
	BTFSS      STATUS+0, 2
	GOTO       L_main38
	INCF       _check_flag+0, 1
L_main38:
;RC4.c,211 :: 		if ( (key[ 14 ] ^ lcg1()) == 174 ) check_flag+=1;
	CALL       _lcg1+0
	MOVF       R0+0, 0
	XORWF      _key+14, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      174
	BTFSS      STATUS+0, 2
	GOTO       L_main39
	INCF       _check_flag+0, 1
L_main39:
;RC4.c,212 :: 		if ( (key[ 15 ] ^ lcg0()) == 105 ) check_flag+=1;
	CALL       _lcg0+0
	MOVF       R0+0, 0
	XORWF      _key+15, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      105
	BTFSS      STATUS+0, 2
	GOTO       L_main40
	INCF       _check_flag+0, 1
L_main40:
;RC4.c,213 :: 		if ( (key[ 16 ] ^ lcg1()) == 129 ) check_flag+=1;
	CALL       _lcg1+0
	MOVF       R0+0, 0
	XORWF      _key+16, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      129
	BTFSS      STATUS+0, 2
	GOTO       L_main41
	INCF       _check_flag+0, 1
L_main41:
;RC4.c,214 :: 		}
L_main22:
;RC4.c,216 :: 		if ( check_flag == 17 )
	MOVF       _check_flag+0, 0
	XORLW      17
	BTFSS      STATUS+0, 2
	GOTO       L_main42
;RC4.c,218 :: 		RC_4( );
	CALL       _RC_4+0
;RC4.c,219 :: 		}
L_main42:
;RC4.c,220 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
