#ifndef REQUESTTOKEN_HPP
# define REQUESTTOKEN_HPP

#include "AToken.hpp"

namespace Requests
{

	typedef enum {
		
		NEW_LINE,
		HEADER_S,
		HEADER_ARGS,
		IDENTIFYER

	} Instructions;


	class RequestToken : public AToken
	{
	private:
		static const std::string special_tokens;
	public:
		RequestToken(std::string const &content) : AToken(content) { }
		virtual void			classify();
		virtual size_t			isSpecial(std::string const &content) const;
		virtual size_t			getSpecialLength(std::string const &content) const;
	};

}




#endif