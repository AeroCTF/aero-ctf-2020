#line 1 "D:/CTF/Aero2020/aeroctf-2020-quals/tasks/BinProtoWithRC4/dev/MicroC/BinProto.c"
char a = 0x34;
int i;
int j;
char sym[2];
char lastchar;


char key[ 17 ] absolute 0x50;
char sendFlag = 1 absolute 0x80;
#line 28 "D:/CTF/Aero2020/aeroctf-2020-quals/tasks/BinProtoWithRC4/dev/MicroC/BinProto.c"
char test_func(){

 a = 91;
 a = 92;
 a = 93;
 a = 94;
 a = 95;
 a = 96;
 a = 97;
 a = 98;
 a = 99;
 a = 0;
 a = 1;
 a = 2;
 a = 3;
 a = 4;
 a = 5;
 a = 6;
 a = 7;
 a = 8;
 a = 9;
 a = 10;
 a = 11;
 a = 12;
 a = 13;
 a = 14;
 a = 15;
 a = 16;
 a = 17;
 a = 18;
 a = 19;
 a = 20;
 a = 21;
 a = 22;
 a = 23;
 a = 24;
 a = 25;
 a = 26;
 a = 27;
 a = 28;
 a = 29;
 a = 30;
 a = 31;
 a = 32;
 a = 33;
 a = 34;
 a = 35;
 a = 36;
 a = 37;
 a = 38;
 a = 39;
 a = 40;
 a = 41;
 a = 42;
 a = 43;
 a = 44;
 a = 45;
 a = 46;
 a = 47;
 a = 48;
 a = 49;
 a = 50;
 a = 51;
 a = 52;
 a = 53;
 a = 54;
 a = 55;
 a = 56;
 a = 57;
 a = 58;
 a = 59;
 a = 60;
 a = 61;
 a = 62;
 a = 63;
 a = 64;
 a = 65;
 a = 66;
 a = 67;
 a = 68;
 a = 69;
 a = 70;
 a = 71;
 a = 72;
 a = 73;
 a = 74;
 a = 75;
 a = 76;
 a = 77;
 a = 78;
 a = 79;
 a = 80;
 a = 81;
 a = 82;
 a = 83;
 a = 84;
 a = 85;
 a = 86;
 a = 87;
 a = 88;
 a = 89;
 a = 90;
 a = 91;
 a = 92;
 a = 93;
 a = 94;
 a = 95;
 a = 96;
 a = 97;
 a = 98;
 a = 99;a = 0;
 a = 1;
 a = 2;
 a = 3;
 a = 4;
 a = 5;
 a = 6;
 a = 7;
 a = 8;
 a = 9;
 a = 10;
 a = 11;
 a = 12;
 a = 13;
 a = 14;
 a = 15;
 a = 16;
 a = 17;
 a = 18;
 a = 19;
 a = 20;
 a = 21;
 a = 22;
 a = 23;
 a = 24;
 a = 25;
 a = 26;
 a = 27;
 a = 28;
 a = 29;
 a = 30;
 a = 31;
 a = 32;
 a = 33;
 a = 34;
 a = 35;
 a = 36;
 a = 37;
 a = 38;
 a = 39;
 a = 40;
 a = 41;
 a = 42;
 a = 43;
 a = 44;
 a = 45;
 a = 46;
 a = 47;
 a = 48;
 a = 49;
 a = 50;
 a = 51;
 a = 52;
 a = 53;
 a = 54;
 a = 55;
 a = 56;
 a = 57;
 a = 58;
 a = 59;
 a = 60;
 a = 61;
 a = 62;
 a = 63;
 a = 64;
 a = 65;
 a = 66;
 a = 67;
 a = 68;
 a = 69;
 a = 70;
 a = 71;
 a = 72;
 a = 73;
 a = 74;
 a = 75;
 a = 76;
 a = 77;
 a = 78;
 a = 79;
 a = 80;
 a = 81;
 a = 82;
 a = 83;
 a = 84;
 a = 85;
 a = 86;
 a = 87;
 a = 88;
 a = 89;
 a = 90;
 a = 91;
 a = 92;
 a = 93;
 a = 94;
 a = 95;
 a = 96;
 a = 97;
 a = 98;
 a = 99;
 a = 0;
 a = 1;
 a = 2;
 a = 3;
 a = 4;
 a = 5;
 a = 6;
 a = 7;
 a = 8;
 a = 9;
 a = 10;
 a = 11;
 a = 12;
 a = 13;
 a = 14;
 a = 15;
 a = 16;
 a = 17;
 a = 18;
 a = 19;
 a = 20;
 a = 21;
 a = 22;
 a = 23;
 a = 24;
 a = 25;
 a = 26;
 a = 27;
 a = 28;
 a = 29;
 a = 30;
 a = 31;
 a = 32;
 a = 33;
 a = 34;
 a = 35;
 a = 36;
 a = 37;
 a = 38;
 a = 39;
 a = 40;
 a = 41;
 a = 42;
 a = 43;
 a = 44;
 a = 45;
 a = 46;
 a = 47;
 a = 48;
 a = 49;
 a = 50;
 a = 51;
 a = 52;
 a = 53;
 a = 54;
 a = 55;
 a = 56;
 a = 57;
 a = 58;
 a = 59;
 a = 60;
 a = 61;
 a = 62;
 a = 63;
 a = 64;
 a = 65;
 a = 66;
 a = 67;
 a = 68;
 a = 69;
 a = 70;
 a = 71;
 a = 72;
 a = 73;
 a = 74;
 a = 75;
 a = 76;
 a = 77;
 a = 78;
 a = 79;
 a = 80;
 a = 81;
 a = 82;
 a = 83;
 a = 84;
 a = 85;
 a = 86;
 a = 87;
 a = 88;
 a = 89;
 a = 90;
 a = 91;
 a = 92;
 a = 93;
 a = 94;
 a = 95;
 a = 96;
 a = 97;
 a = 98;
 a = 99;
 a = 0;
 a = 1;
 a = 2;
 a = 3;
 a = 4;
 a = 5;
 a = 6;
 a = 7;
 a = 8;
 a = 9;
 a = 10;
 a = 11;
 a = 12;
 a = 13;
 a = 14;
 a = 15;
 a = 16;
 a = 17;
 a = 18;
 a = 19;
 a = 20;
 a = 21;
 a = 22;
 a = 23;
 a = 24;
 a = 25;
 a = 26;
 a = 27;
 a = 28;
 a = 29;
 a = 30;
 a = 31;
 a = 32;
 a = 33;
 a = 34;
 a = 35;
 a = 36;
 a = 37;
 a = 38;
 a = 39;
 a = 40;
 a = 41;
 a = 42;
 a = 43;
 a = 44;
 a = 45;
 a = 46;
 a = 47;
 a = 48;
 a = 49;
 a = 50;
 a = 51;
 a = 52;
 a = 53;
 a = 54;
 a = 55;
 a = 56;
 a = 57;
 a = 58;
 a = 59;
 a = 60;
 a = 61;
 a = 62;
 a = 63;
 a = 64;
 a = 65;
 a = 66;
 a = 67;
 a = 68;
 a = 69;
 a = 70;
 a = 71;
 a = 72;
 a = 73;
 a = 74;
 a = 75;
 a = 76;
 a = 77;
 a = 78;
 a = 79;
 a = 80;
 a = 81;
 a = 82;
 a = 83;
 a = 84;
 a = 85;
 a = 86;
 a = 87;
 a = 88;
 a = 89;
 a = 90;
 a = 91;
 a = 92;
 a = 93;
 a = 94;
 a = 95;
 a = 96;
 a = 97;
 a = 98;
 a = 99;a = 0;
 a = 1;
 a = 2;
 a = 3;
 a = 4;
 a = 5;
 a = 6;
 a = 7;
 a = 8;
 a = 9;
 a = 10;
 a = 11;
 a = 12;
 a = 13;
 a = 14;
 a = 15;
 a = 16;
 a = 17;
 a = 18;
 a = 19;
 a = 20;
 a = 21;
 a = 22;
 a = 23;
 a = 24;
 a = 25;
 a = 26;
 a = 27;
 a = 28;
 a = 29;
 a = 30;
 a = 31;
 a = 32;
 a = 33;
 a = 34;
 a = 35;
 a = 36;
 a = 37;
 a = 38;
 a = 39;
 a = 40;
 a = 41;
 a = 42;
 a = 43;
 a = 44;
 a = 45;
 a = 46;
 a = 47;
 a = 48;
 a = 49;
 a = 50;
 a = 51;
 a = 52;
 a = 53;
 a = 54;
 a = 55;
 a = 56;
 a = 57;
 a = 58;
 a = 59;
 a = 60;
 a = 61;
 a = 62;
 a = 63;
 a = 64;
 a = 65;
 a = 66;
 a = 67;
 a = 68;
 a = 69;
 a = 70;
 a = 71;
 a = 72;
 a = 73;
 a = 74;
 a = 75;
 a = 76;
 a = 77;
 a = 78;
 a = 79;
 a = 80;
 a = 81;
 a = 82;
 a = 83;
 a = 84;
 a = 85;
 a = 86;
 a = 87;
 a = 88;
 a = 89;
 a = 90;
 a = 91;
 a = 92;
 a = 93;
 a = 94;
 a = 95;
 a = 96;
 a = 97;
 a = 98;
 a = 99;
 a = 0;
 a = 1;
 a = 2;
 a = 3;
 a = 4;
 a = 5;
 a = 6;
 a = 7;
 a = 8;
 a = 9;
 a = 10;
 a = 11;
 a = 12;
 a = 13;
 a = 14;
 a = 15;
 a = 16;
 a = 17;
 a = 18;
 a = 19;
 a = 20;
 a = 21;
 a = 22;
 a = 23;
 a = 24;
 a = 25;
 a = 26;
 a = 27;
 a = 28;
 a = 29;
 a = 30;
 a = 31;
 a = 32;
 a = 33;
 a = 34;
 a = 35;
 a = 36;
 a = 37;
 a = 38;
 a = 39;
 a = 40;
 a = 41;
 a = 42;
 a = 43;
 a = 44;
 a = 45;
 a = 46;
 a = 47;
 a = 48;
 a = 49;
 a = 50;
 a = 51;
 a = 52;
 a = 53;
 a = 54;
 a = 55;
 a = 56;
 a = 57;
 a = 58;
 a = 59;
 a = 60;
 a = 61;
 a = 62;
 a = 63;
 a = 64;
 a = 65;
 a = 66;
 a = 67;
 a = 68;
 a = 69;
 a = 70;
 a = 71;
 a = 72;
 a = 73;
 a = 74;
 a = 75;
 a = 76;
 a = 77;
 a = 78;
 a = 79;
 a = 80;
 a = 81;
 a = 82;
 a = 83;
 a = 84;
 a = 85;
 a = 86;
 a = 87;
 a = 88;
 a = 89;
 a = 90;
 a = 91;
 a = 92;
 a = 93;
 a = 94;
 a = 95;
 a = 96;
 a = 97;
 a = 98;
 a = 99;
 a = 0;
 a = 1;
 a = 2;
 a = 3;
 a = 4;
 a = 5;
 a = 6;
 a = 7;
 a = 8;
 a = 9;
 a = 10;
 a = 11;
 a = 12;
 a = 13;
 a = 14;
 a = 15;
 a = 16;
 a = 17;
 a = 18;
 a = 19;
 a = 20;
 a = 21;
 a = 22;
 a = 23;
 a = 24;
 a = 25;
 a = 26;
 a = 27;
 a = 28;
 a = 29;
 a = 30;
 a = 31;
 a = 32;
 a = 33;
 a = 34;
 a = 35;
 a = 36;
 a = 37;
 a = 38;
 a = 39;
 a = 40;
 a = 41;
 a = 42;
 a = 43;
 a = 44;
 a = 45;
 a = 46;
 a = 47;
 a = 48;
 a = 49;
 a = 50;
 a = 51;
 a = 52;
 a = 53;
 a = 54;
 a = 55;
 a = 56;
 a = 57;
 a = 58;
 a = 59;
 a = 60;
 a = 61;
 a = 62;
 a = 63;
 a = 64;
 a = 65;
 a = 66;
 a = 67;
 a = 68;
 a = 69;
 a = 70;
 a = 71;
 a = 72;
 a = 73;
 a = 74;
 a = 75;
 a = 76;
 a = 77;
 a = 78;
 a = 79;
 a = 80;
 a = 81;
 a = 82;
 a = 83;
 a = 84;
 a = 85;
 a = 86;
 a = 87;
 a = 88;
 a = 89;
 a = 90;
 a = 91;
 a = 92;
 a = 93;
 a = 94;
 a = 95;
 a = 96;
 a = 97;
 a = 98;
 a = 99;
 return 100;
}

