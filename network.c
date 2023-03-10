#include "./network.h"

int server_run(char *argv[]) {
    char buffer[BUFF_SIZE];
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // set port number from the first argument
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    unsigned short port;
    if (sscanf(argv[1], "%hu", &port) == 0) {
        printf("Error: wrong port");
        return 1;
    };

    // set address from the second argumet
    address.sin_port = htons(port);
    if (inet_aton(argv[2], &address.sin_addr) == 0) {
        printf("Error: wrong address");
        return 1;
    };

    bind(server_socket, (struct sockaddr *)&address, sizeof(address));
    listen(server_socket, BACKLOG);

    // get and check file path from the third argument
    if (file_name_check(argv[3]) == 1 || read_file(buffer, argv[3]) == 1) {
        printf("Error: wrong file name");
        return 1;
    }

    printf("Check at your browser link \"http://%s:%s\"\n", argv[2], argv[1]);
    while (1) {
        int clientSocket = accept(server_socket, NULL, NULL);
        read_file(buffer, argv[3]);
        send(clientSocket, buffer, strlen(buffer), 0);
        close(clientSocket);
    }
    return 0;
}

int read_file(char buffer[], char path[]) {
    char header[64] = "HTTP/1.1 200 OK\r\n\n";
    memset(buffer, '\0', strlen(buffer));
    strcat(buffer, header);
    FILE *fp = fopen(path, "r");
    if (fp != NULL) {
        char line[128];
        while (fgets(line, LINE_LEN, fp) != 0) {
            strcat(buffer, line);
        }
        fclose(fp);
    } else {
        return 1;
    }
    return 0;
}

int file_name_check(char path[]) {
    if (strlen(path) < 5) {
        return 1;
    }
    const char extention[5] = ".html";
    for (int i = 0; i < 5; i++) {
        if (extention[4 - i] != path[strlen(path) - i - 1]) {
            return 1;
        }
    }
    return 0;
}