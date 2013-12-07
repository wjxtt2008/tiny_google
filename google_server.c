// gcc -o dispatcher dispatcher.c 


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>

#define BUFFSIZ 1024

main(argc,argv)
int argc;
char *argv[];
{ 
	char buf[BUFFSIZ];
	char buf1[BUFFSIZ];
	struct sockaddr_in remote;
	int sk;
	int i;
	struct hostent *hp,*gethostbyname();

	sk=socket(AF_INET,SOCK_STREAM,0);

	remote.sin_family=AF_INET;
	hp=gethostbyname(argv[1]);
	bcopy(hp->h_addr,(char*)&remote.sin_addr,hp->h_length);
	remote.sin_port=atoi(argv[2]);

	connect(sk,(struct sockaddr *)&remote,sizeof(remote));

	/*Read input from stdin an send it to the server*/
	for (i = 0; i < BUFFSIZ; i++)
		buf[i] = '\0';
	printf("Type the first message to be echoed\n");

	while(read(0,buf,BUFFSIZ)>1)
	{
		send(sk,buf,strlen(buf)+1, 0);
		for (i = 0; i < BUFFSIZ; i++)
			buf[i] = '\0';
		
		int l;

		if((l = recv(sk, buf1, BUFFSIZ, 0)) > 0)
			printf("receive:%s:\n", buf1);
		else
			printf("receive 0 length");
		for (i = 0; i < BUFFSIZ; i++)
			buf1[i] = '\0';
		printf("Type the next message to be echoed\n");
	}
	
	close(sk);
}
