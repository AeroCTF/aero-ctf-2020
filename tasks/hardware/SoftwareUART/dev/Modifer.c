char error;
char dat[38];
short i;
char key[] = "1e9bfe04dc00d51c32acac6377d19a58";
unsigned int flag[] = {0x329,0x37d,0x2033,0x51ff,0x54d3,0xbdae,0xbdfb,0x32c,0x2546,0x2541,0x5485,0x31b3,0x206e,0x31b6,0xbdfa,0x54d6,0x7794,0x4026,0x455d,0x34c8,0x72ee,0x2541,0x203c,0x32b,0x31b4,0x4023,0x34cf,0x450d,0x4505,0x51fc,0x2517,0x6616};
unsigned int crc = 0;

void crc_ccitt_update (unsigned char dt)
{
    crc = 0;
	dt ^= crc&255;
	dt ^= dt << 4;
	crc = (((unsigned int)dt << 8) | ((crc>>8)&255));
	crc ^= (unsigned char)(dt >> 4);
	crc ^= ((unsigned int)dt << 3);
}

void main() {
    error = Soft_UART_Init(&PORTB, 1, 2,9600, 0);
    for(i = 0; i < 38; i++){
        do{
            dat[i] = Soft_UART_Read(&error);
            Soft_UART_Write(dat[i]);
        }while (error);

    }
    
    for(i = 0; i < 32; i++){
        crc_ccitt_update(dat[i+5]);
        if(crc == (flag[i]^key[i]))
            continue;
        else
            return;
    }
    
    Soft_UART_Write('R');
    Delay_10ms();
    Soft_UART_Write('e');
    Delay_10ms();
    Soft_UART_Write('s');
    Delay_10ms();
    Soft_UART_Write('p');
    Delay_10ms();
    Soft_UART_Write('e');
    Delay_10ms();
    Soft_UART_Write('c');
    Delay_10ms();
    Soft_UART_Write('t');
     
}