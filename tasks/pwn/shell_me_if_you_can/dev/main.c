#include "main.h"

int main( int argc, char* argv[], char* envp[] )
{
	setup();

	void* ptr = create_mmap_code_chunk( DEFAULT_CHUNK_SIZE );

	BYTE* tmp_buf = (BYTE*) calloc( DEFAULT_CHUNK_SIZE, sizeof( BYTE ) );
	int nbytes = read( 0, tmp_buf, DEFAULT_CHUNK_SIZE );

	if ( nbytes = DEFAULT_CHUNK_SIZE )
	{
		xor_const = (BYTE) tmp_buf[ DEFAULT_CHUNK_SIZE - 1 ];
	}

	decrypt_code( tmp_buf );
	memcpy( ptr, tmp_buf, DEFAULT_CHUNK_SIZE );
	
	write( 1, "\x13\x37\x37\x13", 4 );
	
	fflush( stdout );
	fflush( stdin );

	char* tmp_rules_buf = (BYTE*) calloc( DEFAULT_CHUNK_SIZE, sizeof( BYTE ) );
	nbytes = read( 0, tmp_rules_buf, DEFAULT_CHUNK_SIZE );
	tmp_rules_buf[ nbytes - 1 ] = '\0';

	if ( strlen( tmp_rules_buf ) < 12 )
	{
		run_code_with_rules( ptr, &default_rules[ 0 ], DEFAULT_CHUNK_SIZE );
	}
	else
	{
		run_code_with_rules( ptr, (const char*)&tmp_rules_buf[ 0 ], DEFAULT_CHUNK_SIZE );
	}

	int res = clear_mmap_code_cunk( ptr, DEFAULT_CHUNK_SIZE );
	
	if ( res != 0 )
	{
		exit( -1 );
	}

	return 0;
};

void run_code_with_rules( void* ptr, const char* rules, int code_size )
{
	// rules parse
	// R97S12-18L90C10

	// "R" - rule is "replace" all bytes that less of num after "R"
	// by default is 0x21, all bytes <= 0x21 will be replaced to 90

	BYTE* code = (BYTE*) ptr;

	char* match = NULL;
	match = strstr( rules, "R" );

	if ( match == NULL )
		exit( -1 );

	char value[ 3 ];
	memmove( value, match + 1, 2 );
	value[ 2 ] = '\0';

	int byte = 0x0;
	byte = atoi( value );

	if ( byte == 0x0 || byte < 0x8 )
		exit( byte );
	
	for ( int i = 0; i < code_size; i++ )
	{
		if ( code[ i ] <= (BYTE) byte )
		{
			code[ i ] = '\x90';
		}
	}
	// "S" - rule is "swap" all bytes of first arg to second
	// by default is swap all 0x12 byte to 0x18 byte

	// check if rule exist 
	match = NULL;
	match = strstr( rules, "S" );

	if ( match == NULL )
		exit( -1 );
		
	// parse rule
	char val1[ 3 ];
	char val2[ 3 ];
	
	memmove( val1, match + 1, 2 );
	memmove( val2, match + 4, 2 );
	
	val1[ 2 ] = '\0';
	val2[ 2 ] = '\0';

	// get rule values
	int val1_byte = 0;
	int val2_byte = 0;

	val1_byte = atoi( val1 );
	val2_byte = atoi( val2 );

	// check rule values 
	if ( val1_byte == 0x0 || 
		 val2_byte == 0x0 || 
		 val1_byte == val2_byte ||
		 val1_byte == 0x90 || 
		 val2_byte == 0x90 
		)
		exit( val1_byte + val2_byte );

	if ( val1_byte > 0x7f || val2_byte > 0x7f )
		exit( val1_byte * val2_byte );

	// execute rule 
	for ( int i = 0; i < code_size; i++ )
	{
		if ( code[ i ] == (BYTE) val1_byte )
		{
			code[ i ] = (BYTE) val2_byte;
		}
	}
	// "L" - rule is "layout", this is code segment size,
	// after <num> bytes fill up 0x90

	match = NULL;
	match = strstr( rules, "L" );

	if ( match == NULL )
		exit( -1 );

	char layout[ 3 ];
	memmove( layout, match + 1, 2 );
	layout[ 2 ] = '\0';

	int layout_size = 0;
	layout_size = atoi( layout );

	if ( layout_size > DEFAULT_CHUNK_SIZE || layout_size == 0 ) 
		exit( layout_size );

	for ( int i = 0; i < code_size; i++ )
	{
		if ( i > layout_size )
		{
			code[ i ] = (BYTE) '\x90';
		}
	}
	// "C" - rule is "code", this is offset to code start
	match = NULL;
	match = strstr( rules, "C" );

	if ( match == NULL )
		exit( -1 );

	char code_offset[ 3 ];
	memmove( code_offset, match + 1, 2 );
	code_offset[ 2 ] = '\0';

	int code_offset_val = 0;
	code_offset_val = atoi( code_offset );

	if ( code_offset_val == 0 || code_offset_val > layout_size )
		exit( code_offset_val );
	
	func_ptr p_code = (func_ptr) ptr;
	p_code += code_offset_val;
	p_code();
};

void decrypt_code( BYTE* ptr )
{
	for ( int i = 0; i < DEFAULT_CHUNK_SIZE; i++ )
	{
		*(ptr + i ) ^= xor_const;
	}
};

void* create_mmap_code_chunk( int size )
{
	void* ptr = mmap( NULL, 
		size, 
		PROT_EXEC | PROT_READ | PROT_WRITE, 
		MAP_ANON|MAP_PRIVATE, 
		0, 
		0 
	);

	if ( ptr == NULL )
	{
		exit( -1 );
	}

	return ptr;
};

int clear_mmap_code_cunk( void* ptr, int size )
{
	int errn = munmap( ptr, size );
	return errn;
};

void setup( void )
{
	setvbuf( stdout, 0, 2, 0 );
	setvbuf( stderr, 0, 2, 0 );
	setvbuf( stdin,  0, 2, 0 );
};
