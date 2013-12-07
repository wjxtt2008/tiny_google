// gcc -o name_server name_server.c name_server.h


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdlib.h>
#include "name_server.h"

#define BUFFSIZ 1024

char* get_ip(){ // get ip address
	int inet_sock;
	struct ifreq ifr;
	inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
	strcpy(ifr.ifr_name, "eth0");
	if (ioctl(inet_sock, SIOCGIFADDR, &ifr) < 0)
		perror("ioctl");
	return  inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr);
}

struct server_info{
	char type[10];
	char ip[100];
	char port[10];
};


void main() 
{

	struct	sockaddr_in local,remote;
	int		errno,sk,rlen=sizeof(remote),len=sizeof(local);
	char	buf[BUFFSIZ];


	sk=socket(AF_INET,SOCK_DGRAM,0);  /* open socket*/

	local.sin_family=AF_INET;         /* Define the socket domain   */
	local.sin_addr.s_addr=INADDR_ANY; /* Wild-card, machine address */
	local.sin_port=0;                 /* Let the system assign the port number */

	bind(sk,(struct sockaddr *)&local,sizeof(local)); /* bind socket */

	getsockname(sk,(struct sockaddr *)&local,&len);          /* Get the port number assigned */
	printf("socket has port %d\n",local.sin_port); /* Display port number */

	char local_ip[100];
	strcpy(local_ip,get_ip());
	
	char local_port[10];
	sprintf(local_port,"%d",local.sin_port);

	printf("ip:%s, port:%s\n", local_ip, local_port);


	FILE *file = fopen("name.txt", "w"); //save ip port to file
	if (file != NULL) {		
		fprintf (file, "%s %s", local_ip, local_port);	
		fclose (file);
	}

	printf("Save finished.\n");

	while(1) {

		//errno=recvfrom(sk,&temp_packet,sizeof(temp_packet),0,(struct sockaddr *)&remote,&rlen);
		errno = recvfrom(sk, &buf, sizeof(buf), 0, (struct sockaddr *)&remote, &rlen);
		printf("errno%d %s\n", errno, buf);

		struct server_info *new_server = malloc(sizeof(struct server_info));

		strcpy(new_server->type, strtok(buf, " "));
		strcpy(new_server->ip , strtok(NULL, " "));
		strcpy(new_server->port , strtok(NULL, " "));

		//printf("%s\n",buf);
		//sendto(sk,MSG,strlen(MSG)+1,0,(struct sockaddr *)&remote,sizeof(remote));
	}
	close(sk);
}
