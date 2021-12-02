#ifndef CONFIGTOKEN_HPP
# define CONFIGTOKEN_HPP

# include "AToken.hpp"
# include <cctype>

typedef enum {
	IDENTIFYER,
	CURL_SCOPE_S,
	CURL_SCOPE_E,
	NOR_SCOPE_S,
	NOR_SCOPE_E,
	EO_INSTRUCTION,
	NUMBER,
	COMMENT_START,
	NEW_LINE
} instrutions;

class ConfigToken : public AToken
{
private:
	static const std::string special_toekens;
public:
	ConfigToken(std::string const &content) : AToken(content) { }
	void			classify();
	size_t			isSeperator(std::string const &content) const;
	size_t			getSpecialLength(std::string const &content) const;
};

#endif