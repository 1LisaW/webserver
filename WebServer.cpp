#include "WebServer.hpp"

WebServer::WebServer(int argc, char* argv[])
{
	struct Config config;

	config.node = NULL;
	config.service = NULL;
	if (_parse_config(argc, argv, config))
	{
		getaddrinfo(config.node, config.service, &(config.hints), &res);
		socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		fds[0].fd = socket_fd;
  		fds[0].events = POLLIN;
		bind(socket_fd, res->ai_addr, res->ai_addrlen);
		listen(socket_fd, BACKLOG);
		launch();
	};
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

bool WebServer::_parse_config(int argc, char* argv[], struct Config &config)
{
	if (argc < 2)
	{
		std::cout << "Server requires a configuration file" << std::endl;
		return(false);
	}
	int conf_fd = open(argv[1], O_RDONLY);
	if (conf_fd < 0)
	{
		std::cout << "File " << argv[1] << "don't exist or user has no read permission" << std::endl;
		return(false);
	}
	// TODO:: Read from file

	//Mock for locations
	locationStr firstLocation;
	firstLocation.uri.push_back("/");
	firstLocation.exactMatch = false;
	firstLocation.allowedMethods.push_back("GET");
	firstLocation.root = "/www";
	this->_locations.push_back(firstLocation);
	locationStr secondLocation;
	secondLocation.uri.push_back("/cgi-bin");
	secondLocation.uri.push_back("/");
	secondLocation.exactMatch = false;
	secondLocation.allowedMethods.push_back("POST");
	secondLocation.allowedMethods.push_back("DELETE");
	secondLocation.root = "/cgi-bin";
	this->_locations.push_back(secondLocation);



	close(conf_fd);
	config.node = "localhost";
	config.service = "3000";
	// (config.hints) = (struct addrinfo){};
	config.hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
	config.hints.ai_socktype = SOCK_STREAM;
	config.hints.ai_flags = AI_PASSIVE;     // fill in my IP for me
	return (true);
}

void	WebServer::_accept()
{
	new_socket_fd = accept(socket_fd, (res->ai_addr), &(res->ai_addrlen));
	read(new_socket_fd, _buffer, 30000);
// struct sockaddr_in	address =
}

void	WebServer::_handle()
{
std::cout << _buffer << std::endl;
// std::cout << "HTTPREQUEST" << std::endl;
// HTTPRequest request(_buffer);
curr_request = new HTTPRequest(_buffer, WebServer::dictionary);
}

void	WebServer::_respond()
{
	// std::string serv_msg = "Hello from serv\n";
	// write(new_socket_fd, serv_msg.c_str(), serv_msg.length());
	// char arr[200]="HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 16\n\n<h1>testing</h1>";
	// int send_res=
	HTTPResponse response(*curr_request);
	// std::cout << "---- RESPONSE: " << curr_request->get_path() << std::endl;
	// std::cout << response.response << std::endl;
	// std::cout << "RESPONSE ENDS HERE ----- " << std::endl;
	delete curr_request;
	// send(new_socket_fd,arr,sizeof(arr),0);
	send(new_socket_fd,response.response.c_str(), response.response.size(),0);
	close(new_socket_fd);
}

locationStr *WebServer::getLocation(std::string pathWithIndex)
{

	locationStr *location = NULL;
	std::vector<locationStr>::iterator iter;
	int	deepLevelPath = 1000;
	iter = _locations.begin();
	while (iter != _locations.end())
	{
		iter++;
	}
}

Dictionary WebServer::dictionary = Dictionary();
