#include "ConfigToken.hpp"

const std::string ConfigToken::special_toekens = "#;{(})";

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

void ConfigToken::classify() {
	if (_content == "{")
		_type = CURL_SCOPE_S;
	else if (_content == "}")
		_type = CURL_SCOPE_E;
	else if (_content == "(")
		_type = NOR_SCOPE_S;
	else if (_content == ")")
		_type = NOR_SCOPE_E;
	else if (_content == ";")
		_type = EO_INSTRUCTION;
	else if (is_number(_content))
		_type = NUMBER;
	else if (_content == "#")
		_type = COMMENT_START;
	else if (_content == "\n")
		_type = NEW_LINE;
	else
		_type = IDENTIFYER; //--> needs to be more specific not there yet tho
}

/* returns 1 because special ConfigTokens are never longer than 1 */
size_t	ConfigToken::getSpecialLength(std::string const &content) const {
	for (size_t i = 0; special_toekens[i]; i++)
	{
		if (content.find(special_toekens[i]) != std::string::npos)
			return 1;
	}
	return (std::string::npos);
}

size_t	ConfigToken::isSpecial(std::string const &content) const {
	for (size_t i = 0; special_toekens[i]; i++)
	{
		if (content.find(special_toekens[i]) != std::string::npos)
			return content.find(special_toekens[i]);
	}
	return (std::string::npos);
}