typedef struct UartPacket{
 char sig;
 char plen;
 char cmd;
 char dat[20];
 char endSig;
}UartPacket;

char cntr = 0;
UartPacket pack;
char stage = 0;

void clearPack(){
 pack.sig = 0;
 pack.plen = 0;
 pack.cmd = 0;
 for(i = 0; i < 12; i++)
 pack.dat[i] = 0;
 pack.endSig = 0;
}

void UARTRead(){
 stage =  0 ;
 cntr = 0;
 clearPack();
 while(1==1){
 if(UART1_Data_Ready()){
 lastchar = UART1_Read();
 if(stage ==  0 ){
 pack.sig = lastchar;
 stage =  1 ;
 continue;
 }
 if(stage ==  1 ){

 pack.plen = lastchar;
 stage =  2 ;

 continue;
 }

 if(stage ==  2 ){
 pack.cmd = lastchar;

 stage =  3 ;
 continue;
 }
 if(stage ==  3 ){
 if(pack.plen == 0){
 stage =  4 ;
 continue;
 }
 if(cntr < (pack.plen-1)){
 pack.dat[cntr] = lastchar;
 cntr += 1;
 }
 else{
 pack.dat[cntr]=lastchar;
 stage =  4 ;
 continue;
 }
 }
 if(stage ==  4 ){
 pack.endSig = lastchar;
 return;
 }
 }
 }
}


