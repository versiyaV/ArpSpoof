#ifndef _STRING_H
#define _STRING_H
#include <string>
#include <vector>

namespace String 
{
    std::string& ltrim(std::string &s);
    std::string& rtrim(std::string &s);
    std::string& trim(std::string &s);
    std::vector<std::string> split(std::string s, const std::string &delimiter);
}

#endif