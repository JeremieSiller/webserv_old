#include "server.hpp"
#include <signal.h>

void	sig_exit(int sig)
{
	std::cout << "\rServer exited successfully" << std::endl;
	exit(0);
}

int	main(void)
{
	try
	{
		signal(SIGINT, sig_exit);
		static Server s;
		s.launch();
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << '\n';
	}
}