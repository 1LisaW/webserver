#include "includes/ServerConfig.hpp"

// ServerConfig.
ServerConfig::ServerConfig()
{
	listen = "";
	serverName = "";
	errorPages.clear();
	clientMaxBodySize = 0;
	index = "";
	locations.clear();
}

ServerConfig::~ServerConfig()
{
}

void ServerConfig::setListen(std::vector<std::string> vector)
{

	if (!isValidOneDigitValue(vector))
	{
		listen = "";
		return;
	}
	listen = vector[1];
}

void ServerConfig::setServerName(std::vector<std::string> vector)
{
	if (!isValidOneValue(vector))
	{
		serverName = "";
		return;
	}
	serverName = vector[1];
}

void ServerConfig::setClientMaxBodySize(std::vector<std::string> vector)
{
	if (!isValidOneDigitValue(vector))
	{
		clientMaxBodySize = 0;
		return;
	}
	int i;
	std::istringstream(vector[1]) >> i;
	clientMaxBodySize = i;
}

void ServerConfig::setIndex(std::vector<std::string> vector)
{
	if (!isValidOneValue(vector))
	{
		index = "";
		return;
	}
	index = vector[1];
}

void ServerConfig::fillAttributes(std::vector<std::string> confLineVector, Dictionary &dictionary)
{
	if (!dictionary.isAttributeInServerDictionary(confLineVector[0]))
	{
		std::cout << "Attribute of server \"" << confLineVector[0] << "\" not supported." << std::endl;
		return;
	}
	std::string attributeName = confLineVector[0];
	if (!attributeName.compare("listen"))
		setListen(confLineVector);
	else if (!attributeName.compare("server_name"))
		setServerName(confLineVector);
	else if (!attributeName.compare("client_max_body_size"))
		setClientMaxBodySize(confLineVector);
	else if (!attributeName.compare("error_page"))
		addErrorPages(confLineVector);
}

bool ServerConfig::isValid()
{
	if (listen.empty() || serverName.empty())
		return (false);
	return (true);
}

