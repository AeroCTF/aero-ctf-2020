#include <stdio.h>
#include <stdlib.h>

unsigned short crc_ccitt_update (unsigned char dt)
{
    unsigned short crc = 0;
	dt ^= crc&255;
	dt ^= dt << 4;
	crc = (((unsigned int)dt << 8) | ((crc>>8)&255));
	crc ^= (unsigned char)(dt >> 4);
	crc ^= ((unsigned int)dt << 3);
	return crc;
}

int main()
{
    char key[] = "1e9bfe04dc00d51c32acac6377d19a58";
    unsigned short flag[] = {0x329,0x37d,0x2033,0x51ff,0x54d3,0xbdae,0xbdfb,0x32c,0x2546,0x2541,0x5485,0x31b3,0x206e,0x31b6,0xbdfa,0x54d6,0x7794,0x4026,0x455d,0x34c8,0x72ee,0x2541,0x203c,0x32b,0x31b4,0x4023,0x34cf,0x450d,0x4505,0x51fc,0x2517,0x6616};
    for(int i = 0; i<32; i++){
        for(int j = 0; j < 255; j++){
            unsigned short crc = crc_ccitt_update(j);
            //printf("%x:%x\n", flag[i], crc^key[i]);
            if(flag[i] == (crc^key[i])){
                printf("%x\n", j);
                break;
            }
        }
    }
    return 0;
}
