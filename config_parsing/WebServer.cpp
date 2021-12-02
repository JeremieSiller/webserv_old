#include "WebServer.hpp"


WebServer::WebServer(std::string configPath) : conf(configPath)
{
	FD_ZERO(&this->_readfds);
	FD_ZERO(&this->_writefds);
}

int			WebServer::_doSelect()
{
	int	ret = select(this->_servers.size(), &this->_readfds, &this->_writefds, NULL, NULL);

	if (ret <= 0)
		return ret;
	return ret;
}

void		WebServer::_initSets()
{
	for (std::vector<n_Server::Server *>::iterator itr = this->_servers.begin(); itr != this->_servers.end(); itr++)
	{
		FD_SET((*itr)->getServerFD(), &this->_readfds);
	}
	
	for (std::vector<n_Server::HttpClient *>::iterator itr = this->_clients.begin(); itr != this->_clients.end(); itr++)
	{
		FD_SET((*itr)->getClientFD(), &this->_readfds);
	}
}

void		WebServer::run()
{


	_initServers();

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
				// itr->shutdown == tr
				std::cout << (*itr)->readRequest().str();
				if ((*itr)->shutdown())
				{
					FD_CLR((*itr)->getClientFD(), &this->_readfds);
					close((*itr)->getClientFD());
					this->_clients.erase(itr);
					// IDK COULD THROW ERROR
				}
			}
		}

		for (std::vector<n_Server::HttpClient *>::iterator itr = this->_clients.begin(); itr != this->_clients.end(); itr++)
		{
			if (FD_ISSET((*itr)->getClientFD(), &this->_writefds))
			{
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
