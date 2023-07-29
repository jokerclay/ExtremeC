#include <stdio.h>
#include <stdlib.h>
#define DEBUG 1

int main(int argc, char *argv[])
{

#if DEBUG
    printf("debugging\n");
    printf("debugging\n");
    printf("debugging\n");
    printf("debugging\n");
    printf("debugging\n");

#else 
    printf("hello world\n");

#endif /* if DEBUG */

    return EXIT_SUCCESS;
}
