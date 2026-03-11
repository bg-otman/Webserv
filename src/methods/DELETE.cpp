#include "../../includes/HttpResponse.hpp"

std::string     HttpResponse::handleDELETE(const HttpRequest& request)
{
    (void) request;
    return this->build();
}