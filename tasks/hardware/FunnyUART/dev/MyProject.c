int i;
int j;
int seed;
char rfd;
char stage = 0;
char buf[20];
char flag[] = {0x3b, 0xbd, 0xbc, 0x95, 0x6, 0xe1, 0xdb, 0x36, 0xc9, 0x3a,
               0xa9, 0x3b, 0x61, 0x44, 0x99, 0x50, 0xc4, 0xde, 0x85, 0x84};

char key[]  = {0xac, 0x10, 0x5a, 0xc3, 0xbf, 0x76, 0x31, 0xe9, 0x34, 0x7f, 
               0xf, 0x4f, 0x4a, 0xfa};

void PORTINIT(){
     STATUS.RP0 = 1;
     STATUS.RP1 = 0;
     TRISB = 0xFF;
     TRISC = 0x0;
     TRISD = 0x0;

     STATUS.RP0 = 0;
     STATUS.RP1 = 0;
     PORTC = 0;
     PORTD = 0;
}

static unsigned long next = 1;

int myrand(void){
    next = next * 1103515245 + 12345;
    return( (unsigned)(next/65536) % 32768);
}

void mysrand(unsigned seed){
     next = seed;
}

void main() {
   UART1_Init(9600);
   UART1_Write_Text("Enter valid password");
   mysrand(0x1337);
   while(1 && (14 != stage)){
       if(UART1_Data_Ready()){
           rfd = UART1_Read();
           UART1_Write(rfd);
           if( (stage == 0) ){
               if( key[stage] == ( rfd^ (myrand()%0xFF) ) )
                   stage = 1;
               else
                   stage = 0;
               continue;
           }
           if(stage == 1){
               if( key[stage] == ( rfd^ (myrand()%0xFF) ) )
                   stage = 2;
               else
                   stage = 0;
               continue;
           }
           if((stage == 2) ){
               if( key[stage] == ( rfd^ (myrand()%0xFF) ) )
                   stage = 3;
               else
                   stage = 0;
               continue;
           }
           if((stage == 3) ){
               if( key[stage] == ( rfd^ (myrand()%0xFF) ) )
                   stage = 4;
               else
                   stage = 0;
               continue;
           }
           if((stage == 4)){
               if( key[stage] == ( rfd^ (myrand()%0xFF) ) )
                   stage = 5;
               else
                   stage = 0;
               continue;
           }
           if((stage == 5) ){
               if( key[stage] == ( rfd^ (myrand()%0xFF) ) )
                   stage = 6;
               else
                   stage = 0;
               continue;
           }
           if((stage == 6)){
               if( key[stage] == ( rfd^ (myrand()%0xFF) ) )
                   stage = 7;
               else
                   stage = 0;
               continue;
           }
           if((stage == 7) ){
               if( key[stage] == ( rfd^ (myrand()%0xFF) ) )
                   stage = 8;
               else
                   stage = 0;
               continue;
           }
           if((stage == 8) ){
               if( key[stage] == ( rfd^ (myrand()%0xFF) ) )
                   stage = 9;
               else
                   stage = 0;
               continue;
           }
           if((stage == 9)){
               if( key[stage] == ( rfd^ (myrand()%0xFF) ) )
                   stage = 10;
               else
                   stage = 0;
               continue;
           }
           if((stage == 10)){
               if( key[stage] == ( rfd^ (myrand()%0xFF) ) )
                   stage = 11;
               else
                   stage = 0;
               continue;
           }
           if((stage == 11)){
               if( key[stage] == ( rfd^ (myrand()%0xFF) ) )
                   stage = 12;
               else
                   stage = 0;
               continue;
           }
           if((stage == 12)){
               if( key[stage] == ( rfd^ (myrand()%0xFF) ) )
                   stage = 13;
               else
                   stage = 0;
               continue;
           }

           if((stage == 13)){
               if( key[stage] == ( rfd^ (myrand()%0xFF) ) )
                   stage = 14;
               else
                   stage = 0;
               seed = 0x6724;
               UART1_Write_Text("\nCorrect.\n");
               continue;
           }
       }
       rfd = 0;
   }

   mysrand(seed);
   for(i = 0; i < 20; i++){
       buf[i] = myrand()%0xFF;
   }

   for(i = 0; i < 20; i++){
       UART1_Write(buf[i]^flag[i]);
   }
}