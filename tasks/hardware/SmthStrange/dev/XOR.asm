#include <p16f877.inc>  
    CBLOCK  0x20            ;Начало блока переменных
VAR1                        ;отладочная переменная
Delay1
Delay2
Num
byteAddr
tmpByte
    ENDC                    ;конец блока переменных

    org     0x00            ;начало прогрtb
    GOTO    initport        ;запуск с иниализации


initport:
    BSF     STATUS,RP0      ;Перейти в BANK1
    MOVLW   B'00000000'     ;записываем маску в рабочий регистр
    MOVWF   TRISC           ;записываем все 0 в TRISC, все порты на выход
    MOVWF   TRISD           ;записываем все 0 в TRISD, все порты на выход
    MOVLW   B'11111111'     ;записываем маску в рабочий регистр
    MOVWF   TRISB           ;записываем все 1 в TRISB, все порты на вход
    BCF STATUS,RP0          ;переход в банк 0
    MOVLW   B'00000000'     ;записываем все 0 в рабочий регистр
    MOVWF   PORTC           ;ставим все биты порта C в 0
    MOVWF   PORTD           ;ставим все биты порта D в 0

START
    movlw   low (STR_1 - 1)   
    CALL    SEND_STRING
    GOTO    START


TIME                      
     MOVLW     0          
TIME1                       
     MOVWF     Delay1              
     MOVWF     Delay2              
OffDelayLoop:
     decfsz    Delay1,f            
     goto      OffDelayLoop         
     decfsz    Delay2,f            
     goto      OffDelayLoop        
     return                        

SHOW_SYM:
sym0:
    MOVF    VAR1, W
    XORLW   7               ;Сравнить VAR1 и 0

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    sym1            ;Если не равны, перейти дальше

    MOVLW   B'00111111'
    MOVWF   PORTC
    MOVLW   B'01000100'
    MOVWF   PORTD
    GOTO    show_ret

sym1:
    MOVF    VAR1, W
    XORLW   2

    BTFSS   STATUS,Z         ;Пропустить, если равны
    GOTO    sym2             ;Если не равны, перейти дальше

    MOVLW   B'00011000'
    MOVWF   PORTC
    MOVLW   B'00000100'
    MOVWF   PORTD
    GOTO    show_ret

sym2:
    MOVF    VAR1, W
    XORLW   9

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    sym3            ;Если не равны, перейти дальше

    MOVLW   B'00110110'
    MOVWF   PORTC
    MOVLW   B'10001000'
    MOVWF   PORTD
    GOTO show_ret

sym3:
    MOVF    VAR1, W
    XORLW   4

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    sym4            ;Если не равны, перейти дальше

    MOVLW   B'11111100'
    MOVWF   PORTC
    MOVLW   B'00001000'
    MOVWF   PORTD
    GOTO show_ret

sym4:
    MOVF    VAR1, W
    XORLW   3

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    sym5            ;Если не равны, перейти дальше

    MOVLW   B'00011001'
    MOVWF   PORTC
    MOVLW   B'10001000'
    MOVWF   PORTD
    GOTO show_ret

sym5:
    MOVF    VAR1, W
    XORLW   0xc

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    sym6            ;Если не равны, перейти дальше

    MOVLW   B'11101101'
    MOVWF   PORTC
    MOVLW   B'10001000'
    MOVWF   PORTD
    GOTO show_ret

sym6:
    MOVF    VAR1, W
    XORLW   5

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    sym7            ;Если не равны, перейти дальше

    MOVLW   B'11101111'
    MOVWF   PORTC
    MOVLW   B'10001000'
    MOVWF   PORTD
    GOTO show_ret

sym7:
    MOVF    VAR1, W
    XORLW   0xe

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    sym8            ;Если не равны, перейти дальше

    MOVLW   B'00111000'
    MOVWF   PORTC
    MOVLW   B'00000000'
    MOVWF   PORTD
    GOTO show_ret

sym8:
    MOVF    VAR1, W
    XORLW   1

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    sym9            ;Если не равны, перейти дальше

    MOVLW   B'11111111'
    MOVWF   PORTC
    MOVLW   B'10001000'
    MOVWF   PORTD
    GOTO show_ret

sym9:
    MOVF    VAR1, W
    XORLW   0x10

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symA            ;Если не равны, перейти дальше

    MOVLW   B'11111101'
    MOVWF   PORTC
    MOVLW   B'10001000'
    MOVWF   PORTD
    GOTO show_ret     
    
symA:
    MOVF    VAR1, W
    XORLW   0x11

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symB            ;Если не равны, перейти дальше

    MOVLW   B'11111011'
    MOVWF   PORTC
    MOVLW   B'10001000'
    MOVWF   PORTD
    GOTO show_ret       

