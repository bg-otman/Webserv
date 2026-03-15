#include "Config.hpp"
#include "HttpParser.hpp"
#include "HttpResponse.hpp"
#include "Server.hpp"

void    print_request(const HttpRequest& request)
{
    std::cout << "\nRequest line" << std::endl;
    std::cout << "*******" << std::endl;
    std::cout << "Method : " << request.getMethod() << std::endl;
    std::cout << "Path : " << request.getPath() << std::endl;
    std::cout << "Version : " << request.getVersion() << std::endl;
    std::cout << "*******" << std::endl << std::endl;

    std::cout << "Request Headers:" << std::endl;
    std::cout << "+++++++" << std::endl;
    const std::map<std::string, std::string>& headers = request.getHeaders();
    for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }
    std::cout << "+++++++" << std::endl;
    
    std::cout << "\nBody:"<< std::endl;
    std::cout << "[" << request.getBody() << "]" << std::endl;
    std::cout << "+++++++" << std::endl;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./webserv [config_file]" << std::endl;
        return 1;
    }
    int i = 0;
    try {
        ConfigParser parser(argv[1]);
        std::cout << "✅ Configuration parsed and validated successfully!" << std::endl;
        i = 1;
        Server server;
        server.init(parser.getServers());
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}