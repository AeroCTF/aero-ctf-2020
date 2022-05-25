#include <stdio.h>
#include <string.h>
#include <time.h> 
#include <stdlib.h>
#include <unistd.h>

#define CHUNK_SIZE 0x80
#define ID_SIZE 9

void setup( void );

struct ticket
{
	char* from; // + 0
	char* to; // + 8 
	int date; // + 16
	char* owner; // +  24
	int cost; // + 32
	char id[ ID_SIZE ]; // + 36
};

struct list_entry 
{
	struct ticket* entry;
	struct list_entry* next;
	struct list_entry* prev;
};

#define LIST_ENTRY_SIZE sizeof( struct list_entry ) 

int cur_list_size = 0;
struct list_entry* list_head = NULL;
struct list_entry* list_tail = NULL;

struct ticket* cache[ 8 ];
char name[ CHUNK_SIZE ];
int name_size = 0;

// utilites
int read_buf( char* buf, int max_size );
int read_int();
void setup( void );
void generate_ticket_id( char* buf );

// UI
void menu( void );
void reserve_ticket( void );
void view_ticket( void );
int view_ticket_list( void );
void delete_ticket( void );
void change_name( void );
void print_ticket_info( struct ticket* tick );

// Double linked list utilites
void add_to_list( struct ticket* entry );
int del_from_list( struct ticket* entry );
struct ticket* get_elem_by_id( char* id );

// cache utilities funcs
void drop_list_in_cache( void );
struct ticket* find_in_cache( char* _id );

void read_admin_ticket(void) __attribute__((constructor));

void read_admin_ticket(void)
{
	char filename[] = "/tmp/flag.txt";

	FILE* fp = fopen( filename, "r" );

	if ( fp == NULL )
	{
		exit( -1 );
	}

	struct ticket* adm_ticket = (struct ticket*) malloc( sizeof( struct ticket ) );
	char* _from = (char*) malloc( CHUNK_SIZE );
	char* _to = (char*) malloc( CHUNK_SIZE );
	char* _owner = (char*) malloc( CHUNK_SIZE );
	

	adm_ticket->from = _from;
	adm_ticket->to = _to;
	adm_ticket->owner = _owner;

	fgets( adm_ticket->from, CHUNK_SIZE, fp );
	adm_ticket->from[ strlen( adm_ticket->from ) - 1 ] = '\0';

	fgets( adm_ticket->to, CHUNK_SIZE, fp );
	adm_ticket->to[ strlen( adm_ticket->to ) - 1 ] = '\0';

	char tmp_buf[ CHUNK_SIZE ];

	fgets( tmp_buf, CHUNK_SIZE, fp );
	adm_ticket->date = atoi( tmp_buf );
	memset( tmp_buf, 0, CHUNK_SIZE );

	fgets( adm_ticket->owner, CHUNK_SIZE, fp );
	adm_ticket->owner[ strlen( adm_ticket->owner ) - 1 ] = '\0';

	fgets( tmp_buf, CHUNK_SIZE, fp );
	adm_ticket->cost = atoi( tmp_buf );

	fgets( adm_ticket->id, ID_SIZE, fp );
	fclose( fp );

	add_to_list( adm_ticket );
};


// ticket storage
int main()
{
	setup();
	int lifes = 3;

	printf( "{?} Enter name: " );
	name_size = read_buf( name, CHUNK_SIZE+8 ) - 1;

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
				reserve_ticket();
				break;
			case 2:
				view_ticket();
				break;
			case 3:
				view_ticket_list();
				break;
			case 4:
				delete_ticket();
				break;
			case 5:
				change_name();
				break;
			case 6:
				exit( -1 );
				break;
			default:
				lifes -= 1;
				break;
		}
	}

	return 0;
};

void change_name( void )
{
	printf( "{?} Enter name: " );
	name_size = read_buf( name, CHUNK_SIZE + 8 );
};

struct ticket* get_elem_by_id( char* _id )
{
	if ( list_head == NULL )
	{
		puts( "{-} No tickets available!" );
		return NULL;
	}

	struct list_entry* pHead = list_head;

	do {
		// check id
		int res = memcmp( pHead->entry->id, _id, ID_SIZE );

		if ( !res )
		{
			return pHead->entry;
		}

		pHead = pHead->next;
	} while( pHead != NULL );

	return NULL;
};

int del_from_list( struct ticket* tick )
{
	struct list_entry* pHead = list_head;
	struct list_entry* deleted_entry = NULL;

	do {
		if ( pHead->entry == tick )
		{
			deleted_entry = pHead;
			break;
		}

		pHead = pHead->next;
	} while( pHead != NULL );

	if ( deleted_entry == NULL )
		return 0;

	if ( deleted_entry == list_head ) 
		list_head = deleted_entry->next;

	if ( deleted_entry->next != NULL )
		deleted_entry->next->prev = deleted_entry->prev;

	if ( deleted_entry->prev != NULL )
		deleted_entry->prev->next = deleted_entry->next;

	free( tick->from );
	free( tick->to );
	free( tick->owner );
	free( tick );
	free( deleted_entry );

	return 1;
}

