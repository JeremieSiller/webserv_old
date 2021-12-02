#include "Lexer.hpp"
#include "ConfigToken.hpp"
#include "RequestToken.hpp"

int	main(void)
{
	try
	{
		Lexer<ConfigToken> l("test_conf.conf");
		std::vector<ConfigToken>::const_iterator begin = l.getToken().begin();
		std::vector<ConfigToken>::const_iterator end = l.getToken().end();
		while (begin != end)
		{
			std::cout << "|";
			if (begin->content() != "\n")
				std::cout << begin->content();
			else
				std::cout << "\\n";
			std::cout << "| "; 
			if (begin->type() == IP_ADDRESS)
				std::cout << "IP" << std::endl;
			else if (begin->type() == INTEGER)
				std::cout << "int" << std::endl;
			else if (begin->type() == DIRECTORY)
				std::cout << "dir" << std::endl;
			else if (begin->type() == STRING)
				std::cout << "str" << std::endl;
			else if (begin->type() == NEW_LINE)
				std::cout << "\\n" << std::endl;
			else if (begin->type() == PATH)
				std::cout << "path" << std::endl;
			else
				std::cout << begin->identity[begin->type()] << std::endl;
			begin++;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
}