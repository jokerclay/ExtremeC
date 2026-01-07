#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ABC 5
#define ADD(a, b) a + b
#define CODE \
printf("%d\n", i);

#define PRINT(a) printf("%d\n", a);
// #define LOOP(v, s, e) for (int v = s; v <= e; v++) {
// #define ENDLOOP }


#define CMD(NAME) \
    char NAME ## _cmd[256] = ""; \
    strcpy(NAME ## _cmd, #NAME);

#define VERSION "2.3.4"

#define LOG_ERROR(format, ...) \
 fprintf(stderr, format, __VA_ARGS__)

#define LOOP_3(X, ...) \
 printf("%s\n", #X);
#define LOOP_2(X, ...) \
 printf("%s\n", #X); \
 LOOP_3(__VA_ARGS__)
#define LOOP_1(X, ...) \
 printf("%s\n", #X); \
 LOOP_2(__VA_ARGS__)
#define LOOP(...) \
 LOOP_1(__VA_ARGS__)


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

#if 0

    int x = 2;
    int y = ABC;

    int z = x + y;
    int sum = ADD(x,y);

    banner("Defining a macro");
    printf(" z = x + y \n = %d\n",z);
    printf(" sum = ADD(x,y) \n = %d\n",sum);

    // CODE();

    banner("more difficult example");
    LOOP(counter, 1, 10)
    PRINT(counter)
    ENDLOOP


    banner("# and ## ");

    CMD(copy)
        CMD(paste)
        CMD(theparam)
        CMD(cut)
        char cmd[256];
    scanf("%s", cmd);

    /*

    if (strcmp(cmd, copy_cmd) == 0) {
        // ...
    }
    if (strcmp(cmd, paste_cmd) == 0) {
        // ...
    }
    if (strcmp(cmd, cut_cmd) == 0) {
        // ...
    }
    if (strcmp(cmd, theparam_cmd) == 0) {
        // ...
    }

    */

    if (argc < 3) {
        LOG_ERROR("Invalid number of arguments for version %s\n.",
                  VERSION);
        exit(1);
    }
    if (strcmp(argv[1], "-n") != 0) {
        LOG_ERROR("%s is a wrong param at index %d for version %s.",
                  argv[1], 1, VERSION);
        exit(1);
    }

#endif /* if 0 */

    LOOP(copy paste cut)
    LOOP(copy, paste, cut)
    LOOP(copy, paste, cut, select)

    printf("%s\n", "copy paste cut"); printf("%s\n", ""); printf("%s\n", "");
    printf("%s\n", "copy"); printf("%s\n", "paste"); printf("%s\n", "cut");
    printf("%s\n", "copy"); printf("%s\n", "paste"); printf("%s\n", "cut");

    return 0;

}

