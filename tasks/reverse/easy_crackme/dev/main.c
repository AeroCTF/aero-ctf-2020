#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const static unsigned int l[ 4 ] = {
	0xdeadbeef,
	0xc0febabe,
	0xbadc0de,
	0xdeadc0de
};
const static unsigned int k[ 16 ] = {
	0x0,  0x01, 0x10, 0x11, 
	0x02, 0x20, 0x21, 0x22, 
	0x30, 0x31, 0x32, 0x33, 
	0x40, 0x41, 0x42, 0x43
};

const static unsigned int r[ 16 ] = {
	50, 100, 118, 38,
	53, 22,  68,  67,
	1,  80,  87,  4,
	36, 121, 35,  34
};


int main()
{
	// Aero{72730f6d6292ef776ea1ae7d8aaf82804a38bc6252e84ecba5a4985a32f55b18}
	// Aero{72730f6d6292ef776ea1ae7d8aaf82804a38bc6252e84ecba5a4985a32f55b17}
	
	char a[ 128 ];

	int nbytes = read( 0, a, 71 );
	a[ nbytes - 1 ] = '\0';

	if ( strlen( a ) != 70 )
		goto end;

	if ( a[ 49 ] != '4' )
		goto end;

	unsigned int v[ 4 ];

	if ( a[ 48 ] != '8' )
		goto end;

	v[ 0 ]  = a[ 0 ] << 24;
	v[ 0 ] |= a[ 4 ] << 16;
	v[ 0 ] |= a[ 8 ] << 8;
	v[ 0 ] |= a[ 12 ];

	if ( a[ 32 ] != 'f' )
		goto end;

	v[ 1 ]  = a[ 1 ] << 24;
	v[ 1 ] |= a[ 5 ] << 16;
	v[ 1 ] |= a[ 9 ] << 8;
	v[ 1 ] |= a[ 13 ];
	
	if ( a[ 33 ] != '8' )
		goto end;

	v[ 2 ]  = a[ 2 ] << 24;
	v[ 2 ] |= a[ 6 ] << 16;
	v[ 2 ] |= a[ 10 ] << 8;
	v[ 2 ] |= a[ 14 ];

	if ( a[ 47 ] != 'e' )
		goto end;

	v[ 3 ]  = a[ 3 ] << 24;
	v[ 3 ] |= a[ 7 ] << 16;
	v[ 3 ] |= a[ 11 ] << 8;
	v[ 3 ] |= a[ 15 ];

	if ( a[ 46 ] != '2' )
		goto end;
	
	if ( v[ 0 ] != 1098593124 )
		goto end;

	if ( a[ 45 ] != '5' )
		goto end;

	if ( v[ 1 ] != 1698115638 )
		goto end;

	if ( a[ 39 ] != '3' )
		goto end;

	if ( v[ 2 ] != 1915905586 )
		goto end;
	
	if ( a[ 44 ] != '2' )
		goto end;

	if ( v[ 3 ] != 1865889337 )
		goto end;

	if ( a[ 43 ] != '6' )
		goto end;

	v[ 0 ]  = a[ 69 ] << 24;
	v[ 0 ] |= a[ 65 ] << 16;
	v[ 0 ] |= a[ 61 ] << 8;
	v[ 0 ] |= a[ 57 ];

	if ( a[ 37 ] != '4' )
		goto end;

	v[ 1 ]  = a[ 68 ] << 24;
	v[ 1 ] |= a[ 64 ] << 16;
	v[ 1 ] |= a[ 60 ] << 8;
	v[ 1 ] |= a[ 56 ];
	
	if ( a[ 35 ] != '8' )
		goto end;

	v[ 2 ]  = a[ 67 ] << 24;
	v[ 2 ] |= a[ 63 ] << 16;
	v[ 2 ] |= a[ 59 ] << 8;
	v[ 2 ] |= a[ 55 ];

	if ( a[ 38 ] != 'a' )
		goto end;

	v[ 3 ]  = a[ 66 ] << 24;
	v[ 3 ] |= a[ 62 ] << 16;
	v[ 3 ] |= a[ 58 ] << 8;
	v[ 3 ] |= a[ 54 ];

	if ( a[ 42 ] != 'c' )
		goto end;

	if ( ( l[ 0 ] - v[ 0 ] ) != 1635290038 )
		goto end;

	if ( a[ 41 ] != 'b' )
		goto end;

	if ( ( l[ 1 ] - v[ 1 ] ) != 2294897034 )
		goto end;

	if ( a[ 40 ] != '8' )
		goto end;

	if ( ( l[ 2 ] - v[ 2 ] ) != -632845443 )
		goto end;

	if ( a[ 34 ] != '2' )
		goto end;

	if ( ( l[ 3 ] - v[ 3 ] ) != 2088470697 )
		goto end;

	if ( a[ 36 ] != '0' )
		goto end;

	for ( int i = 16; i < 32; i++ )
	{
		if ( ( k[ i % 16 ] ^ a[ i ] ) != r[ i % 16 ] )
			goto end;
	}

	if ( a[ 50 ] != 'e' )
		goto end;
	
	if ( a[ 51 ] != 'c' )
		goto end;

	if ( a[ 52 ] != 'b' )
		goto end;

	if ( a[ 53 ] != 'a' )
		goto end;

	puts( "[+] Correct flag!" );
	exit( 1337 );

end:
	puts( "[-] Incorrect flag!" );
	return 0;
}