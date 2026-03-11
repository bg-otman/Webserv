#include "../../includes/HttpResponse.hpp"

std::string     HttpResponse::handlePOST(const HttpRequest& request)
{
    (void) request;
    return this->build();
}