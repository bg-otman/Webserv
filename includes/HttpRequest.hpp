#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include "libs.hpp"

class HttpRequest
{
    private:
        std::string method;
        std::string path;
        std::string version;
        std::multimap<std::string, std::string> headers;
        std::string body;
    public:
        HttpRequest();
        ~HttpRequest();
        void    setMethod( const std::string& method);
        void    setPath( const std::string& Path);
        void    setVersion( const std::string& version);
        // void    setHeaders( const std::string& version);
        const std::string&    getMethod( void ) const;
        const std::string&    getPath( void ) const;
        const std::string&    getVersion( void ) const;
};

#endif
