#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(char const *buffer)
{
    status_code = status_code::value::uninitialized;
    buff.append(buffer);
    if (!buff.size())
    {
        std::cout << "Err request" << std::endl;
        return ;
    }
    this->method.append(buff.substr(0, buff.find_first_of(' ')));
    buff.erase(0, this->method.length());
    if (HTTPRequest::METHODS.find(method) == HTTPRequest::METHODS.end())
    {  
        this->status_code = status_code::value::bad_request;
        std::cout << "NOT FOUND! " << std::endl;
    }
    std::cout << "Method is " << method << std::endl;
    std::cout << "Rest is " << buff << std::endl;

}

HTTPRequest::~HTTPRequest()
{
}

const std::string methods[] = {"GET","POST","DELETE"};
const std::set<std::string> HTTPRequest::METHODS(methods,methods + sizeof(methods)/sizeof(methods[0]));
// const std::set<std::string> HTTPRequest::METHODS = {"GET", "POST", "DELETE"};
// HTTPRequest::METHODS("")
