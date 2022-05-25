#define READ_BLOCK  0x0
#define WRITE_BLOCK 0x1
#define SET_RC4_KEY 0x2
#define EXECUTE     0x3
void wait(){
     while(!UART1_Tx_Idle())
         continue;
}
unsigned char code1[16] = {0x00, 0x0d, 0x21, 0x30, 0x83, 0x12, 0x03, 0x13, 0xbf, 0x00 ,0x00, 0x11, 0x58, 0x20, 0x08, 0x00};

int i = 0;
int j = 0;

void UartSend(char *dat, char len){
    for(i = 0; i < len; i++){
        UART1_Write(dat[i]);
        Delay_ms(10);
    }
}

void UartSendPacket(char cmd, char *dat, char len){
     UART1_Write(0x13);

     switch(cmd){
         case WRITE_BLOCK:
             UART1_Write(len);
             UART1_Write(WRITE_BLOCK);
             UartSend(dat, len);
             break;

         case EXECUTE:
             UART1_Write(0x1);
             UART1_Write(EXECUTE);
             UART1_Write(0x2);
             break;
     }

     UART1_Write(0x37);
}
int dat;
int addr;
char addrItm[2];
void main(){
     UART1_Init(9600);
     
     UartSendPacket(WRITE_BLOCK, code1, 10);
     Delay_100ms();
     UartSendPacket(WRITE_BLOCK, code1 + 10, 6);
     Delay_ms(1000);
     UartSendPacket(EXECUTE, 0, 0);
}