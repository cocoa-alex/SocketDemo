#include "../unp/unp.h"
#include "../unp/apueerror.h"

int main(int argc, char **argv)
{
	int sockfd,n;
	char recvline[MAXLINE+1];
	struct sockaddr_in servaddr;

	printf("%s\n",argv[1] );
	if (argc!=1)
	{
		/* code */
		err_quit("usage:a.out <IPaddress>");
	}

	if ((sockfd=socket(AF_INET, SOCK_STREAM, 0))<0)
	{
		/* code */
		err_sys("socket error");
	}

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(13);

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<=0)
	{
		/* code */
		err_quit("inet_pton error for %s",argv[1]);
	}

	if (connect(sockfd,(SA *)&servaddr, sizeof(servaddr))<0)
	{
		/* code */
		err_sys("connect error");
	}

	while((n=read(sockfd,recvline,MAXLINE))>0)
	{
		recvline[n]=0;
		if(fputs(recvline, stdout)==EOF)
		{
			err_sys("fputs error");
		}
	}

	if (n<0)
	{
		/* code */
		err_sys("read error");
	}

	exit(0);
}