#include "Token.hpp"

Token::Token(int type, std::string const &content) :
	_type(type), _content(content)
{ }

Token::~Token()
{ }

Token::Token(std::string const &content) :
	_content(content)
{ }

int	const	&Token::type() const {
	return (_type);
}

std::string const &Token::content() const {
	return (_content);
}

void	Token::setType(int const &type) {
	_type = type;
}