#include "Lexer.hpp"

int	main(void)
{
	Lexer l("./test_conf.conf");

	std::vector<Token>::const_iterator begin = l.getToken().begin();
	std::vector<Token>::const_iterator end = l.getToken().end();
	while (begin != end)
	{
		std::cout << "|" << begin->content() << "|" << std::endl;
		begin++;
	}
}