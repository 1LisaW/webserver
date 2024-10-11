#include "includes/WebServer.hpp"

WebServer::WebServer(ServerConfig &serverConfigElem, Dictionary &dictionaryGlobal):serverConfig(serverConfigElem), dictionary(dictionaryGlobal)
{
		struct addrinfo hints;
		hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_flags = AI_PASSIVE;     // fill in my IP for me
		getaddrinfo(serverConfig.serverName.c_str(), serverConfig.listen.c_str(), &(hints), &res);
		socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		fds[0].fd = socket_fd;
  		fds[0].events = POLLIN;
		bind(socket_fd, res->ai_addr, res->ai_addrlen);
		listen(socket_fd, BACKLOG);
		launch();
}

WebServer::~WebServer()
{
}

void WebServer::launch()
{
	while (true)
	{
		std::cout << "---LAUNCH----" << std::endl;
		_accept();
		_handle();
		_respond();
		std::cout << "---LAUNCH STOPED----" << std::endl;

	}
}

void	WebServer::_accept()
{
	new_socket_fd = accept(socket_fd, (res->ai_addr), &(res->ai_addrlen));
	read(new_socket_fd, _buffer, 30000);
}

void	WebServer::_handle()
{
std::cout << _buffer << std::endl;
curr_request = new HTTPRequest(_buffer, dictionary);
}

void	WebServer::_respond()
{
	std::string responseFile = getResponseFilePath(curr_request, serverConfig);
	HTTPResponse response(*curr_request);
	delete curr_request;
	send(new_socket_fd,response.response.c_str(), response.response.size(),0);
	close(new_socket_fd);
}

std::string WebServer::getResponseErrorFilePath(LocationConfig *location, enum status_code_value statusCode)
{
	if (!location)
		return ("");
	std::vector<std::string> errPathVector;
	std::string errPagePath;
	switch (statusCode)
	{
	case forbidden:
		errPathVector =location->errorPages["403"];
		break;
	case not_found:
		errPathVector =location->errorPages["404"];
		break;
	case method_not_allowed:
		errPathVector =location->errorPages["405"];
		break;
	default:
		break;
	}
	if (!errPathVector.size())
		return ("");
	errPagePath.append(errPathVector[0]);
	errPagePath.append(errPathVector[1]);
	int fileFd = open(errPagePath.c_str(), O_RDONLY);
	if (fileFd < 0)
	{
		errPagePath.clear();
	}
	else
		close(fileFd);
	return (errPagePath);
}

std::string WebServer::getResponseFilePath(HTTPRequest *request, ServerConfig &serverConfig)
{
	std::string filePath;
	std::string requestUri = request->get_path();
	// get the location that matches uri of the request
	LocationConfig *location = serverConfig.getLocation(requestUri);
	// if there no location or method is not allowed set error status code
	if (location == NULL)
		request->setStatusCode(not_found);
	else if (!location->isMethodAllowed(request->get_method()))
		request->setStatusCode(method_not_allowed);
	// get path of file
	else
	{
		std::string restUriPath;
		filePath.append(location->root);
		restUriPath.append(requestUri.substr(filePath.size() - 1));
		filePath.append("/");
		filePath.append(restUriPath);

		std::string fileExtention = getUriExtention(filePath);
		if (!fileExtention.size())
		{
			filePath.append("/");
			filePath.append(location->index);
		}
		int fileFd = open(filePath.c_str(), O_RDONLY);
		if (fileFd < 0)
		{
			request->setStatusCode(not_found);
		}
		else
			close(fileFd);
		if (request->get_status_code() && request->get_status_code() != ok)
		{
			filePath.clear();
			filePath.append(getResponseErrorFilePath(location, request->get_status_code()));
		}
	}
	return (filePath);
}

