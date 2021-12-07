#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

#include "Lexer.hpp"
#include "ConfigToken.hpp"
#include "RequestToken.hpp"
#include "Server.hpp"
#include <sys/select.h>
#include <iostream>
#include <vector>

class WebServer
{
	private:

		Lexer<ConfigToken>	conf;

		std::vector<n_Server::Server*> _servers;
		std::vector<n_Server::HttpClient*> _clients;

		fd_set		_readfds;
		fd_set		_writefds;

		int			_maxfds;

		void	_initServers();

		void	_initSets();

		void	_cleanUP();

		int		_doSelect();

		void	_checkSelect();

	public:

		WebServer(std::string configPath);

		void	run();

};

#endif