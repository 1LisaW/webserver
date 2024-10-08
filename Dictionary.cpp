#include "Dictionary.hpp"


Dictionary::Dictionary()
{
	init();
}

Dictionary::~Dictionary()
{
}

void Dictionary::_setContentTypes()
{
	// text
	contentTypes["html"] = "text/html";
	contentTypes["css"] = "text/css";
	contentTypes["js"] = "text/javascript";
	contentTypes["txt"] = "text/plain";
	// image
	contentTypes["ico"] = "image/x-icon";
	contentTypes["gif"] = "image/gif";
	contentTypes["jpeg"] = "image/jpeg";
	contentTypes["png"] = "image/png";
}

void Dictionary::_setMethods()
{
	const std::string methodsArr[] = {"GET","POST","DELETE"};
	methods = std::set<std::string>(methodsArr, methodsArr + sizeof(methodsArr)/sizeof(methodsArr[0]));
}

void Dictionary::init()
{
	_setMethods();
	_setContentTypes();
}

bool Dictionary::isMethodInDictionary(std::string method)
{
	if (methods.find(method) == methods.end())
		return (false);
	return (true);
}

std::string Dictionary::getContentTypeFromDictionary(std::string type)
{
	if (contentTypes.find(type) == contentTypes.end())
		return ("");
	return (contentTypes[type]);
}
