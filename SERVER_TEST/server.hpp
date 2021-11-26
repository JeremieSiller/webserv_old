#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <sys/socket.h>
# include <exception>
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
# include <cstdlib>
# include <cstring>
# include <sys/errno.h>


class Server {
private:
	class ServerErr : public std::exception {
	private:
		std::string _msg;
	public:
		ServerErr() : _msg(std::strerror(errno)) { };
		ServerErr(std::string const &msg) : _msg(msg) { 
			_msg += std::strerror(errno);
		};
		virtual ~ServerErr() _NOEXCEPT { }
		virtual const char * what() const throw() {
			return (_msg.c_str());
		}
	};
private:
	struct sockaddr_in	_address;
	int					_socket;
	int					_domain;
	int					_type;
	int					_protocol;
	int					_port;
	int					_new_socket;
	int					_addrlen;
public:
	Server();
	~Server();
	void				launch();
};

#endif