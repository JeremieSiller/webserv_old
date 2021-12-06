#include "WebServer.hpp"


WebServer::WebServer(std::string configPath) : conf(configPath)
{
	FD_ZERO(&this->_readfds);
	FD_ZERO(&this->_writefds);
}

int			WebServer::_doSelect()
{

	struct timeval tv;

	tv.tv_sec = 5;
	tv.tv_usec = 0;	


	int	ret = select(this->_maxfds + 1, &this->_readfds, &this->_writefds, NULL, &tv);
	
	if (ret <= 0)
		return ret;
	return ret;
}

void		WebServer::_initSets()
{
	FD_ZERO(&this->_readfds);
	FD_ZERO(&this->_writefds);
	this->_maxfds = 0;
	for (std::vector<n_Server::Server *>::iterator itr = this->_servers.begin(); itr != this->_servers.end(); itr++)
	{
		FD_SET((*itr)->getServerFD(), &this->_readfds);
		if ((*itr)->getServerFD() > this->_maxfds)
			this->_maxfds = (*itr)->getServerFD();
	}
	
	for (std::vector<n_Server::HttpClient *>::iterator itr = this->_clients.begin(); itr != this->_clients.end(); itr++)
	{
		if ((*itr)->getClientMode() == n_Server::READING)
			FD_SET((*itr)->getClientFD(), &this->_readfds);
		else if ((*itr)->getClientMode() == n_Server::WRITING)
			FD_SET((*itr)->getClientFD(), &this->_writefds);
		if ((*itr)->getClientFD() > this->_maxfds)
			this->_maxfds = (*itr)->getClientFD();
	}
}

void		WebServer::run()
{


	_initServers();

	for (int i =0; i < this->_servers.size(); i++)
	{
		std::cout << this->_servers[i]->getServerFD() << std::endl;
	}

	while (true)
	{

		_initSets();

		_doSelect();

		for (std::vector<n_Server::Server *>::iterator itr = this->_servers.begin(); itr != this->_servers.end(); itr++)
		{
			if (FD_ISSET((*itr)->getServerFD(), &this->_readfds))
			{
				n_Server::HttpClient *newFD = (*itr)->newAccept();
				if (newFD == NULL)
					continue;
				this->_clients.push_back(newFD);
			}
		}

		for (std::vector<n_Server::HttpClient *>::iterator itr = this->_clients.begin(); itr != this->_clients.end(); itr++)
		{
			if (FD_ISSET((*itr)->getClientFD(), &this->_readfds))
			{
				// CALL TO itr->readRequest(), returns stringstream Handle and save request somewhere i guess
				// itr->getClientMode == tr
				std::cout << (*itr)->readRequest().str();
				if (!(*itr)->getClientMode())
				{
					FD_CLR((*itr)->getClientFD(), &this->_readfds);
					close((*itr)->getClientFD());

					this->_clients.erase(itr);
					itr--;
					// IDK COULD THROW ERROR
				}
			}
			else if (FD_ISSET((*itr)->getClientFD(), &this->_writefds))
			{

				write((*itr)->getClientFD(), "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 11\n\nHello world", strlen("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 11\n\nHello world"));
				(*itr)->setClientMode(n_Server::READING);
				// CALL TO itr->readRequest(), returns stringstream Handle and save request somewhere i guess
				// respond to clients here
				
			}
		}
	}
}

void	WebServer::_initServers()
{
	this->_servers.push_back(new n_Server::Server(AF_INET, SOCK_STREAM, 0, 80, "168.119.226.83"));
}

void	_cleanUP()
{





}
