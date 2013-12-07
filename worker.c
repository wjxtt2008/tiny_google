// worker.c

// gcc -o worker worker.c -lpthread


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

//pthread
#include <pthread.h>

#define BUFFSIZ 1024

void *thr_fn(void *arg){
	int rsk = *((int *) arg);
	char buf[BUFFSIZ];
	char buf1[BUFFSIZ];
	pthread_t tid = pthread_self();

	while(recv(rsk,buf,BUFFSIZ, 0)>0)
	{
		printf("receive %lu : %s \n", (unsigned long) tid, buf);

		
		system(buf);// call script


		buf1[0] = 'e';
		buf1[1] = 'n';
		buf1[2] = 'd';
		buf1[3] = '\0';
		send(rsk, buf1, strlen(buf1)+1, 0);
		printf("send %lu : %s \n", (unsigned long) tid, buf1);
	}

	printf("Connection Closed: %lu \n", (unsigned long) tid);
	close(rsk);
}



main()
{
	struct sockaddr_in local;
	int sk, len=sizeof(local);

	/* Create an internet domain stream socket */
	sk=socket(AF_INET,SOCK_STREAM,0);

	/*Construct and bind the name using default values*/
	local.sin_family=AF_INET;
	local.sin_addr.s_addr=INADDR_ANY;
	local.sin_port=0;
	bind(sk,(struct sockaddr *)&local,sizeof(local));

	/*Find out and publish socket name */
	getsockname(sk,(struct sockaddr *)&local,&len);
	printf("Socket has port %d\n",local.sin_port);

	/* Start accepting connections */
	/*Declare willingness to accept a connection*/
	listen(sk,10); 
	while(1){
		pthread_t ntid;
		int rsk = accept(sk,0,0);/*Accept new request for a connection*/
		// create a thread for this connection
		pthread_create(&ntid, NULL, thr_fn, (void *) &rsk);// possible segmentation failure
		printf("Connection established using thread : %lu \n",(unsigned long) ntid);
	}
}

