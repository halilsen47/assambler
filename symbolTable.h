#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <string>
#include <unordered_map>

class symbolTable
{
private:
    std::unordered_map<std::string, int> symboltable;

public:
    symbolTable(/* args */);

    void addEntry(std::string symbol, int address);
    bool contains(std::string symbol);
    int getAdress(std::string symbol);
};

#endif