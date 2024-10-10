#ifndef SERVERCONFIG_H
# define SERVERCONFIG_H

# include "LocationConfig.hpp"
# include <sstream>


class ServerConfig: public Attribute
{
private:
	void	setListen(std::vector<std::string> vector);
	void	setServerName(std::vector<std::string> vector);
	void	setClientMaxBodySize(std::vector<std::string> vector);
	void	setIndex(std::vector<std::string> vector);

public:
	std::string listen;
	std::string serverName;
	int clientMaxBodySize;
	std::string index;
	std::vector<LocationConfig> locations;

	ServerConfig();
	~ServerConfig();
	void	fillAttributes(std::vector<std::string> confLineVector, Dictionary &dictionary);
	bool	isValid();
};


#endif
