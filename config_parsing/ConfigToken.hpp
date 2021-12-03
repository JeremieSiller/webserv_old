#ifndef CONFIGTOKEN_HPP
# define CONFIGTOKEN_HPP

# include "AToken.hpp"
# include <cctype>


class ConfigToken : public AToken
{
public:
	typedef enum {
		CURL_SCOPE_S,
		CURL_SCOPE_E,
		SCOPE_E,
		SCOPE_S,
		COMMENT,
		NEW_LINE,
		SERVER,
		LOCATION,
		ROOT, //directory ??
		ERROR_PAGE,
		MAX_BODY_SIZE,
		METHOD,
		GET,
		POST,
		DELTE,
		INDEX, // can this differ>
		UPLOAD_ENABLE,
		ON,
		OFF,
		LISTEN,
		CGI_EXTENSION,
		CGI_PATH,
		SERVER_NAME,
		AUTO_INDEX,
		DOUBLE_DOT,
		EOF_INSTRUCT,
		IP_ADDRESS,
		INTEGER,
		DIRECTORY,
		PATH,
		STRING
	} instrutions;
private:
	static const std::string	special_toekens;
public:
	size_t						getPos() const;
	static const std::string	identity[];
	ConfigToken(std::string const &content) : AToken(content) { }
	void			classify();
	size_t			isSeperator(std::string const &content) const;
	size_t			getSpecialLength(std::string const &content) const;
	bool			isAllowed_toFollow(AToken const &in) const;
	bool			isAllowed_toPreceed(AToken const &in) const;
	void			setType(instrutions const &val);
};

#endif