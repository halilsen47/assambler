#ifndef CODE_H
#define CODE_H

#include <string>
#include <fstream>
#include <unordered_map>

class Code
{
private:
    std::unordered_map<std::string, std::string> destMap;
    std::unordered_map<std::string, std::string> compMap;
    std::unordered_map<std::string, std::string> jumpMap;

public:
    Code();

    std::string dest(std::string operation);
    std::string comp(std::string operation);
    std::string jump(std::string operation);
};

#endif
