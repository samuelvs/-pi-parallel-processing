#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//socket
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include <math.h>

struct sockaddr_in remoto;

#define PORTA 8888
#define LEN 4096
int main(){
    int sockfd;
    int slen;
    int len = sizeof(remoto);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd== -1){
        perror("socket ");
        exit(1);
    } 
    else {
        printf("Socket criado com sucesso\n");
    }
    
    remoto.sin_family        = AF_INET;
    remoto.sin_port          = htons(PORTA);
    remoto.sin_addr.s_addr   = inet_addr("127.0.0.1");
    memset(remoto.sin_zero, 0x0, 8);

    if(connect(sockfd, (struct sockaddr*)&remoto,  len) == -1){
        perror("connect ");
        exit(1);
    } else {
        printf("conectado com o servidor");
    }
    double msgRead;
    double result;
    while(1){
        if(recv(sockfd, &msgRead, sizeof(msgRead), 0) > 0){
            break;
        }
    }
    int mode = (int)msgRead;
    printf("%d", mode);
    if(mode == 1){
        while(1){
            if((slen = recv(sockfd, &msgRead, sizeof(msgRead), 0)) > 0){
                if(msgRead > -1){
                    result = pow(-1, msgRead) / ((2 * msgRead) + 1);
                    send(sockfd, &result, sizeof(result),0);
                } else {
                    break;
                }
            }
        }
    } else if (mode == 2){
        printf("MODO 2");
    }

    close(sockfd);
    printf("Client/e  encerrado\n");
    return 0;
}