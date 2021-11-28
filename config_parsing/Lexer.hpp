#ifndef LEXER_HPP
# define LEXER_HPP

# include <vector>
# include <cstdarg>
# include <iostream>
# include <sstream>
# include <string>
# include <iterator>
# include <fstream>
# include "Token.hpp"

# define DEFAULT_PATH "./conf.conf"
# define WHITE
# define FILE_NOT_FOUND "Could not find config file at: "

class Lexer {
private:
/* execptions classes */
	class FileNotFound : public std::exception {
	private:
		std::string _msg;
	public:
		FileNotFound(std::string const &path) : _msg(FILE_NOT_FOUND) {
			_msg += path;
		}
		const char *what() const throw () {
			return (_msg.c_str());
		}
		virtual ~FileNotFound() _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW { }; // dont ask me why but compiler says I need it // (different syntax on macos :|)
	};
private:
/* attributes */
	std::vector<Token>	_tokens;
	std::string	const	&_path;
	std::ifstream		_file;
/* private member functions */
	void	split_tokens();
	void	validate_tokens();
public:
/* public member functions */
	Lexer(std::string const &path = DEFAULT_PATH);
	~Lexer();
	std::vector<Token> const &getToken() const;
};

#endif