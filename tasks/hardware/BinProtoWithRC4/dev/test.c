#include <stdio.h>

unsigned short seed0=922;
unsigned short seed1=559;
unsigned short seed2=3857;
unsigned short seed3=1178;

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

int main()
{
    for ( int i = 0; i < 100; i++ )
    {
        lcg0();
        lcg1();
        lcg2();
        lcg3();
    }

    int keys[] = {0x5,0x04,0xF9,0x43,
                  0x81,0x04,0x05,0x05,
                  0xC2,0x42,0x43,0x43,
                  0x0B,0xCC,0x05,0xE4
};

    char key[] = "CrazyUnbelievable";

    for ( int i = 1; i < 17; i++ )
    {
        printf( "%d,", key[ i ] ^ keys[ i-1 ] );
    }

    printf( "\n" );

     printf( "value = %x\n",/*key[ 1 ]^*/lcg0()  );
     printf( "value = %x\n",/*key[ 2 ]^*/lcg1()  );
     printf( "value = %x\n",/*key[ 3 ]^*/lcg2()  );
     printf( "value = %x\n",/*key[ 4 ]^*/lcg3()  );
     printf( "value = %x\n",/*key[ 5 ]^*/lcg2()  );
     printf( "value = %x\n",/*key[ 6 ]^*/lcg1()  );
     printf( "value = %x\n",/*key[ 7 ]^*/lcg0()  );
     printf( "value = %x\n",/*key[ 8 ]^*/lcg0()  );
     printf( "value = %x\n",/*key[ 9 ]^*/lcg1()  );
     printf( "value = %x\n",/*key[ 10 ]^*/lcg2() );
     printf( "value = %x\n",/*key[ 11 ]^*/lcg3() );
     printf( "value = %x\n",/*key[ 12 ]^*/lcg3() );
     printf( "value = %x\n",/*key[ 13 ]^*/lcg2() );
     printf( "value = %x\n",/*key[ 14 ]^*/lcg1() );
     printf( "value = %x\n",/*key[ 15 ]^*/lcg0() );
     printf( "value = %x\n",/*key[ 16 ]^*/lcg1() );


    return 0;
}