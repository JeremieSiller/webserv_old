#include "Server.hpp"
#include <signal.h>

void	sig_exit(int sig)
{
	std::cout << "\nServer exited successfully" << std::endl;
	exit(0);
	(void)sig;
}

int main()
{
	signal(SIGINT, sig_exit);
	static Server net(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);

	net.launchServer(10);

	return 0;
}
