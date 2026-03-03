#include "../includes/HttpRequest.hpp"

HttpRequest::HttpRequest()
{
}

HttpRequest::~HttpRequest()
{
}

void    HttpRequest::setMethod(const std::string& method)
{
    this->method = method;
}

void    HttpRequest::setPath(const std::string& path)
{
    this->path = path;
}

void    HttpRequest::setVersion(const std::string& version)
{
    this->version = version;
}

const std::string&  HttpRequest::getMethod( void ) const
{
    return this->method;
}

const std::string&  HttpRequest::getPath( void ) const
{
    return this->path;
}

const std::string&  HttpRequest::getVersion( void ) const
{
    return this->version;
}
