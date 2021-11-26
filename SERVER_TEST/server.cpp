#include "server.hpp"

Server::Server() : 
	_address(), _socket(), _domain(), _type(), _protocol(0), _port(4243) {
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
	{
		std::cout << "lol\n";
		throw (ServerErr());

	}
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(_port);
	_addrlen = sizeof(_address);
	if (bind(_socket, (struct sockaddr *)&_address, sizeof(_address)) == -1)
	{
		throw (ServerErr());
	}
	if (listen(_socket, 10) == -1)
		throw (ServerErr());
}

Server::~Server() {
	std::cout << "lol\n";
	close(_socket);
	close(_new_socket);
}

void	Server::launch() {
	char	buf[30000] = {0};
	int		bytes;
	while (1)
	{
		_new_socket = accept(_socket, (struct sockaddr *)&_address, (socklen_t*)&_addrlen);
		if (_new_socket == -1)
			throw (ServerErr());
		bytes = read(_new_socket, buf, 30000);
		std::cout << buf;
		write(_new_socket, "HTTP/1.1  200 OK HELLO WORLD\n", strlen("HELLO WORLD\n"));
		close(_new_socket);
	}
}
