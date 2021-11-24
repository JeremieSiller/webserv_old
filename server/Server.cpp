#include "Server.hpp"

Server::Server(int domain, int type, int protocol, unsigned short port, int addr)
{
	if ((this->_serverFD = socket(domain, type, protocol)) == 0)
	{
		perror("socket fail");
		exit(EXIT_FATAL);
	}
	memset(&_saddress, 0, sizeof(_saddress));
	this->_saddress.sin_family = domain;
	this->_saddress.sin_port = htons(port);
	this->_saddress.sin_addr.s_addr = htonl(addr);
}


int	Server::bindSocket()
{
	return (bind(this->_serverFD, (struct sockaddr *)&this->_saddress, sizeof(this->_saddress)));
}

int	Server::listenSocket(int &backlog)
{	
	return (listen(this->_serverFD, backlog));
}

void	Server::setResponse()
{
	this->_response.str("");
	if (this->_parser.getPath() == "./flavicon.ico")
	{
		this->_response << " 200 OK " << endl << endl;
	}
	else if (this->_parser.getMethod() == 0) // GET
	{
		std::stringstream	messageBuf;
		std::ifstream		fileStream(this->_parser.getPath());
		
		if (!fileStream.is_open())
		{
			this->_response << this->_parser.getHttpver() << " 404 ERROR " << endl << endl;
			return ;
		}

		while (!fileStream.eof())
		{
			std::string	filebuf;
			std::getline(fileStream, filebuf);
			messageBuf << filebuf << endl;
		}
		std::cout << this->_parser.getHttpver();
		this->_response << this->_parser.getHttpver();
		this->_response << " 200 OK " ; // RESPONSE TYPE /https://developer.mozilla.org/en-US/docs/Web/HTTP/Status

		this->_response << endl;
		// BODY HEADERSA

		this->_response << "Content-Type" << this->_parser.getContentType() << endl;
		this->_response << "Content-Length: " << messageBuf.str().length();
		this->_response << endl << endl;
		this->_response << messageBuf.str();
	}

}

int	Server::acceptLoop()
{
	struct pollfd	fds[1];
	int				pollret;

	while (true)
	{
		if ((this->_acceptFD = accept(this->_serverFD, (struct sockaddr *)(&this->_saddress), &this->_slen)) == -1)
			return (-1);
		fds[0].fd = this->_acceptFD;
		fds[0].events = 0;
		fds[0].events |= POLL_IN;
		fds[0].events |= POLL_OUT;
		fcntl(this->_acceptFD, F_SETFL, O_NONBLOCK);
		pollret = poll(fds, 1, 5000);
		if (pollret == 0)
		{
			write(1, "timeout",7);
		}
		else
		{
			char request[10000] = {0};
			int readval = recv(this->_acceptFD, request, 10000, 0);
			
			this->_parser.parseRequest(request);

			setResponse();

			// Write Response to socket;
			write(this->_acceptFD, this->_response.str().c_str(), this->_response.str().length());
			cout << this->_response.str();
			cout << "------------------------------" << endl;
			cout << "------------------------------" << endl;
			close(this->_acceptFD);
		}
	}
}

void	Server::launchServer(int backlog)
{
	if (bindSocket() == -1)
	{
		perror("bind");
		exit(EXIT_FATAL);
	}
	if (listenSocket(backlog) == -1)
	{
		perror("listen");
		exit(EXIT_FATAL);
	}
	acceptLoop();
}