void delete_ticket( void )
{
	char ticket_id[ ID_SIZE ];
	printf( "{?} Enter ticket id: " );
	read_buf( ticket_id, ID_SIZE );

	struct ticket* tick = get_elem_by_id( ticket_id );

	if ( tick == NULL )
	{
		puts( "{-} Ticket not found!" );
	}
	else
	{
		del_from_list( tick );
	}
};

void print_ticket_info( struct ticket* tick )
{
	printf( "---- Ticket %8s ----\n", tick->id );
	printf( "From: %s\n", tick->from );
	printf( "To: %s\n", tick->to );
	printf( "Date: %d\n", tick->date );
	printf( "Cost: %d\n", tick->cost );
	printf( "Owner: %s\n", tick->owner );	
};

struct ticket* find_in_cache( char* _id )
{
	if ( cur_list_size < 8 )
	{
		return NULL;
	} 

	for ( int i = 0; i < 8; i++ )
	{
		// check id
		int res = memcmp( cache[ i ]->id, _id, ID_SIZE );

		if ( !res )
		{
			return cache[ i ];
		}
	}

	return NULL;
};

void view_ticket()
{
	char ticket_id[ ID_SIZE ];
	printf( "{?} Enter ticket id: " );
	read_buf( ticket_id, ID_SIZE );

	struct ticket* tick = find_in_cache( ticket_id );

	if ( tick == NULL )
		tick = get_elem_by_id( ticket_id );

	if ( tick == NULL )
	{
		puts( "{-} Ticket not found!" );
	}
	else
	{
		print_ticket_info( tick );
	}
}

int view_ticket_list()
{
	if ( list_head == NULL )
	{
		puts( "{-} No tickets available!" );
		return 0;
	}

	struct list_entry* pHead = list_head;

	do {
		// check owner name
		int res = memcmp( pHead->entry->owner, name, name_size );

		if ( !res )
		{
			print_ticket_info( pHead->entry );
		}

		pHead = pHead->next;
	} while ( pHead != NULL );

	return 1;
}

void drop_list_in_cache( void )
{
	struct list_entry* pTail = list_tail;
	int cache_idx = 0;

	do {
		cache[ cache_idx ] = pTail->entry;
		pTail = pTail->prev;
		cache_idx += 1;
	} while ( pTail != NULL && cache_idx < 8 );
};

void add_to_list( struct ticket* entry )
{
	if ( list_head == NULL )
	{
		list_head = (struct list_entry*) malloc( LIST_ENTRY_SIZE );
		
		list_head->entry = entry;
		list_head->next = NULL;
		list_head->prev = NULL;

		list_tail = list_head;
	}
	else
	{
		struct list_entry* new_entry = (struct list_entry*) malloc( LIST_ENTRY_SIZE );

		new_entry->entry = entry;
		new_entry->next = NULL;
		new_entry->prev = list_tail;

		list_tail->next = new_entry;
		list_tail = new_entry;
	}

	cur_list_size += 1;

	if ( cur_list_size == 8 )
	{
		drop_list_in_cache();
	}
};

void generate_ticket_id( char* buf )
{
	char alph[62] = "qwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNM";

	unsigned char idxs[ 8 ];

	FILE* fp = fopen( "/dev/urandom", "r" );

	if ( fp == NULL )
	{
		puts( "{-} Some internal error!" );
		puts( "{-} Tell admin!" );
		exit( -123 );
	}

	int nbytes = fread( idxs, 1, 8, fp );
		
	if ( nbytes <= 0 )
	{
		puts( "{-} Some internal erorr!" );
		puts( "{-} Tell admin!" );
		exit( -133 );
	}

	fclose( fp );
	fp = NULL;

	for ( int i = 0; i < 8; i++ )
	{
		int idx = 0;
		idx = idxs[ i ] % 62;

		buf[ i ] = alph[ idx ];
	}

	buf[ 8 ] = '\0';
};

void reserve_ticket( void )
{
	// make new ticket obj
	struct ticket* new_ticket = (struct ticket*) malloc( sizeof( struct ticket ) );

	// add departure city to tikcet
	char* _from = (char*) malloc( CHUNK_SIZE );
	printf( "{?} Enter departure city: " );
	read_buf( _from, CHUNK_SIZE );

	new_ticket->from = _from;

	// add destination city to ticket
	char* _to = (char*) malloc( CHUNK_SIZE );
	printf( "{?} Enter destination city: " );
	read_buf( _to, CHUNK_SIZE );

	new_ticket->to = _to;

	// add cost
	printf( "{?} Enter the desired cost: " );
	int _cost = read_int();
	new_ticket->cost = _cost;

	// add owner
	char* _owner = (char*) malloc( name_size );
	memcpy( _owner, name, name_size );
	new_ticket->owner = _owner;

	// add date
	new_ticket->date = time( NULL );

	generate_ticket_id( new_ticket->id );
	printf( "{+} Your ticket id: %s\n", new_ticket->id );
	add_to_list( new_ticket );
};

void setup( void )
{
	alarm( 5 );

	setvbuf( stdin,  0, 2, 0 );
	setvbuf( stdout, 0, 2, 0 );
	setvbuf( stderr, 0, 2, 0 );
};

void menu()
{
	puts( "-------- Ticket Storage --------" );
	puts( "1. Reserve a ticket" );
	puts( "2. View ticket" );
	puts( "3. View ticket list" );
	puts( "4. Delete ticket" );
	puts( "5. Change name" );
	puts( "6. Exit" );

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