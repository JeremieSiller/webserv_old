#include "server.hpp"

Server::Server() : 
	_address(), _socket(), _domain(), _type(), _protocol(0), _port(80) {
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
	{
		throw (ServerErr("socket: "));
	}
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(_port);
	_addrlen = sizeof(_address);
	if (bind(_socket, (struct sockaddr *)&_address, sizeof(_address)) == -1)
	{
		throw (ServerErr("bind: "));
	}
	if (listen(_socket, 10) == -1)
		throw (ServerErr("listen: "));
}

Server::~Server() {
	close(_socket);
	close(_new_socket);
}

void	Server::launch() {
	char	buf[30000] = {0};
	int		bytes;
	fd_set	current_sockets, ready_sockets;
	FD_ZERO(&current_sockets);
	FD_SET(_socket, &current_sockets);
	while (1)
	{
		ready_sockets = current_sockets;
		if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0)
			throw(ServerErr("select"));
		for (int i = 0; i < FD_SETSIZE; i++) {
			if (FD_ISSET(i, &ready_sockets)) {
				if (i == _socket) {
					_new_socket = accept(_socket, (struct sockaddr *)&_address, (socklen_t*)&_addrlen);
					if (_new_socket < 0)
						throw(ServerErr("accept"));
					FD_SET(_new_socket, &current_sockets);
				}
				else
				{
					bytes = read(_new_socket, buf, 30000);
					std::cout << buf;
					write(_new_socket, "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 11\n\nHello world", strlen("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 11\n\nHello world"));
					close(_new_socket);
					FD_CLR(i, &current_sockets);
				}
			}
		}
	}
}
