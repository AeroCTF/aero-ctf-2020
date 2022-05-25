#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>

#define MAIN_JOURNAL_FILE_PATH "/tmp/journal.txt"
#define READ_INT_ERROR 0xdeadbeef


struct journal { 
	char sub_buf[ 1024 ];
	char main_buf[ 512 ];

	FILE* main_fp;
	FILE* sub_fp;
};

struct journal *nav_jr;
char alph[62] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789\0";
char bad_chars[14] = "./\\tkasnfhglxd";
char name[84];

void setup( void );
void print_menu( void );
int read_int( void );

void open_main_journal( void );
void read_main_journal( void );
void close_main_journal( void );
int create_sub_journal( void );
void read_sub_journal( void );
void write_sub_journal( void );
void close_sub_journal( void );
void change_username( void );

int main()
{
	setup();
	int lifes = 3;

	printf( "Enter your name: " );
	int nbytes = read( 0, name, 84 );
	name[ nbytes - 1 ] = '\0';

	printf( "Hello, %s\n", name );

	while( 1 )
	{
		if ( lifes == 0 )
			exit( -1 );

		print_menu();
		int option = read_int();

		if ( option == READ_INT_ERROR )
			exit( READ_INT_ERROR );

		switch( option )
		{
			case 1:
				open_main_journal();
				break;
			case 2:
				read_main_journal();
				break;
			case 3:
				close_main_journal();
				break;
			case 4:
				create_sub_journal();
				break;
			case 5:
				write_sub_journal();
				break;
			case 6:
				read_sub_journal(); 
				break;
			case 7:
				close_sub_journal(); 
				break;
			case 8:
				change_username();
				break;
			case 9:
				exit( -4 );
				break;
			default:
				puts( "{-} Incorrect option!" );
				lifes -= 1;
				break;
		} 
	}

};


void setup( void )
{
	nav_jr = (struct journal*) malloc( sizeof( struct journal ) );
	
	nav_jr->main_fp = NULL;
	nav_jr->sub_fp = NULL;

	memset( nav_jr->main_buf, 0, 512 );
	memset( nav_jr->sub_buf, 0, 1024 );

	alarm( 5 );

	setvbuf( stdout, 0, 2, 0 );
  	setvbuf( stderr, 0, 2, 0 );
  	setvbuf( stdin,  0, 2, 0 );
};

void print_menu( void )
{
	puts( "------ Navigation Journal ------" );
	puts( "1. Open main journal" );
	puts( "2. Read main journal" );
	puts( "3. Close main journal" );
	puts( "4. Create sub journal" );
	puts( "5. Write sub journal" );
	puts( "6. Read sub journal" );
	puts( "7. Close sub journal" );
	puts( "8. Change username" );
	puts( "9. Exit" );
	printf( "> " );
};

int read_int( void )
{
	char buf[ 16 ];

	int nbytes = read( 0, buf, 16 );

	if ( nbytes > 0 )
	{
		buf[ nbytes - 1 ] = '\0';
	}

	unsigned int result = atoi( buf );

	if ( result > 0 )
		return result;
	
	return READ_INT_ERROR;
};

void open_main_journal( void )
{
	nav_jr->main_fp = fopen( MAIN_JOURNAL_FILE_PATH, "r" );

	if ( nav_jr->main_fp == NULL )
	{
		puts( "{-} Some error in main journal open!" );
		puts( "{-} Tell admin!" );
		exit( -3 );
	}
	else
	{
		puts( "{+} Main journal is successfully open!" );
	}
};

void read_main_journal( void )
{
	if ( nav_jr->main_fp != NULL )
	{
		int nbytes = fread( nav_jr->main_buf, 1, 512, nav_jr->main_fp );

		if ( nbytes > 0 )
		{
			puts( "{+} Main journal content: " );
			write( 1, nav_jr->main_buf, 512 );
		}
		else
		{
			puts( "{-} Some error in read main journal!" );
		}
	}
	else
	{
		puts( "{-} Main journal is not open!" );
	}
};

void close_main_journal( void )
{
	if ( nav_jr->main_fp != NULL )
	{
		fclose( nav_jr->main_fp );
		nav_jr->main_fp = NULL;
		puts( "{+} Main journal is successfully closed!" );
	}
	else
	{
		puts( "{-} Main journal is not open!" );
	}
};

char* generate_random_name( void )
{
	char* rnd_name = (char*) malloc( 32 );
	memset( rnd_name, 0, 32 );

	unsigned char rnd_idx[ 16 ];

	FILE* fp = fopen( "/dev/urandom","r" );

	if ( fp != NULL )
	{
		int nbytes = fread( rnd_idx, 1, 16, fp );

		if ( nbytes <= 0 )
		{
			puts( "{-} Some internal erorr!" );
			puts( "{-} Tell admin!" );
			exit( -2 );
		}
	}
	else
	{
		puts( "{-} Some internal error!" );
		puts( "{-} Tell admin!" );
		exit( -1 );
	}

	for ( int i = 0; i < 16; i++ )
	{
		int idx = (int) rnd_idx[ i ];
		idx %= 62;
		rnd_name[ i ] = alph[ idx ];
	}

	return rnd_name;
}

int create_sub_journal( void )
{
	if ( nav_jr->sub_fp != NULL )
	{
		puts( "{-} Sub journal already created!" );
		return 1;
	}

	char* journal_name = (char*) malloc( 128 );
	memset( journal_name, 0, 128 );
	strcat( journal_name, "/tmp/" );

	char* random_name = generate_random_name();
	strcat( journal_name, random_name );
	free( random_name );

	printf( "{+} Creating journal with name <%s>\n", journal_name );
	printf( "{?} Do you agree with this name?[Y\\N]: " );
	
	char buf[4];
	int nbytes = read( 0, buf, 4 );
	buf[ nbytes - 1 ] = '\0';

	if ( buf[ 0 ] == 'N' )
	{
		printf( "{?} Enter your name: " );
		char name[ 6 ];
		int nbytes = read( 0, name, 6 );

		for ( int i = 0; i < nbytes; i++ )
		{
			for ( int j = 0; j < 13; j++ )
			{
				if ( name[ i ] == bad_chars[ j ] )
				{
					name[ i ] = ' ';
				}
			}
		}

		memset( journal_name, 0, 128 );
		strcat( journal_name, "/tmp/" );
		strcat( journal_name, name );

		printf( "{+} New file name: " );
		printf( journal_name );
	}

	nav_jr->sub_fp = fopen( journal_name, "w" );

	// if ( nav_jr->sub_fp == NULL )
	// {
	// 	puts( "{-} Some error in sub journal open!" );
	// 	puts( "{-} Tell admin!" );
	// 	exit( -7 );
	// }

	return 0;
};

void close_sub_journal( void )
{
	if ( nav_jr->sub_fp != NULL )
	{
		fwrite( nav_jr->sub_buf, 1, 1024, nav_jr->sub_fp );
		fclose( nav_jr->sub_fp );
		nav_jr->sub_fp = NULL;
	}
	else
	{
		nav_jr->sub_fp = NULL;
	}
};

void read_sub_journal( void )
{
	puts( "{+} Sub journal content: " );
	write( 1,  nav_jr->sub_buf, 1540 );
};

void write_sub_journal( void )
{
	printf( "{?} Enter data: " );
	int nbytes = read( 0, nav_jr->sub_buf, 1540 );
};

void change_username( void )
{
	printf( "{?} Enter new username: " );
	int nbytes = read( 0, name, 84 );
	name[ nbytes - 1 ] = '\0';
}