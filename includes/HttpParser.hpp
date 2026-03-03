#ifndef HTTPPARSER_HPP
#define HTTPPARSER_HPP

#include "libs.hpp"
#include "HttpRequest.hpp"
#include "Utils.hpp"

enum StatusCode {
    OK = 200,
    CREATED = 201,
    NO_CONTENT = 204,
    BAD_REQUEST = 400,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    METHOD_NOT_ALLOWED = 405,
    PAYLOAD_TOO_LARGE = 413,
    URI_TOO_LONG = 414,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    HTTP_VERSION_NOT_SUPPORTED = 505
};

enum ParseResult {
	NONE,
    INCOMPLETE,
    COMPLETE,
    ERROR
};

class HttpParser
{
    private:
        enum ParseState {
            REQUEST_LINE,
            HEADERS,
            BODY,
        };
        ParseState	state;
        std::string	buffer;
		HttpRequest	request;
        size_t		expectedBodySize;
		int			errorCode;

		ParseResult		parseRequestLine();
		ParseResult		parseHeaders();
		// ParseResult		parseBody();
		// ParseResult		parseChunkBody();
    public:
        HttpParser();
        ~HttpParser();
		ParseResult         parseRequest(const std::string& data);
		const HttpRequest&  getRequest( void ) const;
		int				    getErrorCode( void ) const;
};


#endif
