#ifndef NETWORK_HPP 
# define NETWORK_HPP 

# include <sys/socket.h>
# include <fstream>
# include <sstream>
# include <netinet/in.h>
# include <unistd.h>
# include <stdlib.h>
# include <string>
# include <fcntl.h>
# include <iostream>
# include <poll.h>
# include <string.h>
# include <sstream>

# include "Parser.hpp"

# define EXIT_FATAL -1

#ifndef POLL_IN
# define POLL_IN 1
#endif

#ifndef POLL_OUT
# define POLL_OUT 1
#endif

using std::string;
using std::cout;
using std::endl;


class Server
{
	private:
		struct sockaddr_in		_saddress;
		socklen_t				_slen;
		int						_serverFD;
		int						_acceptFD;
		Parser					_parser;

		std::stringstream		_response;


		int	bindSocket();
		int	listenSocket(int &backlog);
		int	acceptLoop();

		void	setResponse();

	public:

		Server(int domain, int type, int protocol, unsigned short port, int addr);

		void	launchServer(int backlog);

		~Server()
		{
			close(this->_serverFD);
		}
};

#endif
