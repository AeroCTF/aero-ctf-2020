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
    char flag[] = "jgznmhf,jnf726"; //опятьработа726
    char sym;
    char newSym;
    srand(0x1337);

    for(int i = 0; i < 14; i++){
        sym = rand()%0xFF;
        printf("%x\n", (sym^flag[i])&0xFF);
    }

    return 0;
}
