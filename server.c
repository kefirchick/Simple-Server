#include "./network.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Error: wrong argument count.\n");
        return 1;
    } else {
        if (server_run(argv) == 1) {
            return 1;
        }
    }
    return 0;
}