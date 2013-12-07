// gcc -o name_test name_test.c name_server.h


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

#define MSG "There are simply GREAT!!!"

void get_name_server(char *line, char *ip, char *port){

}

char* get_ip(void) {
	int inet_sock;
	struct ifreq ifr;
	inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
	strcpy(ifr.ifr_name, "eth0");
	if (ioctl(inet_sock, SIOCGIFADDR, &ifr) < 0)
		perror("ioctl");
	return  inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr);
}

void main()
{

	int	udp_sk,sk;
	//char	buf[BUFSIZ];

	struct	sockaddr_in local,remote;
	struct	hostent *hp,*gethostname();
	

	char ip[100],port[10],buf[200];
	int sent,ip_len,port_len,len=sizeof(local);
	char test[]="this is a test";
	//char op_regmain[]="1 ";


	////// get name server info "ns_*"
	int ns_port;
	char *ns_ip, *ns_port_string;
	FILE *ns_fp;
	char *ns_line;
	size_t ns_len = 0;
	ssize_t ns_read;

	ns_fp = fopen("name.txt", "r");
	if (ns_fp != NULL) {		
		if((ns_read = getline(&ns_line, &ns_len, ns_fp)) != -1) {
			ns_ip = strtok(ns_line, " ");
			ns_port_string = strtok(NULL, " ");
			ns_port = atoi(ns_port_string);
		}else {
			printf("Read name file error");
		}
	}else{
		printf("Read name file error");
	}
	printf("%s : %d\n", ns_ip, ns_port);
	////// end of get name server info


	// setup a UDP to name server

	udp_sk=socket(AF_INET,SOCK_DGRAM,0);
	remote.sin_family=AF_INET;
	if( inet_pton(AF_INET,ns_ip, &remote.sin_addr) <= 0){
		printf("inet_pton error for %s\n",ns_ip);
		exit(0);
	}
	remote.sin_port = ns_port;

	/*********************************************************/
	/* Send the TCP info                                     */ 
	/*********************************************************/

	/* Create an internet domain stream socket */
	sk=socket(AF_INET,SOCK_STREAM,0);

	/*Construct and bind the name using default values*/
	local.sin_family=AF_INET;
	local.sin_addr.s_addr=INADDR_ANY;
	local.sin_port=0;
	bind(sk,(struct sockaddr *)&local,sizeof(local));

	/*Find out and publish socket name */
	getsockname(sk,(struct sockaddr *)&local,&len);
	printf("TCP Socket has port %d\n",local.sin_port);

	/*save ip&port to my_name for registeration*/
	sprintf(port,"%d",local.sin_port);
	strcpy(ip,get_ip());
/*
	ip_len=strlen(ip);
	port_len=strlen(port);
	buf[0]=1;
	strncpy(buf+1,ip,ip_len);
	strncpy(buf+2+ip_len,port,port_len);
	buf[ip_len+port_len+2]='\0';
*/
	//strcat(buf,op_regmain);

	buf[0]='1';
	buf[1]=' ';
	buf[2]='\0';
	strcat(buf,ip);
	strcat(buf," ");
	strcat(buf,port);
	printf("buf:%s\n",buf);

	sent = sendto(udp_sk,buf,strlen(buf)+1,0,(struct sockaddr *)&remote,sizeof(remote));
	//sent = sendto(udp_sk,MSG,strlen(MSG)+1,0,(struct sockaddr *)&remote,sizeof(remote));
	printf("sent %d\n",sent);

	bzero(buf, sizeof(buf));
	read(udp_sk,buf,BUFSIZ);
	printf("%s\n",buf);
	close(udp_sk);
}
