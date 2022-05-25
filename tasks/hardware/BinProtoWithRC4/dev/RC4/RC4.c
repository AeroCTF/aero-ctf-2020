#pragma orgall 0xe
static int x = 0;
static int y = 0;
char check_flag = 0;
unsigned int i;
unsigned int j;
int n;
int rnd;
int ii;

char sendFlag = 0;
unsigned char addrItm[10];
#define N 64
#define FLAG_LEN 20
#define KEY_LEN 17

unsigned char SS[N];
char flag[] = {118, 69, 102, 98, 111, 25, 93, 71, 58, 98, 122, 102, 3, 104, 84, 111, 35, 126, 1, 93};
char key[] = "CrazyUnbelievable";
unsigned char tmp;

#define READ_BLOCK  0x0
#define WRITE_BLOCK 0x1
#define SET_RC4_KEY 0x2
#define EXECUTE     0x3

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

void S_swap( unsigned char a, unsigned char b )
{
    tmp = SS[a];
    SS[a] = SS[b];
    SS[b] = tmp;
}

int KSA()
{
    j = 0;

    for(i = 0; i < N; i++)
        SS[i] = i;

    for(i = 0; i < N; i++) {
        j = (j + SS[i] + key[i % KEY_LEN]) % N;
        S_swap(i, j);
    }

    return 0;
}

int PRGA()
{
    i = 0;
    j = 0;

    for ( n = 0; n < FLAG_LEN; n++ )
    {
        i = ( i + 1 ) % N;
        j = ( j + SS[ i ] ) % N;

        S_swap( i, j );
        rnd = SS[ ( SS[ i ] + SS[ j ] ) % N ];

        flag[ n ] = rnd ^ flag[ n ];
    }

    return 0;
}

int RC_4( )
{
    KSA( );

    PRGA( );

    return 0;
}

int dat;
int addr;


void main()
{
    i = 0xe;
    UART1_Init(9600);
    
    if( 0 == sendFlag ){
        j = 0;
        while( j < 4 ){
            dat = FLASH_Read( 0 );
            addrItm[2 + j*2]     = dat&0xff;
            addrItm[2 + j*2 + 1] = dat >> 8;
            j = j + 1;
        }
        UART1_Write(0x13);
        Delay_10ms();
        UART1_Write(0x0A);
        Delay_10ms();
        UART1_Write(0x01);
        Delay_10ms();
        UART1_Write(0x00);
        Delay_10ms();
        UART1_Write(0x0d);
        Delay_10ms();
        ii = 0;
        while ( ii < 8 )
        {
            UART1_Write(addrItm[ ii+2 ]);
            Delay_10ms();
            ii = ii + 1;
        }

        UART1_Write(0x37);
        Delay_ms(100);
        
        while ( i < 0x4e7 ) {
            //UART1_Write(i&0xff);
            j = 0;
            while( j < 4 ){
                dat = FLASH_Read( i+j );
                addrItm[2 + j*2]     = dat&0xff;
                addrItm[2 + j*2 + 1] = dat >> 8;
                j = j + 1;
            }
            addrItm[0] = i >> 8;
            addrItm[1] = i&0xff;

//            UART1_Write( addrItm[0] );
//            UART1_Write( addrItm[1] );
            //UartSendPacket(WRITE_BLOCK, addrItm, 10);
            UART1_Write(0x13);
            Delay_10ms();
            UART1_Write(0x0A);
            Delay_10ms();
            UART1_Write(0x01);
            Delay_10ms();
            ii = 0;
            while ( ii < 10 )
            {
                UART1_Write(addrItm[ ii ]);
                Delay_10ms();
                ii = ii + 1;
            }
            
            UART1_Write(0x37);
            Delay_ms(100);
            
            i = i + 4;
        }
        //Delay_ms(5000);
        UART1_Write(0x13);
        Delay_10ms();
        UART1_Write(0x01);
        Delay_10ms();
        UART1_Write(0x03);
        Delay_10ms();
        UART1_Write(0x01);
        Delay_10ms();
        UART1_Write(0x37);
        Delay_10ms();
    }
    check_flag = 0;
    
    if ( key[0] == 'C' )
    {
           check_flag += 1;
           for ( ii = 0; ii < 100; ii = ii + 1 )
           {
             lcg0();
             lcg1();
             lcg2();
             lcg3();
           }
             if ( (key[ 1 ] ^ lcg0()) == 119 ) check_flag+=1;
             if ( (key[ 2 ] ^ lcg1()) == 101 ) check_flag+=1;
             if ( (key[ 3 ] ^ lcg2()) == 131 ) check_flag+=1;
             if ( (key[ 4 ] ^ lcg3()) == 58 ) check_flag+=1;
             if ( (key[ 5 ] ^ lcg2()) == 212 ) check_flag+=1;
             if ( (key[ 6 ] ^ lcg1()) == 106 ) check_flag+=1;
             if ( (key[ 7 ] ^ lcg0()) == 103 ) check_flag+=1;
             if ( (key[ 8 ] ^ lcg0()) == 96 ) check_flag+=1;
             if ( (key[ 9 ] ^ lcg1()) == 174 ) check_flag+=1;
             if ( (key[ 10 ] ^ lcg2()) == 43 ) check_flag+=1;
             if ( (key[ 11 ] ^ lcg3()) == 38 ) check_flag+=1;
             if ( (key[ 12 ] ^ lcg3()) == 53 ) check_flag+=1;
             if ( (key[ 13 ] ^ lcg2()) == 106 ) check_flag+=1;
             if ( (key[ 14 ] ^ lcg1()) == 174 ) check_flag+=1;
             if ( (key[ 15 ] ^ lcg0()) == 105 ) check_flag+=1;
             if ( (key[ 16 ] ^ lcg1()) == 129 ) check_flag+=1;
    }

    if ( check_flag == 17 )
    {
       RC_4( );
    }
}
