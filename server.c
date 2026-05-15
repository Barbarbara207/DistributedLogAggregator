#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>

// quando c'è errore chiama questa func
void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "usage: %s port\n", argv[0]);
        exit(1);
    }

    int sockfd, newsockfd, portno, n;
    char buffer[255];

    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    // pulisce cose
    bzero((char *) &serv_addr, sizeof(serv_addr));

    // converte primo argv (indirizzo) da stringa a intero
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
        error("ERROR on accept");
    }

    while (1) {
        //pulisce buffer
        bzero(buffer,255);

        //legge tutto quello che arriva in sockfd
        n = read(newsockfd, buffer, 255);
        if (n < 0) {
            error("ERROR reading from socket");
        }
        printf("Client: %s\n",buffer);
        bzero(buffer,255);
        fgets(buffer,255,stdin);

        n = write(newsockfd, buffer, 255);
        if (n < 0) {
            error("ERROR writing to socket");
        }
        //"string compare" confronta quello che si è scritto con il codice di uscita dal loop che
        // in questo caso è "Bye"
        int i = strncmp("Bye", buffer, 3);
        if (i == 0) {
            break;
        }
    }
    close(newsockfd);
    close(sockfd);

    return 0;
}