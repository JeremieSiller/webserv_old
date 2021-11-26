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
class ServerErr : public std::exception {
public:
	virtual const char * what() const throw() {
		return (std::strerror(errno));
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