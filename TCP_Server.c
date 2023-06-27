#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5555

int main(void)
{
    int s, s2, t, len; 		
    struct sockaddr_in local, remote;
    char str[100];

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
  {
        perror("socket creation failed…\n");
        exit(1);
    }

    bzero((char *)&local,sizeof(local));
    bzero((char *)&remote,sizeof(remote));
    local.sin_family = AF_INET;
    local.sin_port =htons(PORT);
    local.sin_addr.s_addr =htonl(INADDR_ANY);


    
    if (bind(s, (struct sockaddr *)&local,sizeof(local)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }
    len=sizeof(remote);
	 
    for(;;) {
        int done, n;
        printf("Waiting for a connection...\n");
        t = sizeof(remote);
        if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
            perror("accept");
            exit(1);
        }

        printf("Connected.\n");

        while(1)
        {
            n = recv(s2, str, 100, 0);
            if (n == -1) {
               printf("error in recieving");
               exit(1);
            }
            printf(("serverecho> %s\n",str));  
        
           printf("\nEnter data to be sent to client: ");
		fgets(str,100,stdin);
			if(strncmp(str,"end",3)==0)
			break;
			n=send(s2,str,100,0);
			if(n==-1)
			{
				printf("Error in sending");
				exit(1);
			}
        } 	

        close(s2);
    }

    return 0;
}
