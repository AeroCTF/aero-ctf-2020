#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CHUNK_SIZE 0x80

char name[ CHUNK_SIZE ];

struct entry
{
	char ticket_id[ 8 ];
	double rating;
};

int read_buf( char* buf, int max_size );
int read_int();

void menu( void );
void setup( void );

int main()
{
	setup();

	printf( "{?} Enter name: " );
	read_buf( name, CHUNK_SIZE );

	int lifes = 3;
	int fexit = 0;

	int cur_rating_idx = 0;
	struct entry rating_list[ 10 ];

	while ( 1 && fexit != 1 )
	{
		if ( lifes <= 0 )
			exit( -2 );

		menu();
		int option = read_int();

		if ( option == 0xdeadbeef )
			exit( -1 );

		switch ( option )
		{
			case 1:
				{
					printf( "{?} Enter your ticket id: " );
					read_buf( rating_list[ cur_rating_idx ].ticket_id, 8 );
					printf( "{?} Enter your rating: " );
					scanf( "%lf", &rating_list[ cur_rating_idx ].rating );

					printf( "{+} You set rating <%lf> to ticket <%s>\n", 
						rating_list[ cur_rating_idx ].rating, 
						rating_list[ cur_rating_idx ].ticket_id );

					cur_rating_idx += 1;
					break;	
				}
			case 2:
				{
					puts( "----- Your rating list -----" );

					for ( int i = 0; i < cur_rating_idx; i++ )
					{
						printf( "----- Rating [%d] -----\n", i );
						printf( "Ticket: %s\n", rating_list[ i ].ticket_id );
						printf( "Score: %lf\n", rating_list[ i ].rating );
					}
				}
			case 3:
				{
					puts( "------ Profile ------" );
					printf( "Name: %s\n", name );
					printf( "You set %d ratins\n", cur_rating_idx );
					break;
				}
			case 4:
				fexit = 1;
				break;
			default:
				lifes -= 1;
				break;
		}
	}


	return 0;
};


void menu( void )
{
	puts( "1. Set rating" );
	puts( "2. View rating list" );
	puts( "3. View porfile info" );
	puts( "4. Exit" );

	printf( "> " );
};

void setup( void )
{
	alarm( 5 );

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
};