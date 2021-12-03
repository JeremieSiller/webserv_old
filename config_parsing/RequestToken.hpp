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
		void			classify();
		size_t			isSeperator(std::string const &content) const;
		size_t			getSpecialLength(std::string const &content) const;
		bool			isAllowed_toFollow(AToken const &in) const { return true; }
		bool			isAllowed_toPreceed(AToken const &in) const { return true; }
	};

}




#endif