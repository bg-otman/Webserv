#include "../includes/HttpParser.hpp"

HttpParser::HttpParser()
    : state(REQUEST_LINE), expectedBodySize(0), errorCode(0)
{
    (void) state; // to silent -Werror for now
    (void) expectedBodySize;
    (void) errorCode;
}

HttpParser::~HttpParser() {}

ParseResult		HttpParser::parseRequest(const std::string& data)
{
    ParseResult result = NONE;
    this->errorCode = 0;
    this->buffer.append(data);
    while (true)
    {
        switch (this->state)
        {
            case REQUEST_LINE:
                result = parseRequestLine();
                break;
            case HEADERS:
                result = parseHeaders();
                // return COMPLETE; // temperory for testing
                break;
            case BODY:
                // result = parseBody();
                break;
            default:
                break;
        }
        if (result != NONE) break;
    }
    return result;
}

ParseResult HttpParser::parseRequestLine()
{
    std::vector<std::string>    requestLine;
    size_t                      pos = buffer.find("\r\n");
    size_t                      uriMaxLength = 8000;
    size_t                      p_size = strlen("HTTP/"); // Pattern size
    double                      version = 0.0;

    if (pos == std::string::npos)
        return INCOMPLETE;
    requestLine = Utils::split(buffer.substr(0, pos), ' ');
    buffer.erase(0, pos + 2); // 2 for \r\n
    if (requestLine.size() != 3)
    {
        if (requestLine.size() == 2)
            requestLine.push_back("HTTP/0.9"); // default version
        else
            errorCode = BAD_REQUEST;
    } else if (requestLine.size() == 3 && requestLine[2] == "HTTP/0.9")
        errorCode = BAD_REQUEST;
    if (!errorCode && (requestLine[0] != "GET" && requestLine[0] != "POST"
                            && requestLine[0] != "DELETE"))
        Utils::isAllUpper(requestLine[0]) ? errorCode = METHOD_NOT_ALLOWED : errorCode = BAD_REQUEST;
    if (!errorCode && requestLine[1].length() > uriMaxLength)
        errorCode = URI_TOO_LONG;
    if (!errorCode && requestLine[2].substr(0, p_size) != "HTTP/")
        errorCode = BAD_REQUEST;
    else if (!errorCode)
    {
        char *endptr = NULL;
        version = strtod(requestLine[2].substr(p_size, requestLine[2].length() - p_size).c_str(), &endptr);
        if (version < 0.9 || *endptr)
            errorCode = BAD_REQUEST;
        else if (version > 1.1)
            errorCode = HTTP_VERSION_NOT_SUPPORTED;
    }

    if (errorCode == 0)
    {
        this->request.setMethod(requestLine[0]);
        this->request.setPath(requestLine[1]);
        this->request.setVersion(requestLine[2]);
        this->state = HEADERS; // adjust parse state
        return NONE;
    }
    return ERROR;
}


/*
    All duplicate headers should be combined separated by comma 
    Edge cases:
        {Host, Conten-length, Transfer-Encoding} headers can't be duplicated
        {Set-Cookie} headers should not be concatenated

*/
ParseResult HttpParser::parseHeaders()
{
    std::multimap<std::string, std::string> headers;
    
}

const HttpRequest&    HttpParser::getRequest( void ) const
{
    return this->request;
}

int HttpParser::getErrorCode( void ) const
{
    return this->errorCode;
}
