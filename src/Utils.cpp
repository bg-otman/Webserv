#include "Utils.hpp"

std::vector<std::string> Utils::split(const std::string str, const char delimter)
{
    std::stringstream           ss(str);
    std::string                 word;
    std::vector<std::string>    result;

    while (std::getline(ss, word, delimter))
        if (!word.empty())
            result.push_back(word);
    return result;
}

bool    Utils::isAllUpper(const std::string& str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if (std::islower(str[i]))
            return false;
    }
    return true;
}
