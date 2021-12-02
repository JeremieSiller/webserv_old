#include "Server.hpp"


using namespace n_Server;

Server::Server(int domain, int type, int protocol, unsigned short port, std::string addr)
{
	int error;

	if ((error = init(domain, type, protocol, port, addr)) > 0)
	{
		perror("Server Creation");
		exit(error);
	}
}

int		Server::getServerFD()
{
	return (this->_serverFD);
}

int		Server::init(int domain, int type, int protocol, unsigned short port, std::string addr)
{

	if ((this->_serverFD = socket(domain, type, protocol)) == 0)
		return ERROR_SOCKET;

	std::memset(&this->_saddress, 0, sizeof(this->_saddress));
	this->_saddress.sin_family = domain;
	this->_saddress.sin_port = htons(port);
	//this->_saddress.sin_addr.s_addr = htonl(inet_addr(addr.c_str()));
	this->_saddress.sin_addr.s_addr = inet_addr(addr.c_str());

	if (bind(this->_serverFD, (struct sockaddr *)&this->_saddress, sizeof(this->_saddress)) == -1)
		return ERROR_BIND;

	if (listen(this->_serverFD, DEFAULT_BACKLOG) == -1)
		return ERROR_LISTEN;
	return SUCCES;
}

HttpClient		*Server::newAccept()
{
	int	clientFD;

	clientFD = accept(this->_serverFD, (struct sockaddr *)&this->_saddress, &this->_slen);

	if (clientFD == -1)
		NULL;

	return new HttpClient(clientFD);
}

HttpClient::HttpClient(int const &fd)
{
	fcntl(this->_clientFD, F_SETFL, O_NONBLOCK);
	this->_clientFD = fd;
	this->_shutdown = false;
}

int		HttpClient::getClientFD()
{
	return (this->_clientFD);
}

std::stringstream  &	HttpClient::readRequest()
{
	char				buffer[READ_BUFFER_SIZE];

	this->_readClient.str() = std::string("");
	int	count = recv(this->_clientFD, buffer, READ_BUFFER_SIZE, 0);
	if (count <= 0)
		this->_shutdown = true;
	this->_readClient << buffer;
	return (this->_readClient);
}

bool					HttpClient::shutdown()
{
	return (this->_shutdown);
}