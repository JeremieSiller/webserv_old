#ifndef LEXER_HPP
# define LEXER_HPP

# include <vector>
# include <cstdarg>
# include <iostream>
# include <sstream>
# include <string>
# include <iterator>
# include <fstream>

# define DEFAULT_PATH "./conf.conf" //TO-DO
# define FILE_NOT_FOUND "Could not find config file at: "

/**
 * Lexer splits stringstream into tokens which are saved in a vector
 * takes a Token as a template and classfies the tokens depedning on the Tokens classify function
 * Can also take a path to open a file and split it into tokens.
 * Throws excecption if file is not found
**/
template<typename Token>
class Lexer {
private:
/* execptions classes */
	class FileNotFound;
private:
/* attributes */
	std::vector<Token>	_tokens;
	std::stringstream	_stream;
/* private member functions */
	void	split_tokens();
	void	validate_tokens();
public:
/* public member functions */
	Lexer(std::stringstream const &stream);
	Lexer(std::string const &_path = DEFAULT_PATH);
	~Lexer() { };
	std::vector<Token> const &getToken() const;
};

template<typename Token>
Lexer<Token>::Lexer(std::stringstream const &stream) : _tokens(), _stream()
{
	_stream << stream.rdbuf();
	split_tokens();
	validate_tokens();
}

template<typename Token>
Lexer<Token>::Lexer(std::string const &_path)
		: _tokens(), _stream()
{
	std::ifstream file(_path.c_str());
	if (!file)
		throw FileNotFound(_path);
	_stream << file.rdbuf();
	split_tokens();
	validate_tokens();
}

template<typename Token>
class Lexer<Token>::FileNotFound : public std::exception {
private:
	std::string _msg;
public:
	FileNotFound(std::string const &path) : _msg(FILE_NOT_FOUND) {
		_msg += path;
	}
	const char *what() const throw () {
		return (_msg.c_str());
	}
	#ifdef __linux__
	~FileNotFound() _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW { } // dont ask me why but compiler says I need it // (different syntax on macos :|)
	#endif
	#ifdef __APPLE__
	~FileNotFound() _NOEXCEPT {};
	#endif
};

template<typename Token>
void	Lexer<Token>::split_tokens() {
	std::string							line;
	std::stringstream					tmp;
	std::istream_iterator<std::string>	end;
	std::istream_iterator<std::string>	start;
	while (std::getline(_stream, line))
	{
		tmp << line;
		start = tmp;
		while (start != end)
		{
			Token t(*start);
			if (t.isSeperator(*start) == std::string::npos)
			{
				_tokens.push_back(*start);
				start++;
				continue ;
			}
			line = *start;
			size_t i = t.isSeperator(line);
			while (i != std::string::npos && line.length() > 0)
			{
				if (i > 0)
					_tokens.push_back(line.substr(0, i)); // push back string inbetween
				_tokens.push_back(line.substr(i, t.getSpecialLength(line))); // push back speical character
				line = line.substr(i + t.getSpecialLength(line)); // set line after special character
				i = t.isSeperator(line); // find next speical 
			}
			if (line.length() > 0)
				_tokens.push_back(line);
			start++;
		}
		tmp.clear();
		_tokens.push_back(Token("\n"));
	}
}

template<class Token>
void	Lexer<Token>::validate_tokens() {
	typename std::vector<Token>::iterator	it = _tokens.begin();
	while (it != _tokens.end())
	{
		it->classify();
		if (it->type() == Token::COMMENT)
		{
			while (it != _tokens.end() && it->content() != "\n")
			{
				it->setType(Token::COMMENT);
				it++;
			}
			continue ;
		}
		it++;
	}
}

template<typename Token>
std::vector<Token> const &Lexer<Token>::getToken() const {
		return _tokens;
};

#endif