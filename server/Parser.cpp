#include "Parser.hpp"


void	Parser::ParseRequest(string request)
{
	string buffer;

	buffer = request.substr(0, request.find('\n'));

	this->_method = -1;
	if (buffer.substr(0, buffer.find(' ')) == "GET")
		this->_method = 0;
	else if (buffer.substr(0, buffer.find(' ')) == "POST")
		this->_method = 1;
	else if (buffer.substr(0, buffer.find(' ')) == "DELETE")
		this->_method = 2;
	
	buffer = buffer.substr(buffer.find(' ') + 1);
	this->_path = ".";
	this->_path += buffer.substr(0, buffer.find(' '));

	buffer = buffer.substr(buffer.find(' ') + 1);
	this->_httpver = buffer.substr(0, buffer.find(' '));
}