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
#include <pthread.h> 
#include <semaphore.h> 

int listenfd = 0, connfd = 0,n=0;
struct sockaddr_in serv_addr; 
char * message;
char sendBuff[10250];
char recvBuff[10250];
char *msg;

void *Client()
{
    while(1)
    {
        //printf("client: ");
        n = read(connfd, recvBuff, sizeof(recvBuff)-1);
        recvBuff[n] = 0;
        printf("client:%s",recvBuff);
    }
}

void *Server()
{
    while(1)
    {
        //printf("server: ");
        fgets(msg,50,stdin);
        strcpy(sendBuff,msg);
        write(connfd, sendBuff, strlen(sendBuff));
    }
}

int main(int argc, char *argv[])
{
    msg=(char *)malloc(sizeof(char)*10240);
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5400); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
    
    //close(connfd);
    pthread_t read,write;
    pthread_create(&read,NULL,Client,NULL);
   pthread_create(&write,NULL,Server,NULL);

   pthread_join(read,NULL);
   pthread_join(write,NULL); 
        
    return 0;

}