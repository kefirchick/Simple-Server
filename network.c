#include "./network.h"

void server_run(int argc, char *argv[]) {
    if (argc != 3) printf("error: wrong adress");
    char buffer[4096];

    int server_socket = socket(AF_INET,SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    unsigned short port;
    sscanf(argv[1], "%hu", &port);
    address.sin_port = htons(port);
    inet_aton(argv[2], &address.sin_addr);

    bind(server_socket, (struct sockaddr *) &address, sizeof(address));
    
    int is_listen = listen(server_socket, 8);
    if (is_listen < 0) {
        printf("error: server is not listening.\n");
    }

    int clientSocket;
    while(1) {
        clientSocket = accept(server_socket, NULL, NULL);
        read_file(buffer, argv[3]);
        send(clientSocket, buffer, strlen(buffer), 0);
        close(clientSocket);
    }
}

void read_file(char buffer[], char path[]) {
    char header[64] = "HTTP/1.1 200 OK\r\n\n";
    memset(buffer, '\0', strlen(buffer));
    strcat(buffer, header);

    FILE *fp = fopen(path, "r");

    char line[128];
    while (fgets(line, 128, fp) != 0) {
        strcat(buffer, line);
    }
    fclose(fp);
}