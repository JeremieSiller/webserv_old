#ifndef ATOKEN_HPP
# define ATOKEN_HPP

# include <string>

class AToken {
protected:
	int					_type;
	const std::string	_content;
public:
	AToken(int type, std::string const &content);
	AToken(std::string const &content);
	virtual ~AToken();
	int	const			&type()		const;
	std::string const	&content()	const;
	/* should return the index of a special token (e.g. '{' or ';') that need to be handled as one token even if
		there are characters next to the */ 
	virtual size_t		isSpecial(std::string const &content) const = 0;
	/* should return the length of the first special token found in content */
	virtual size_t		getSpecialLength(std::string const &content) const = 0;
	/* classifies the token */ 
	virtual void		classify() = 0;
};

#endif