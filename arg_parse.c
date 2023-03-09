#include "./arg_parse.h"

void parse_args(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("%s \n", argv[i]);
    }
}