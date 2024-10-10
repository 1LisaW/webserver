#ifndef WEBSERVER_H
# define WEBSERVER_H

# include <fcntl.h>
# include <unistd.h>
# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
#include <sys/poll.h>

# include "../../Configuration/includes/Dictionary.hpp"
# include "../../HTTP/includes/HTTPRequest.hpp"
# include "../../HTTP/includes/HTTPResponse.hpp"

#define BACKLOG 10     // how many pending connections queue will hold

struct locationStr {
	bool	exactMatch;
    std::vector<std::string> uri;
    std::string root;
    std::vector<std::string> allowedMethods;
} ;

struct Config
{
	const char* node; // e.g. "www.example.com" or IP
	const char* service;  // e.g. "http" or port number
	struct addrinfo hints;
};


class WebServer
{
private:
	int		socket_fd;
	int		new_socket_fd;
	struct pollfd fds[200];
	char	_buffer[30000];
	struct addrinfo *res;
	bool	_parse_config(int argc, char* argv[], struct Config &config);
	void	_accept();
	void	_handle();
	void	_respond();
	HTTPRequest *curr_request;
	std::vector<locationStr> _locations;
	locationStr *getLocation(std::string path);
public:
	WebServer(int argc, char* argv[]);
	~WebServer();
	void launch();
	static std::map<std::string, std::string> dictionaryContentTypes;
	static Dictionary dictionary;
};

// std::map<std::string, std::string> WebServer::dictionaryContentTypes = setDictionaryContentTypes();
#endif
