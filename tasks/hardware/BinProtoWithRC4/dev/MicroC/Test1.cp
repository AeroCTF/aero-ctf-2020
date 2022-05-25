#line 1 "D:/CTF/Aero2020/aeroctf-2020-quals/tasks/BinProtoWithRC4/dev/MicroC/Test1.c"
void main(){
 UART1_Init(9600);
 UART1_Write(0x13);
 UART1_Write(0x1);
 UART1_Write(0x5);
 UART1_Write(0x10);
 UART1_Write(0x11);
 UART1_Write(0x12);
 UART1_Write(0x13);
 UART1_Write(0x14);
 UART1_Write(0x37);
}
