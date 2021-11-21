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

# include "Parser.hpp"

# define EXIT_FATAL -1

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

		int	bindSocket()
		{
			return (bind(_serverFD, (struct sockaddr *)&_saddress, sizeof(_saddress)));
		}

		int	listenSocket(int &backlog)
		{
			return (listen(_serverFD, backlog));
		}

	public:

		Server(int domain, int type, int protocol, unsigned short port, int addr)
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

		void	launchServer(int backlog)
		{

			if (bindSocket() == -1)
			{
				perror("bind");
				exit(EXIT_FATAL);
			}
			
			if (listenSocket(backlog) == -1)
			{
				perror("bind");
				exit(EXIT_FATAL);
			}

			int	size = -1;
			int curfd = -1;
			struct pollfd polf[10000];

			memset(polf, -1, sizeof(pollfd) * 10000);

			while (true)
			{
				if ((this->_acceptFD = accept(this->_serverFD, (struct sockaddr *)(&this->_saddress), &this->_slen)) == -1)
					exit(EXIT_FATAL);		
				size++;
				polf[size].fd = this->_acceptFD;
				polf[size].events = POLL_OUT;
				fcntl(polf[size].fd, F_SETFL, O_NONBLOCK);
				poll(polf, 10000, 500);
				curfd++;
				char test[10000] = {0};		
				int readval = read(polf[curfd].fd, test, 10000);
				test[readval] = 0;
				string test2(test);
				this->_parser.ParseRequest(test2);
				// TEST
				if (this->_parser.getPath() != "./")
				{
					string path = this->_parser.getPath();
					path[0] = ' ';
					std::ifstream file(this->_parser.getPath());
					string response = "HTTP/1.1 200 OK\nContent-Type: ";
					response += "text/";
					response += path.substr(path.find('.') + 1);
					response += "\n";
					std::stringstream ss;
					while (!file.eof())
					{
						string buf;
						buf = "";
						std::getline(file, buf);
						ss << buf;
						ss << endl;
					}
					response += "Content-Length: ";
					response += std::to_string(ss.str().length());
					response += "\n\n";
					response += ss.str();
					write(polf[curfd].fd, response.c_str(), response.length());
					close(polf[curfd].fd);
					polf[curfd].fd = -1;
					file.close();
				}
				cout << "------------------------------" << endl;
				cout << "Method: " << this->_parser.getMethod() << endl;
				cout << "Path: " << this->_parser.getPath() << endl;
				cout << "HTTPVER: " << this->_parser.getHttpver() << endl;
				cout << test2 << endl;
				cout << "------------------------------" << endl;
				cout << "------------------------------" << endl;

			}
		}

		~Server()
		{
			close(this->_serverFD);
		}
};

#endif