#include "Lexer.hpp"
#include "ConfigToken.hpp"

int	main(void)
{
	try
	{
			std::ifstream file("./test_conf.conf");
		std::stringstream stream;
		stream << file.rdbuf();
		Lexer<ConfigToken> l(stream);
		std::vector<ConfigToken>::const_iterator begin = l.getToken().begin();
		std::vector<ConfigToken>::const_iterator end = l.getToken().end();
		while (begin != end)
		{
			std::cout << "|";
			if (begin->content() != "\n")
				std::cout << begin->content();
			else
				std::cout << "\\n";
			std::cout << "|" << std::endl;
			begin++;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
}