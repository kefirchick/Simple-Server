#include "./network.h"

int server_run(char *argv[]) {
    char buffer[4096];

    int server_socket = socket(AF_INET,SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    unsigned short port;
    if (sscanf(argv[1], "%hu", &port) == 0) {
        printf("Error: wrong port");
        return 1;
    };
    address.sin_port = htons(port);
    if (inet_aton(argv[2], &address.sin_addr) == 0) {
        printf("Error: wrong address");
        return 1;
    };

    bind(server_socket, (struct sockaddr *) &address, sizeof(address));
    
    listen(server_socket, 8);

    if (read_file(buffer, argv[3]) == 1) {
        printf("Error: wrong file name");
        return 1;
    }

    int clientSocket;
    while(1) {
        clientSocket = accept(server_socket, NULL, NULL);
        read_file(buffer, argv[3]);
        send(clientSocket, buffer, strlen(buffer), 0);
        close(clientSocket);
    }
    return 0;
}

int read_file(char buffer[], char path[]) {
    char header[64] = "HTTP/1.1 200 OK\r\n\n";
    char line[128];

    memset(buffer, '\0', strlen(buffer));
    strcat(buffer, header);
    FILE *fp = fopen(path, "r");
    if (fp != NULL) {
        while (fgets(line, 128, fp) != 0) {
            strcat(buffer, line);
        }
        fclose(fp);
    } else {
        return 1;
    }
    return 0;
}

int file_name_check(char path[]) {
    char extention[5] = ".html";
    for (int i = 0; i < 5; i++) {
        if (extention[4-i] != path[strlen(path)-i]) {
            printf("!!!!!!!!!!");
        }
    }
    return 0;
}