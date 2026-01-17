#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    const char* target = "./build/00_main";
    const char* source = "./00/main.c";

    if (argc > 1 && strcmp(argv[1], "clean") == 0) {
        Nob_Cmd cmd = {0};
        nob_cmd_append(&cmd, "rm", "-rf", "build", "nob.old", "02/code/main", "02/code/main.o");
        if (!nob_cmd_run(&cmd)) return 1;
        return 0;
    }

    if (!nob_mkdir_if_not_exists("build")) return 1;

    Nob_Cmd build_cmd = {0};
    nob_cmd_append(&build_cmd, "cc", "-Wall", "-Wextra", "-o", target, source);
    if (!nob_cmd_run(&build_cmd)) return 1;

    Nob_Cmd run_cmd = {0};
    nob_cmd_append(&run_cmd, target);
    if (!nob_cmd_run(&run_cmd)) return 1;

    return 0;
}
