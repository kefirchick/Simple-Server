#include "./network.h"

void parse_args(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    parse_args(argc, argv);
    server_run();
    return 0;
}

void parse_args(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("%s \n", argv[i]);
    }
}