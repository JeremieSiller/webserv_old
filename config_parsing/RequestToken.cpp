#include "RequestToken.hpp"

const std::string Requests::RequestToken::special_tokens = ":,";

static bool	is_number(std::string const &str) {
	std::string::const_iterator s = str.begin();
	while (s != str.end())
	{
		if (!std::isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

void Requests::RequestToken::classify() {
	if (_content == ":")
		_type = Instructions::HEADER_S;
	else if (_content == ",")
		_type = Instructions::HEADER_ARGS;
	else if (_content == "\n")
		_type = Instructions::NEW_LINE;
	else
		_type = Instructions::IDENTIFYER; //--> needs to be more specific not there yet tho
}

/* returns 1 because special RequestTokens are never longer than 1 */
size_t	Requests::RequestToken::getSpecialLength(std::string const &content) const {
	for (size_t i = 0; special_tokens[i]; i++)
	{
		if (content.find(special_tokens[i]) != std::string::npos)
			return 1;
	}
	return (std::string::npos);
}

size_t	Requests::RequestToken::isSpecial(std::string const &content) const {
	for (size_t i = 0; special_tokens[i]; i++)
	{
		if (content.find(special_tokens[i]) != std::string::npos)
			return content.find(special_tokens[i]);
	}
	return (std::string::npos);
}

