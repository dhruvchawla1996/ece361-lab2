#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <ctype.h>
#include <arpa/inet.h>
#include "lab3database.h"

#define MAX_BACKLOG 20

struct client {
    char ID[MAX_NAME];
    char sessionID[MAX_NAME];
    int socket;
    struct client *next;
};

struct session_client_list {
    char ID[MAX_NAME];
    struct session_client_list* next;
};

struct session {
    char ID[MAX_NAME];
    struct session_client_list* client_list;
    struct session* next;
};

struct client *client_list;
struct session *session_list;

void handle_new_connection(struct sockaddr_in, int);

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Usage: ./server <port no>\n");
        return 0;
    }

    int port_listen = atoi(argv[1]);

    client_list = NULL;
    session_list = NULL;

    int sockfd; // socket to listen on
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error: Socket can't be created\n"); return 0;
    }

    struct sockaddr_in serv_addr, cli_addr; // structs to store server and client address info
    serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_listen);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// don't need to bind socket to specific IP
	memset(serv_addr.sin_zero, '\0', sizeof(serv_addr.sin_zero));

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("Error: Socket bind call not successful\n"); return 0;
    }

    if (listen(sockfd, MAX_BACKLOG) < 0) {
        printf("Error: Socket can't listen\n"); return 0;
    }

    fd_set read_fds;
    int fdmax = sockfd;
    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(sockfd, &read_fds);

        struct client* temp = client_list;
        while(temp != NULL) {
            FD_SET(temp->socket, &read_fds);
            fdmax = (fdmax < temp->socket) ? temp->socket : fdmax;
            temp = temp->next;
        }

        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            printf("Error: Select went wrong\n"); return 0;
        }

        if (FD_ISSET(sockfd, &read_fds)) {
            handle_new_connection(cli_addr, sockfd); // handle new connections
        } else {
            struct client* temp = client_list;
            while(temp != NULL) {
                if (FD_ISSET(temp->socket, &read_fds)) break;
                temp = temp->next;
            }
            if (temp != NULL) {} // handle client on call
        }
    }

    return 0;
}

void handle_new_connection (struct sockaddr_in cli_addr, int sockfd) {
    int cli_len = sizeof(cli_addr);
    if (accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len) < 0) {
        printf("Error: Accepting new connection\n"); return;
    }

    return;
}
