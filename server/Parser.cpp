#include "Parser.hpp"

void	Parser::flush()
{
	this->_path = "";
	this->_contentType = "";
	this->_method = 0;
}

void	Parser::parseRequest(string request)
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

	if (buffer.find('.') != string::npos)
	{
		this->_contentType += ": text/";
		this->_contentType += buffer.substr(buffer.find('.') + 1,buffer.find(' ') - (buffer.find('.') + 1));
	}
	else
		this->_contentType = ": text/plain";

	buffer = buffer.substr(buffer.find(' ') + 1);
	this->_httpver = buffer.substr(0, buffer.find(' '));




}