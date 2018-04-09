#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <pthread.h> 
#include <semaphore.h> 

int sockfd = 0, n = 0;
char recvBuff[10240];
char sendBuff[10240];
struct sockaddr_in serv_addr;
char *message;

void *Client()
{
	while(1)
	{
		//printf("client: ");
	    fgets(message,50,stdin);  
	    strcpy(sendBuff,message);
	    write(sockfd, sendBuff, strlen(sendBuff));
	}
}

void *Server()
{
	while(1)
	{
		n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
	    
	   // printf("server: "); 	
	    recvBuff[n] = 0;
	    printf("server: %s",recvBuff );
	}
}
int main(int argc, char *argv[])
{
    
	message= (char*)malloc(sizeof(char)*10240);
 /*   if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }*/ 

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5400); 

    if(inet_pton(AF_INET,"127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
   
   pthread_t read,write;
   pthread_create(&write,NULL,Client,NULL);
   pthread_create(&read,NULL,Server,NULL);

   pthread_join(write,NULL);
   pthread_join(read,NULL); 


    return 0;
}