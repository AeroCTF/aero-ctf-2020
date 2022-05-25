#include <stdio.h>
#define RAND_MAX 0x7fff

static unsigned int next = 1;
int rand()
{
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/(65536)) & (RAND_MAX);
}

void srand(unsigned int seed)
{
  next = seed;
}

int main()
{
    char key[]  = {0xac, 0x10, 0x5a, 0xc3, 0xbf, 0x76, 0x31, 0xe9, 0x34, 0x7f,
               0xf, 0x4f, 0x4a, 0xfa};
    char sym;
    srand(0x1337);

    for(int i = 0; i < 14; i++){
        sym = rand()%0xFF;
        printf("%c\n", (sym^key[i])&0xFF);
    }

    return 0;
}
