#include "includes/HTTPResponse.hpp"

HTTPResponse::HTTPResponse(HTTPRequest &request, std::string filePath) : _request(request)
{
	status_code = _request.get_status_code();
	if (!status_code)
		status_code = ok;
	status_line.append(_request.get_protocol_v());
	status_line.append(" ");
	std::ostringstream stat_code_str;
	stat_code_str << status_code;
	status_line.append(stat_code_str.str());
	status_line.append(" ");
	status_line.append(getStatusCodeMsg(status_code));
	status_line.append("\r\n");
	response.append(status_line);

	if (_request.getRequestType() == REDIRECT_REQUEST)
	{
		response_headers.append("Location: ");
		response_headers.append(filePath);
		response_headers.append("\r\n");
		response_headers.append("Content-Type: text/plain; charset=utf-8\r\n");
		response.append(response_headers);
		return ;
	}

	if (_request.headers.find("Connection") == _request.headers.end())
		response_headers.append("Connection: keep-alive\r\n");
	else
	{
		response_headers.append("Connection: ");
		response_headers.append(_request.headers["Connection"]);
		response_headers.append("\r\n");
	}
	response_headers.append("Content-Type: ");

	std::string fileExtention = getUriExtention(filePath);
	if (request.getRequestType() == GET_DIR_LIST)
		fileExtention.replace(fileExtention.begin(), fileExtention.end(), "html");
	//  fileExtention = getUriExtention(filePath);
	// std::cout << "fileExtention " << fileExtention << " filePath " << filePath.empty() << " getContentTypeFromDictionary " <<_request.dictionary.getContentTypeFromDictionary(fileExtention) << " " <<_request.dictionary.getContentTypeFromDictionary("html") << std::endl;
	response_headers.append(_request.dictionary.getContentTypeFromDictionary(fileExtention));
	response_headers.append("\r\n");
	// if ()
	if (request.getRequestType() == GET_DIR_LIST)
		content.append(getDirectoryListing(filePath));
	else
		_set_content(filePath);
	response.append(response_headers);
	response.append("Content-Length: ");
	std::ostringstream cont_l;
	cont_l << content.size();
	response.append(cont_l.str());
	response.append("\r\n");
	response.append("\r\n");
	response.append(content);

	// if (request.get_method().compare("GET"))
	// 	get();
}

HTTPResponse::~HTTPResponse()
{
}

void HTTPResponse::get()
{
}

void HTTPResponse::_set_content(std::string filePath)
{
	if (filePath.empty())
	{
		content.clear();
		content.append(getDefaultErrorPageContent(_request.get_status_code()));
		return ;
	}
	FILE *fileToRead = std::fopen(filePath.c_str(), "r");
	if (fileToRead == NULL)
	{
		std::cerr << "file open error\n";
		content.clear();
		content.append(getDefaultErrorPageContent(_request.get_status_code()));
		// std::fclose(fileToRead);
		return ;

	}
	int c;
	while ((c = std::fgetc(fileToRead)) != EOF)
	{
		char ch = c;
		std::stringstream ss;
		ss << ch;
		content += ss.str();
	}

	// Close the file
	std::fclose(fileToRead);
	std::cout << "\n\n"; // Add spacing between files
}

std::string HTTPResponse::getDefaultErrorPageContent(enum status_code_value statusCode)
{
	std::string content;
	content.append("<!DOCTYPE html>");
	content.append("<head>");
	content.append("</head>");
	content.append("<div id=\"main\" style=\"display: table; width: 100%; height: 100vh; text-align: center; \">\r\n");
    content.append("	<div class=\"fof\" style=\"display: table-cell; vertical-align: middle; \"\r\n>");
	content.append("   		<h1 style=\"font-size: 50px; display: inline-block; padding-right: 12px; animation: type .5s alternate infinite; \">Error ");
	std::ostringstream stat_code_str;
		stat_code_str << statusCode;
	content.append(stat_code_str.str());
	content.append("</h1>\r\n");
    content.append("	</div>\r\n");
	content.append("</div>");
	return (content);
}

std::string HTTPResponse::getDirectoryListing(std::string filePath)
{
	std::string content;
	content.append("<!DOCTYPE html>");
	content.append("<head>");
	content.append("</head>");
	DIR *dir;
	struct dirent *ent;
	std::string relativePath = ".";
	relativePath.append(filePath);
	if ((dir = opendir (relativePath.c_str())) != NULL) {
  	/* print all the files and directories within directory */
		content.append("<h1> List of directory files: </h1>\r\n");
		content.append("<div style=\"display: table; width: 100%; text-align: left; margin-left:10px \">\r\n");
		while ((ent = readdir(dir)) != NULL)
		{
		    content.append("	<div class=\"fof\" style=\"display: table-row; height: 25px; vertical-align: middle; \"\r\n>");
			content.append("<a href=\"");
			content.append(ent->d_name);
			content.append("\">\r\n");
			content.append(ent->d_name);
			// printf ("%s\n", ent->d_name);
			content.append("</a>\r\n");
			content.append("</div>\r\n");

		}
		content.append("</div>\r\n");
		closedir (dir);

	}
	else {
  	/* could not open directory */
  		perror ("");
  	// return EXIT_FAILURE;
	}
	return (content);
}

void HTTPResponse::urlEncode(std::string &string)
{
    std::string allowedChars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-_.~";
    std::string hexChars = allowedChars.substr(0, 16);
    char charToEncode;
    size_t posToEncode = string.find_first_not_of(allowedChars, 0);
    while (
        (posToEncode !=std::string::npos)
        &&(posToEncode< string.size())
        )
    {
        charToEncode=string[posToEncode];
        string[posToEncode]='%';
        string.insert(string.begin() + posToEncode + 1,hexChars[charToEncode&0xf]);
        string.insert(string.begin() + posToEncode + 1,hexChars[charToEncode>>4]);
        posToEncode+=3;
        posToEncode = string.find_first_not_of(allowedChars, posToEncode);
    }
}
