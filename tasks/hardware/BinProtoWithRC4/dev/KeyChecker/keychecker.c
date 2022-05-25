char flag[] = {118, 69, 102, 98, 111, 25, 93, 71, 58, 98, 122, 102, 3, 104, 84, 111, 35, 126, 1, 93};
char key[] = "CrazyUnbelievable";

char check_flag = 0;
int ii = 0;
unsigned int seed0=922;
unsigned int seed1=559;
unsigned int seed2=3857;
unsigned int seed3=1178;

unsigned char lcg0(void) {
        seed0=((974  * seed0) + 4095) % 53528;
        return seed0 & 0xff;
}

unsigned char lcg1(void) {
        seed1=((2204  * seed1) + 2196) % 45634;
        return seed1 & 0xff;
}

unsigned char lcg2(void) {
        seed2=((3642  * seed2) + 1047) % 27663;
        return seed2 & 0xff;
}

unsigned char lcg3(void) {
        seed3=((4266  * seed3) + 2245) % 55961;
        return seed3 & 0xff;
}

void main() {
   UART1_Init(9600);
   check_flag += 1;
   for ( ii = 0; ii < 100; ii = ii + 1 )
   {
     lcg0();
     lcg1();
     lcg2();
     lcg3();
   }
  UART1_Write(lcg0());
  UART1_Write(lcg1());
  UART1_Write(lcg2());
  UART1_Write(lcg3());
  UART1_Write(lcg2());
  UART1_Write(lcg1());
  UART1_Write(lcg0());
  UART1_Write(lcg0());
  UART1_Write(lcg1());
  UART1_Write(lcg2());
  UART1_Write(lcg3());
  UART1_Write(lcg3());
  UART1_Write(lcg2());
  UART1_Write(lcg1());
  UART1_Write(lcg0());
  UART1_Write(lcg1());

}