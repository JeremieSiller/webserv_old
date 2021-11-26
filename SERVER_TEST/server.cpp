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

#define PORT 8001
#define MAXLINE 4096

void	err_n_die(std::string const &str)
{
	std::cerr << str << std::endl;
	perror("lol");
	exit(1);
}
int	socket_fd = 0;
struct sockaddr_in addr =  (struct sockaddr_in){  };
int	listening = 0;
int	client_socket = 0;

void	exit_and_unlink(int signal)
{
	exit(0);
	(void)signal;
}

int	main(int argc, char **argv)
{
	signal(SIGINT, &exit_and_unlink);
	if ( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		err_n_die("could not create socket");
	
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(socket_fd, (struct sockaddr *) &addr, sizeof(addr)) == -1)
		err_n_die("bind didnt work");

	if ( (listening = listen(socket_fd, MAXLINE)) == -1)
		err_n_die("listen didnt work");
	char str[MAXLINE + 1];
		bzero(str, MAXLINE + 1);
	while (1) {
		client_socket = accept(socket_fd, NULL, NULL);
		while (read(client_socket, str, MAXLINE) > 0)
		{
			std::cerr << str;
			if (strchr(str, '\n'))
				break;
			bzero(str, MAXLINE + 1);
		}
		send(client_socket, "HTTP/1.1 200 ok\r\n\nwtf hell", strlen("HTTP/1.1 200 ok\r\n\nwtf hell"), 0);
		close(client_socket);
	}
	(void)argc;
	(void)argv;
}