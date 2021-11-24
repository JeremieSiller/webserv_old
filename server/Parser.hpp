#ifndef PARSER_HPP
# define PARSER_HPP

# include <string>
# include <iostream>

using std::cout;
using std::endl;
using std::string;

class Parser
{
	private:
		// REQUESTLINE
		int			_method;
		string		_path;
		string		_query; // preceded by ?
		/* additionally there is a scheme and host components somewhere idk*/
		string		_httpver;


		string		_contentType;

		//	HTTP HEADERS
		/* A lot of headers idk*/

		//	MSG BODY
		string		_body;	

	public:
		Parser() : _method(0), _path(""), _query(""), _httpver(""){}

		void	parseRequest(string request);

		int		getMethod() { return this->_method; }
		string	getPath() { return this->_path; }
		string	getHttpver() { return this->_httpver; }
		string	getContentType() { return this->_contentType; }
};

#endif