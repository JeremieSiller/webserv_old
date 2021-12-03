#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <sstream>
# include <stdlib.h>
# include <unistd.h>
# include <cstring>
# include <fcntl.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdio.h>

namespace n_Server
{
	# define DEFAULT_BACKLOG -1
	# define READ_BUFFER_SIZE 4096


	typedef enum {
		SUCCES,
		ERROR_ACCEPT = 1,
		ERROR_SOCKET,
		ERROR_BIND,
		ERROR_LISTEN,



		
	} Returns;



	class HttpClient
	{

		private:

			int						_clientFD;
			std::stringstream		_readClient;
			bool					_shutdown;

		public:

		int							getClientFD();
		
		bool						shutdown();

		// READS FROM CLIENT SOCKET AND RETURNS IT IN A STRINGSTREAM
		std::stringstream &	readRequest();

		//Creates new HTTPCLIENT SHIT
		HttpClient(int const &);

		~HttpClient()
		{
			close(this->_clientFD);
		}

	};


	class Server
	{
		private:

			struct sockaddr_in		_saddress;
			socklen_t				_slen;
			int						_serverFD;

		public:

			Server(){}

			Server(int, int, int, unsigned short, std::string);

			// Initializes server: set serversocket, bind, listen
			int		init(int, int, int, unsigned short, std::string);

			// Returns Listener SOCKET 
			int		getServerFD();

			// Accepts new clnt and returns SOCKET
			HttpClient		*newAccept();

			~Server()
			{
				close(this->_serverFD);
			}

	};



}



#endif