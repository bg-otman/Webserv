#include "../../includes/HttpResponse.hpp"

std::string     HttpResponse::handleGET(const HttpRequest& request)
{
    (void) request;
    return this->build();
}
