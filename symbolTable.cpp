#include "symbolTable.h"
#include <iostream>

symbolTable::symbolTable()
{
    symboltable =
        {
            {"SP", 0},
            {"LCL", 1},
            {"ARG", 2},
            {"THIS", 3},
            {"THAT", 4},
            {"SCREEN", 16384},
            {"KBD", 24576}

        };
    for (size_t i = 0; i < 16; i++)
    {
        std::string name = 'R' + std::to_string(i);
        symboltable[name] = i;
    }
}

void symbolTable::addEntry(std::string symbol, int address)
{
    symboltable[symbol] = address;
}

bool symbolTable::contains(std::string symbol)
{
    return symboltable.count(symbol);
}

int symbolTable::getAdress(std::string symbol)
{
    return symboltable[symbol];
}