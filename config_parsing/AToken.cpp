#include "AToken.hpp"

AToken::AToken(int type, std::string const &content) :
	_type(type), _content(content)
{ }

AToken::~AToken()
{ }

AToken::AToken(std::string const &content) :
	_type() , _content(content)
{ }

int	const	&AToken::type() const {
	return (_type);
}

std::string const &AToken::content() const {
	return (_content);
}
