#include "Lexer.hpp"

Lexer::Lexer(std::string const &path) :
	_tokens(), _path(path), _file(path.c_str())
{
	if (!_file)
		throw  Lexer::FileNotFound(_path);
	split_tokens();
}

Lexer::~Lexer() { }

std::vector<Token>	const &Lexer::getToken() const {
	return _tokens;
}


void	Lexer::split_tokens() {
	std::stringstream	stream;

	stream << _file.rdbuf();
	_file.close();
	std::copy(std::istream_iterator<std::string>(stream), 
			std::istream_iterator<std::string>(),
			std::back_inserter(_tokens));
}

void	Lexer::validate_tokens() {
	return ;
	// not sure what to do here
}