symB:
    MOVF    VAR1, W
    XORLW   4

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symC            ;Если не равны, перейти дальше

    MOVLW   B'00111100'
    MOVWF   PORTC
    MOVLW   B'00101010'
    MOVWF   PORTD
    GOTO show_ret    

symC:
    MOVF    VAR1, W
    XORLW   0xb

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symD            ;Если не равны, перейти дальше

    MOVLW   B'11100111'
    MOVWF   PORTC
    MOVLW   B'00000000'
    MOVWF   PORTD
    GOTO show_ret

symD:
    MOVF    VAR1, W
    XORLW   6

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symE            ;Если не равны, перейти дальше

    MOVLW   B'00111100'
    MOVWF   PORTC
    MOVLW   B'00100010'
    MOVWF   PORTD
    GOTO show_ret  

symE:
    MOVF    VAR1, W
    XORLW   0x15

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symF            ;Если не равны, перейти дальше

    MOVLW   B'11100111'
    MOVWF   PORTC
    MOVLW   B'10000000'
    MOVWF   PORTD
    GOTO show_ret

symF:
    MOVF    VAR1, W
    XORLW   8

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symG            ;Если не равны, перейти дальше

    MOVLW   B'11100011'
    MOVWF   PORTC
    MOVLW   B'10000000'
    MOVWF   PORTD
    GOTO show_ret

symG:
    MOVF    VAR1, W
    XORLW   0x17

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symH            ;Если не равны, перейти дальше

    MOVLW   B'11101111'
    MOVWF   PORTC
    MOVLW   B'00001000'
    MOVWF   PORTD
    GOTO show_ret

symH:
    MOVF    VAR1, W
    XORLW   0x12

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symI            ;Если не равны, перейти дальше

    MOVLW   B'11011011'
    MOVWF   PORTC
    MOVLW   B'10001000'
    MOVWF   PORTD
    GOTO show_ret

symI:
    MOVF    VAR1, W
    XORLW   0x19

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symJ            ;Если не равны, перейти дальше

    MOVLW   B'11100100'
    MOVWF   PORTC
    MOVLW   B'00100010'
    MOVWF   PORTD
    GOTO show_ret

symJ:
    MOVF    VAR1, W
    XORLW   0x14

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symK            ;Если не равны, перейти дальше

    MOVLW   B'11011110'
    MOVWF   PORTC
    MOVLW   B'00000000'
    MOVWF   PORTD
    GOTO show_ret

symK:
    MOVF    VAR1, W
    XORLW   0xd

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symL            ;Если не равны, перейти дальше

    MOVLW   B'00000011'
    MOVWF   PORTC
    MOVLW   B'10010100'
    MOVWF   PORTD
    GOTO show_ret

symL:
    MOVF    VAR1, W
    XORLW   0x1c

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symM            ;Если не равны, перейти дальше

    MOVLW   B'11000111'
    MOVWF   PORTC
    MOVLW   B'00000000'
    MOVWF   PORTD
    GOTO show_ret

symM:
    MOVF    VAR1, W
    XORLW   0xf

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symN            ;Если не равны, перейти дальше

    MOVLW   B'11011011'
    MOVWF   PORTC
    MOVLW   B'00000101'
    MOVWF   PORTD
    GOTO show_ret

symN:
    MOVF    VAR1, W
    XORLW   0x1e

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symO            ;Если не равны, перейти дальше

    MOVLW   B'11011011'
    MOVWF   PORTC
    MOVLW   B'00010001'
    MOVWF   PORTD
    GOTO show_ret

symO:
    MOVF    VAR1, W
    XORLW   0

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symP            ;Если не равны, перейти дальше

    MOVLW   B'11111111'
    MOVWF   PORTC
    MOVLW   B'00000000'
    MOVWF   PORTD
    GOTO show_ret

symP:
    MOVF    VAR1, W
    XORLW   0x18

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symQ            ;Если не равны, перейти дальше

    MOVLW   B'11110011'
    MOVWF   PORTC
    MOVLW   B'10001000'
    MOVWF   PORTD
    GOTO show_ret

symQ:
    MOVF    VAR1, W
    XORLW   0x13

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symR            ;Если не равны, перейти дальше

    MOVLW   B'11111111'
    MOVWF   PORTC
    MOVLW   B'00010000'
    MOVWF   PORTD
    GOTO show_ret

symR:
    MOVF    VAR1, W
    XORLW   0x1a

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symS            ;Если не равны, перейти дальше

    MOVLW   B'11110011'
    MOVWF   PORTC
    MOVLW   B'10011000'
    MOVWF   PORTD
    GOTO show_ret

