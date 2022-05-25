#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char* argv[] )
{
	double var;
	long long int arg = atoll( argv[ 1 ] );

	//printf( "arg = %d\n", arg );

	memcpy( (void*)&var, (void*)&arg, 8 );
	
	printf( "%256.2048lf\n", var );

	return 0; 
}