#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void *ptr;

void setup( void );
int read_int( void );
int read_buf( char* buf, int max_size );
void * wait_bomb(void *x);

void * wait_bomb(void *x)
{	
	sleep( 3 );

	for ( int i = 0; i < 3; i++ )
	{
		printf( "." );
		sleep( 1 );
	}

	puts( "************ BOOOOOOOOOOOM!!!!!!!!!!! ************" );

	// int a = (int)x;
	// int *p_a = &a;

	// printf("Diff:0x%lx\nmalloc: %p, stack: %p\n", (unsigned long long)ptr - (unsigned long long)p_a, ptr, p_a);
	
	return 0;
}

int main()
{
	setup();

	puts( "---- Save plane ----" );
	puts( "{?} How many resources do you need to save the plane?" );
	printf( "{?} Resources: " );

	int resources_size = read_int();

	if ( resources_size > 0x200000 )
	{
		puts( "{-} Sorry, is to much" );
		exit( -1 );
	}
	
	ptr = malloc( resources_size );

	puts( "{+} You can use this resources as you will!" );
	
	pthread_t one;
	pthread_create(&one, NULL, &wait_bomb, 0);
	void *val;

	printf( "{?} Enter data offset: " );
	int offset = read_int();
	// -4384
	printf( "offset = %d\n", offset );

	printf( "{?} Input data: " );
	read_buf( ptr + offset, resources_size );

	pthread_join(one,&val);

	exit( 0 );
}

void setup( void )
{
	alarm( 15 );

	setvbuf( stdout, 0, 2, 0 );
	setvbuf( stderr, 0, 2, 0 );
	setvbuf( stdin,  0, 2, 0 );
};

int read_int( void )
{
	char buf[ 8 ];
	int nbytes = read( 0, buf, 8 );
	buf[ nbytes - 1 ] = '\0';

	int result = 0xdeadbeef;

	result = atoi( buf );

	return result;
};

int read_buf( char* buf, int max_size )
{
	int nbytes = 0;

	nbytes = read( 0, buf, max_size );

	if ( nbytes > 0 )
	{
		if ( buf[ nbytes - 1 ] == '\n' )
		{
			buf[ nbytes - 1 ] = 0;
		}
	}
	else
	{
		return 0;
	}

	return nbytes;
}