symS:
    MOVF    VAR1, W
    XORLW   0x23

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symT            ;Если не равны, перейти дальше

    MOVLW   B'11101101'
    MOVWF   PORTC
    MOVLW   B'10001000'
    MOVWF   PORTD
    GOTO show_ret

symT:
    MOVF    VAR1, W
    XORLW   0x16

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symU            ;Если не равны, перейти дальше

    MOVLW   B'11100000'
    MOVWF   PORTC
    MOVLW   B'00100010'
    MOVWF   PORTD
    GOTO show_ret

symU:
    MOVF    VAR1, W
    XORLW   0x25

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symV            ;Если не равны, перейти дальше

    MOVLW   B'11011111'
    MOVWF   PORTC
    MOVLW   B'00000000'
    MOVWF   PORTD
    GOTO show_ret

symV:
    MOVF    VAR1, W
    XORLW   0x20

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symW            ;Если не равны, перейти дальше

    MOVLW   B'11000011'
    MOVWF   PORTC
    MOVLW   B'01000100'
    MOVWF   PORTD
    GOTO show_ret

symW:
    MOVF    VAR1, W
    XORLW   0x21

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symX            ;Если не равны, перейти дальше

    MOVLW   B'00011011'
    MOVWF   PORTC
    MOVLW   B'01010000'
    MOVWF   PORTD
    GOTO show_ret

symX:
    MOVF    VAR1, W
    XORLW   0x22

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symY           ;Если не равны, перейти дальше

    MOVLW   B'00000000'
    MOVWF   PORTC
    MOVLW   B'01010101'
    MOVWF   PORTD
    GOTO show_ret

symY:
    MOVF    VAR1, W
    XORLW   0x1b

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symZ            ;Если не равны, перейти дальше

    MOVLW   B'00000000'
    MOVWF   PORTC
    MOVLW   B'00100101'
    MOVWF   PORTD
    GOTO show_ret

symZ:
    MOVF    VAR1, W
    XORLW   0x24

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symOpen         ;Если не равны, перейти дальше

    MOVLW   B'11100100'
    MOVWF   PORTC
    MOVLW   B'01000100'
    MOVWF   PORTD
    GOTO show_ret

symOpen:
    MOVF    VAR1, W
    XORLW   0x1d

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symClose        ;Если не равны, перейти дальше

    MOVLW   B'00000000'
    MOVWF   PORTC
    MOVLW   B'10100010'
    MOVWF   PORTD
    GOTO show_ret

symClose:
    MOVF    VAR1, W
    XORLW   0x26

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    symUnderline    ;Если не равны, перейти дальше

    MOVLW   B'00000000'
    MOVWF   PORTC
    MOVLW   B'00101010'
    MOVWF   PORTD
    GOTO show_ret

symUnderline:
    MOVF    VAR1, W
    XORLW   0x1f

    BTFSS   STATUS,Z        ;Пропустить, если равны
    GOTO    show_ret        ;Если не равны, перейти дальше

    MOVLW   B'00000100'
    MOVWF   PORTC
    MOVLW   B'00000000'
    MOVWF   PORTD
    GOTO show_ret
show_ret:
    RETURN

SEND_STRING:
    MOVWF    byteAddr    ; адрес первого байта
T_LOOP:    
    movlw    high C_TBL
    movwf    PCLATH    ; Страница памяти программ таблиц
    MOVFW    byteAddr    ; примем адрес байта
    CALL    C_TBL    ; Примем байт
    movwf    tmpByte    ; сохраним
    movlw    high SEND_STRING
    movwf    PCLATH    ; Восстановим страницу памяти программ
    movf    tmpByte, W
    XORLW   0x87
    SUBLW   0xAA
    movwf   VAR1
    CALL SHOW_SYM
    CALL TIME
    movfw    tmpByte    ;
    BTFSC    STATUS,Z    ; Проверка на конец строки, обычно на 0
    RETURN        ; 0 - уходим
T_WAIT:    
    INCF    byteAddr,F
    GOTO     T_LOOP
;-----------------------------
    ORG 0xf00        ; можно другое, желательно кратное 256, чтобы уместилось макс. 255 символов
    
C_TBL:    addwf    PCL
STR_1:    dt 0xa,0xe,0x1b,0x18,0x24,0x17,0x18,0x1d,0x11,0x12,0x17,0x10,0x26,0x17,0xe,0x20,0x26,0x11,0xa,0xd,0x2,0xf,0x2,0xd,0x25,0x0  

Main_End:
    END