#include "./network.h"
#include "./arg_parse.h"

int main(int argc, char *argv[]) {
    parse_args(argc, argv);
    server_run();
    return 0;
}