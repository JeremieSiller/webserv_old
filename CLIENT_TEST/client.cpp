#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <string>
#include <iostream>

#define PORT 80

#define MAXLINE 4096
#define SA struct sockaddr

void	err_n_die(std::string const &str)
{
	std::cerr << str << std::endl;
	exit(1);
}


int	main(int argc, char **argv)
{
	int						sockfd, n;
	int						send_bytes;
	struct sockaddr_in		servaddr;
	char					sendline[MAXLINE];
	char					recvline[MAXLINE];
	if (argc != 2)
		err_n_die("usage: <server adress>");
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_n_die("could not create socket");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_n_die("inet_pton didnt work");
	
	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		err_n_die("connect failed!");
	strcpy(sendline, "GET / HTTP/1.1\r\n\r\n");
	send_bytes = strlen(sendline);
	if (write(sockfd, sendline, send_bytes) != send_bytes)
		err_n_die("write error");
	bzero(recvline, MAXLINE);
	while ((n = read(sockfd, recvline, MAXLINE-1)) > 0)
	{
		printf("%s", recvline);
		bzero(recvline, MAXLINE);
	}
	if (n < 0)
		err_n_die("read error");
	exit(0);
}