# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

# define SERVER_ADDR "127.0.0.1"

void Communicate(int sock)
{     printf("SERVER Chat Terminal\n");
   char buf[1024];
   int quit;
	int n;
	while(1)
	{      bzero(buf,1024);
	        n=recv(sock,buf,sizeof(buf),0);
	          quit = strcmp(buf,"bye");
	          if(quit==10)
	  	  {quit=0;}
                if(quit == 0)
                {
	         printf("\nClient: %s",buf);
		 close(sock);
                // printf("\nClient left\n\n");
		 break;
                }
               else
         	{
	       	printf("\nClient: %s",buf);
		bzero(buf,1024);
		printf("Server Reply: ");
		fgets(buf,sizeof(buf)-1,stdin);
		send(sock,buf,strlen(buf),0);
         	}
      }
	}	



void main(int argc,char *argv[])
{

	int serverSocfd,port,newsocketd,size;
	struct sockaddr_in server,client;
	


        // Socket Creation
	serverSocfd = socket(AF_INET,SOCK_STREAM,0);
	if(serverSocfd<0)
	{
		perror("Socket Error");
		exit(0);
	}

	port = atoi(argv[1]);
		server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	server.sin_port = port;
	
      
        // binding
        int  n = bind(serverSocfd,(struct sockaddr*)&server,sizeof(server));
	if(n<0)
{
	perror("The destination port and Ip binding unsuccesfull");
                exit(0);
}
       printf("Binded to port no %d\n",port);


         
        // Listening
	listen(serverSocfd,5);
	printf("..............Listening..............\n");

	//Accepting and communicating
	while(1)
	{
		size = sizeof(client);
		newsocketd = accept(serverSocfd,(struct sockaddr*)&client,&size);    
		printf("******************************Connection Established with client***************************\n\n");
		Communicate(newsocketd);

	}
       close(serverSocfd);
}
