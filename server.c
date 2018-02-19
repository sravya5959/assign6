#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0,n=0;
    struct sockaddr_in serv_addr; 
    char * message;
    char sendBuff[10250];
    char recvBuff[10250];
    char *msg=(char *)malloc(sizeof(char)*10240);
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5400); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
    int i;
    while(1)
    {
        printf("client: ");
        n = read(connfd, recvBuff, sizeof(recvBuff)-1);
        recvBuff[n] = 0;
        printf("%s",recvBuff);
       
        printf("server: ");
        fgets(msg,50,stdin);
       
        strcpy(sendBuff,msg);
        write(connfd, sendBuff, strlen(sendBuff)); 
        sleep(1);
    }
    close(connfd);
    sleep(1);
        
        

}