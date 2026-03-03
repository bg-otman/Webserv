#ifndef UTILS_HPP
#define UTILS_HPP

#include "libs.hpp"

class Utils
{
    private:
        Utils();
    public:
        static std::vector<std::string> split(const std::string str, const char delimter);
        static bool    isAllUpper(const std::string& str);
};

#endif
