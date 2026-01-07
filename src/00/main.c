#include <stdio.h>
#include <stdlib.h>


#define NOB_IMPLEMENTATION
#include "../nob.h"


#define DEBUG 1

int main(void)
{

#if DEBUG
    nob_log(NOB_INFO, "Using nob_log from nob.h");
    
#else 
    printf("hello world\n");

#endif // DEBUG

    return EXIT_SUCCESS;
}
