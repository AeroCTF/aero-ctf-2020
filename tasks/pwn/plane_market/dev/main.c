#include <stdio.h>
#include <string.h>
#include <time.h> 
#include <stdlib.h>
#include <unistd.h>

#define CHUNK_SIZE 0x80
#define USER_NAME_SIZE 0x20
#define ID_SIZE 9

void setup( void );

struct plane
{
	char* name;
	long long int cost;
	long long int sale_time;
	char* comment;
	long long int name_size;
	long long int del_time;
};

struct plane plane_list[ 16 ];
int last_plane_id = -1;
int lifes = 3;
int option;

// utilites
int read_buf( char* buf, int max_size );
int read_int();
void setup( void );
int market( void );

// UI
void menu( void );
int change_plane_name( void );
int view_plane( void );
void view_list( void );
int delete_plane( void );
void sell_plane( void );

// plane market
int main()
{
	setup();
	market();
	return 0;
};

int market( void )
{
	char username[ CHUNK_SIZE ];
	printf( "{?} Enter name: " );
	read_buf( username, CHUNK_SIZE );

	while ( 1 )
	{
		if ( lifes <= 0 )
			return 0;

		menu();
		option = read_int();

		if ( option == 0xdeadbeef )
			exit( -1 );

		switch ( option )
		{
			case 1:
				sell_plane();
				break;
			case 2:
				delete_plane();
				break;
			case 3:
				view_list();
				break;
			case 4:
				view_plane();
				break;
			case 5:
				change_plane_name();
				break;
			case 6:
			{
				printf( "{?} You logined as %s\n", username );
				break;
			}
			case 7:
				exit( -1 );
				break;
			default:
				lifes -= 1;
				break;
		}
	}
};

int change_plane_name( void )
{
	printf( "{?} Enter plane id: " );
	int plane_id = read_int();

	if ( plane_id >= 16 )
	{
		puts( "{-} Error id!" );
		return 0;
	}

	if ( plane_id == last_plane_id )
	{
		printf( "{?} Enter new plane name: " );
		read_buf( plane_list[ plane_id ].name, plane_list[ plane_id ].name_size );
	}
	else
	{
		if ( plane_list[ plane_id ].del_time == 0 )
		{
			printf( "{?} Enter new plane name: " );
			read_buf( plane_list[ plane_id ].name, plane_list[ plane_id ].name_size );
			last_plane_id = plane_id;
		}
	}
};

int view_plane( void )
{
	printf( "{?} Enter plane id: " );
	int plane_id = read_int();

	if ( plane_id >= 16 )
	{
		puts( "{-} Error id!" );
		return 0;
	}

	if ( plane_list[ plane_id ].del_time != 0 )
	{
		puts( "{-} No such plane!" );
		return 0;
	}

	printf( "---- Plane [%d] ----\n", plane_id );
	printf( "Name: %s\n", plane_list[ plane_id ].name );
	printf( "Cost: %lld\n", plane_list[ plane_id ].cost );
	printf( "Time: %lld\n", plane_list[ plane_id ].sale_time );

	if ( plane_list[ plane_id ].comment != NULL )
	{
		printf( "Comment: %s\n", plane_list[ plane_id ].comment );
	}
	else
	{
		puts( "Comment: <Empty>" );  
	}

	return 1;
};

void view_list( void )
{
	puts( "---- Plane list ----" );

	for ( int i = 0; i < 16; i++ )
	{
		if ( plane_list[ i ].del_time == 0 )
		{
			printf( "---- Plane [%d] ----\n", i );
			printf( "Name: %s\n", plane_list[ i ].name );
			printf( "Cost: %lld\n", plane_list[ i ].cost );
			printf( "Time: %lld\n", plane_list[ i ].sale_time );

			if ( plane_list[ i ].comment != NULL )
			{
				printf( "Comment: %s\n", plane_list[ i ].comment );
			}
			else
			{
				puts( "Comment: <Empty>" );  
			}
		}
	}
};

int delete_plane( void )
{
	printf( "{?} Enter plane id: " );
	int plane_id = read_int();

	if ( plane_id >= 16 )
	{
		puts( "{-} Error id!" );
		return 0;
	}

	if ( plane_list[ plane_id ].del_time != 0 )
	{
		puts( "{-} No such plane!" );
		return 0;
	}

	plane_list[ plane_id ].del_time = time( NULL );
	free( plane_list[ plane_id ].name );

	if ( plane_list[ plane_id ].comment != NULL )
	{
		free( plane_list[ plane_id ].comment );
		plane_list[ plane_id ].comment = NULL;
	}

	return 1;
};

void sell_plane( void )
{
	char added = 0;

	for ( int i = 0; i < 16; i++ )
	{
		if ( plane_list[ i ].del_time != 0 )
		{
			added = 1;

			struct plane *new_plane = &plane_list[ i ];
			
			printf( "{?} Enter name size: " );
			int name_size = read_int();
			new_plane->name_size = name_size;

			printf( "{?} Enter plane name: " );
			new_plane->name = (char*) malloc( name_size );
			read_buf( new_plane->name, name_size );

			printf( "{?} Enter plane cost: " );
			new_plane->cost = (long long int)read_int();
			new_plane->sale_time = (long long int) time( NULL );

			char option[ 2 ];
			printf( "{?} Do you wanna leave a comment? [Y\\N]: " );
			read_buf( option, 2 );

			if ( option[ 0 ] == 'Y' )
			{
				printf( "{?} Enter comment size: " );
				int comment_size = read_int();

				new_plane->comment = (char*) malloc( comment_size );
				printf( "{?} Comment: " );
				read_buf( new_plane->comment, comment_size );
			}
			else
			{
				new_plane->comment = NULL;
			}

			new_plane->del_time = 0;
			break;	
		}
	}

	if ( !added )
	{
		puts( "{-} No space available!" );
	}
};

void setup( void )
{
	alarm( 5 );

	for ( int i = 0; i < 16; i++ )
		plane_list[ i ].del_time = 0xffffffff;
	
	setvbuf( stdin,  0, 2, 0 );
	setvbuf( stdout, 0, 2, 0 );
	setvbuf( stderr, 0, 2, 0 );
};

void menu()
{
	puts( "-------- Plane market --------" );
	puts( "1. Sell plane" );
	puts( "2. Delete plane" );
	puts( "3. View sales list" );
	puts( "4. View plane" );
	puts( "5. Change plane name" );
	puts( "6. View profile" );
	puts( "7. Exit" );

	printf( "> " );
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