#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void banner(const char* words) {
    int dash_num = strlen(words);
    for (int i = 0; i < dash_num; i++) {
        printf("-");
    }
    printf("\n%s\n", words);
    for (int i = 0; i < dash_num; i++) {
        printf("-");
    }
    printf("\n");
}




int main(int argc, char** argv) {

    banner("FROM SOURCE TO BINARY");
    return 0;

}

