#ifndef HTTPPRESPONSE_H
# define HTTPPRESPONSE_H

#include "HTTP.h"
#include "HTTPRequest.hpp"
#include <sstream>
#include <cstdio>
# include <string>
#include <dirent.h>


class HTTPResponse
{
private:
	enum status_code_value status_code;
	HTTPRequest &_request;
	std::string status_line;
	std::string response_headers;
	std::string content;
	void	_set_content(std::string filePath);
public:
	HTTPResponse(HTTPRequest &request, std::string filePath);
	~HTTPResponse();
	std::string response;
	void	get();
	std::string getDefaultErrorPageContent(enum status_code_value statusCode);
	std::string getDirectoryListing(std::string filePath);
	void urlEncode(std::string &url);
};

#endif
