#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>

#define DEFAULT_CHUNK_SIZE 0x80 

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;
typedef unsigned long long QWORD;
typedef void (*func_ptr)(void);

const char default_rules[] = "R97S12-18L40C30";
const BYTE default_xor_const = 0x7f;
BYTE xor_const = default_xor_const;

void setup( void );
void* create_mmap_code_chunk( int size );
int clear_mmap_code_cunk( void* ptr, int size );
void decrypt_code( BYTE* ptr );
void run_code_with_rules( void* ptr, const char*, int code_size );