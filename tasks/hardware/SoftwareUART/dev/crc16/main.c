#include <stdio.h>
#include <stdlib.h>

unsigned short crc_ccitt_update (unsigned char dt)
{
    unsigned short crc;
    crc = 0;
	dt ^= crc&255;
	dt ^= dt << 4;
	crc = (((unsigned short)dt << 8) | ((crc>>8)&255));
	crc ^= (unsigned char)(dt >> 4);
	crc ^= ((unsigned short)dt << 3);
	return crc;
}

int main()
{
    unsigned short crc = 0;
    char key[] = "1e9bfe04dc00d51c32acac6377d19a58";
    char flag[] = "Aero{331c6883dd6010864b7ead130be77cd5}";
    for(int i = 5; i < 37; i++){
        crc = crc_ccitt_update(flag[i]);
        printf("%x\n", crc ^ key[i-5]);
    }


    return 0;
}
