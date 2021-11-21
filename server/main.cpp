#include "Server.hpp"


int main()
{
	Server net(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);

	net.launchServer(2);

	return 0;
}