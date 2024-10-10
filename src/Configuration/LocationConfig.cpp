#include "includes/LocationConfig.hpp"

// Location
LocationConfig::LocationConfig(Dictionary &dict, std::map<std::string, std::vector<std::string> > serverErrPages) : dictionary(dict)
{
	resetToDefault();
	std::map<std::string, std::vector<std::string> >::iterator itErrPage;

	for (itErrPage = serverErrPages.begin(); itErrPage != serverErrPages.end(); itErrPage++)
	{
		std::vector<std::string> second = itErrPage->second;
		errorPages[itErrPage->first] = second;
	}
}
LocationConfig &LocationConfig::operator=(const LocationConfig &rhs)
{
	resetToDefault();
	this->dictionary = rhs.dictionary;

	std::map<std::string, std::vector<std::string> >::const_iterator itErrPage;

	for (itErrPage = rhs.errorPages.begin(); itErrPage != rhs.errorPages.end(); itErrPage++)
	{
		std::vector<std::string> second = itErrPage->second;
		this->errorPages[itErrPage->first] = second;
	}
	return (*this);
}

LocationConfig::~LocationConfig()
{
}
void LocationConfig::resetToDefault()
{
	this->modifier.clear();
	this->strictMatch = false;
	this->uri.clear();
	this->allowedMethods.clear();
	this->root.clear();
	this->index.clear();

	this->isCgi = false;
	this->cgiPass.clear();
	this->cgiIndex.clear();
	this->cgiInclude.clear();
	this->cgiParams.clear();
	this->errorPages.clear();
}
void LocationConfig::setUri(std::vector<std::string> vector)
{
	size_t idx = 1;
	if (vector[idx].size() == 1 && (vector[idx][0] == '=' || vector[idx][0] == '~'))
	{
		modifier = vector[idx];
		idx++;
	}
	if (vector.size() != (idx + 2))
	{
		modifier.clear();
		std::cout << "Invalid location data" << std::endl;
		return;
	}
	uri = vector[idx];
}
void LocationConfig::setRoot(std::vector<std::string> vector)
{
	if (!isValidOneValue(vector))
	{
		root.empty();
		return;
	}
	root = vector[1];
}

void LocationConfig::setIndex(std::vector<std::string> vector)
{
	if (!isValidOneValue(vector))
	{
		index.empty();
		return;
	}
	index = vector[1];
}
void LocationConfig::setAllowedMethods(std::vector<std::string> vector)
{
	size_t size = vector.size();
	for (size_t i = 1; i < size; i++)
	{
		if (dictionary.isMethodInDictionary(vector[i]))
			allowedMethods.insert(vector[i]);
		else
			std::cout << "Method " << vector[i] << " is not supported by server. This method will be ignored" << std::endl;
	}
}

void LocationConfig::setCgiPass(std::vector<std::string> vector)
{
	isCgi = true;
	if (!isValidOneValue(vector))
	{
		cgiPass.empty();
		return;
	}
	cgiPass = vector[1];
}

void LocationConfig::setCgiIndex(std::vector<std::string> vector)
{
	isCgi = true;
	if (!isValidOneValue(vector))
	{
		cgiIndex.empty();
		return;
	}
	cgiIndex = vector[1];
}

void LocationConfig::setCgiInclude(std::vector<std::string> vector)
{
	isCgi = true;
	if (!isValidOneValue(vector))
	{
		cgiInclude.empty();
		return;
	}
	cgiInclude = vector[1];
}

void LocationConfig::setCgiParams(std::vector<std::string> vector)
{
	isCgi = true;
	if (vector.size() != 3)
	{
		std::cout << "Incorrect format fo CGI parameters" << std::endl;
		return;
	}
	cgiParams[vector[1]] = vector[2];
}

void LocationConfig::fillAttributes(std::vector<std::string> confLineVector, Dictionary &dictionary)
{
	if (!dictionary.isAttributeInLocationDictionary(confLineVector[0]))
	{
		std::cout << "Attribute of location \"" << confLineVector[0] << "\" not supported." << std::endl;
		return;
	}
	std::string attributeName = confLineVector[0];
	if (!attributeName.compare("root"))
		setRoot(confLineVector);
	else if (!attributeName.compare("index"))
		setIndex(confLineVector);
	else if (!attributeName.compare("error_page"))
		addErrorPages(confLineVector);
	else if (!attributeName.compare("allow_methods"))
		setAllowedMethods(confLineVector);
	else if (!attributeName.compare("cgi_pass"))
		setCgiPass(confLineVector);
	else if (!attributeName.compare("cgi_index"))
		setCgiIndex(confLineVector);
	else if (!attributeName.compare("include"))
		setCgiInclude(confLineVector);
	else if (!attributeName.compare("cgi_param"))
		setCgiParams(confLineVector);
}

bool LocationConfig::isValid()
{
	if (!isCgi && (uri.empty() || root.empty()))
		return (false);
	return (true);
}