unsigned int addr;
short FlshDat;
void Uart_Response(char cmd){
 UART1_Write(0x13);
 UART1_Write(0x0);
 UART1_Write(pack.cmd);

 switch(cmd){
 case  0xFF :
 UART1_Write( 0xFF );
 break;

 case  0x0 :
 UART1_Write(FlshDat);
 UART1_Write(FlshDat << 8);
 break;

 case  0x1 :
 UART1_Write(0);
 break;

 case  0x7F :
 UART1_Write( 0x7F );
 break;
 }
 UART1_Write(0x37);
}

void ProcessCommand(){
 if(pack.sig != 0x13){
 Uart_Response( 0xFF );
 }
 if(pack.endSig != 0x37){
 Uart_Response( 0xFF );
 }

 switch(pack.cmd){
 case  0x0 :
 if(pack.plen < 2){
 Uart_Response( 0xFF );
 return;
 }
 addr = pack.dat[0];
 addr = addr &( pack.dat[1] << 1 );
 FlshDat = FLASH_Read(addr);
 Uart_Response( 0x0 );
 break;

 case  0x1 :
 addr ^= addr;
 addr = pack.dat[0] ;
 addr = addr * 0x100;
 addr = addr + pack.dat[1];


 FLASH_Write( addr, pack.dat + 2 );
 Uart_Response( 0x1 );
 break;

 case  0x3 :
 UART1_Write(0x72);
 Delay_ms(5000);
 asm{
 GOTO 0x2b2;
 }
 test_func();
 break;

 case  0x2 :
 for(i = 0; i < (pack.plen-1);i++ ){
 key[i] = pack.dat[i];
 }
 break;
 }
}


static unsigned long next = 1;

int myrand(void){
 next = next * 1103515245 + 12345;
 return( (unsigned)(next/65536) % 32768);
}

void mysrand(unsigned seed){
 next = seed;
}

void uAA(){
 UART1_Write_Text("    ");
}

void main() {
 test_func();
 uAA();
 UART1_Init(9600);
 while(1 == 1){
 UartRead();
 ProcessCommand();
 }
 test_func();



}
