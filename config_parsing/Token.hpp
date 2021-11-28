#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
/*
** not sure what else we need this is a mess xD
*/
typedef enum e_types {
	UNDEFINED,
	EO_INST,
	SCOPE_BEG,
	SCOPE_END,
	IDENTIFIER,
	INTEGER,
	METHOD,
	FULLPATH,
	RELATIVEPATH,
	INSTRUCTION
} t_types;


class Token {
private:
	int					_type;
	const std::string	_content;
public:
	Token(int type, std::string const &content);
	Token(std::string const &content);
	~Token();
	int	const			&type()		const;
	std::string const	&content()	const;
	void				setType(int const &type);
};

#endif