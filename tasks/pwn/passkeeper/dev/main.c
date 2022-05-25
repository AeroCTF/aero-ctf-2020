#include <stdio.h>
#include <string.h>
#include <time.h> 
#include <stdlib.h>
#include <unistd.h>

#define CHUNK_SIZE 0x40
#define ID_SIZE 9


void setup( void );
void menu( void );

int read_buf( char* buf, int max_size );
int read_int( void );

typedef void (*func_ptr)(void*);

struct user_info {
	char name[ CHUNK_SIZE ];
	func_ptr print_name;
};

void print_name( struct user_info *user );
struct user_info user;

int main()
{
	char secret_password[ 16 ];
	int lifes = 3;
	int idx = 0;
	char* passwords[ 16 ];

	setup();

	printf( "{?} Enter name: " );
	read_buf( user.name, CHUNK_SIZE );

	printf( "{?} Enter secret: " );
	read_buf( secret_password, 16 );
	
	while ( 1 )
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
				if ( idx >= 16 )
				{
					puts( "{-} No available space!" );
					break;
				}

				char* password = (char*) malloc( 0x30 );
				
				printf( "{?} Enter password: " );
				read_buf( password, 0x30 );
				
				passwords[ idx ] = password;
				idx += 1;

				break;
			}
			case 2:
			{
				printf( "{?} Enter password id: " );
				int id = read_int();

				if ( id > idx || id < 0 )
				{
					puts( "{-} Error password id!" );
				}
				else
				{
					if ( passwords[ id ] != NULL )
					{
						printf( "---- Password [%d] ----\n", id );
						printf( "Value: %s\n", passwords[ id ] );
						printf( "Owner: %s\n", user.name );
					};
				}

				break;
			}
			case 3:
			{
				for ( int i = 0; i < idx; i++ )
				{
					if ( passwords[ i ] != NULL )
					{
						printf( "---- Password [%d] ----\n", i );
						printf( "Value: %s\n", passwords[ i ] );
						printf( "Owner: %s\n", user.name );
					}
				}
				break;
			}
			case 4:
			{
				printf( "{?} Enter password id: " );
				int del_idx = read_int();

				if ( del_idx > idx )
				{
					puts( "{-} Error password id!" );
				}
				else
				{
					if ( passwords[ del_idx ] != NULL )
					{
						free( passwords[ del_idx ] );
						passwords[ del_idx ] = NULL;
						idx -= 1;
					}
					else
						puts( "{-} Delete error!" );
				}

				break;
			}
			case 5:
			{
				for ( int i = 0; i < idx; i++ )
				{
					if ( passwords[ i ] )
					{
						free( passwords[ i ] );
						passwords[ i ] = NULL;
						idx -= 1;
					}
				}
				break;
			}
			case 6:
			{
				user.print_name( &user );
				break;
			}
			case 7:
			{
				printf( "Enter new secret: " );
				read_buf( secret_password, 16 );
				break;
			}
			case 8:
				exit( -1 );
				break;
			default:
				lifes -= 1;
				break;
		}
	}

};

void print_name( struct user_info *user )
{
	printf( "You logined as %s\n", user->name );
};

void setup( void )
{
	alarm( 5 );
	user.print_name = print_name;
	setvbuf( stdin,  0, 2, 0 );
	setvbuf( stdout, 0, 2, 0 );
	setvbuf( stderr, 0, 2, 0 );
};

void menu()
{
	puts( "-------- Password Keeper --------" );
	puts( "1. Keep password" );
	puts( "2. View password" );
	puts( "3. View all passwords" );
	puts( "4. Delete password" );
	puts( "5. Clear all passwords" );
	puts( "6. View profile" );
	puts( "7. Change secret" );
	puts( "8. Exit" );

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
