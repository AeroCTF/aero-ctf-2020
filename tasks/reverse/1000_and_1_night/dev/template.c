#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void setup( void );
int check( char* );

int main()
{
	setup();

	printf( "[?] Enter valid token: " );

	char* buf = (char*) malloc( 64 );
	int nbytes = read( 0, buf, 64 );
	
	buf[ nbytes - 1 ] = '\0';


	if ( strlen( buf ) != 32 ) 
	{
		puts( "[-] Incorrect!" );
		return 1337; 
	}

	if ( !check( buf ) )
	{
		puts( "[-] Incorrect!" );
	}
	else
	{
		puts( "[+] This is a valid token!" );
	}
};

void setup( void )
{
	setvbuf( stdin,  0, 2, 0 );
	setvbuf( stdout, 0, 2, 0 );
	setvbuf( stderr, 0, 2, 0 );
};

int check( char* buf )
{
	%s
	return 1;
};