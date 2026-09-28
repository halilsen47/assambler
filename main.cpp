#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include "parser.h"
#include "code.h"
#include "symbolTable.h"

int main(int argc, char *argv[])
{
    // Varsayilan: pong.asm -> pong.hack
    // Istege bagli: main.exe <girdi.asm> <cikti.hack>
    std::string inputFile = (argc > 1) ? argv[1] : "pong_fast.asm";
    std::string outputFile = (argc > 2) ? argv[2] : "pong_fast.hack";

    Parser parser(inputFile);
    std::ofstream file(outputFile);
    Code code;
    symbolTable symbolTable;
    int romAddress = 0;
    int ramAddress = 16;

    while (parser.hasMoreLines())
    {
        parser.advance();
        CommandType type = parser.instructionType();
        // L
        if (type == L_COMMAND)
        {
            std::string symbol = parser.symbol();
            symbolTable.addEntry(symbol, romAddress);
        }
        // A
        if (type == A_COMMAND || type == C_COMMAND)
            romAddress++;
    }
    parser.reset();

    while (parser.hasMoreLines())
    {
        parser.advance();
        CommandType type = parser.instructionType();
        // A
        if (type == A_COMMAND)
        {
            bool isNumber = true;
            std::string symbol = parser.symbol();
            std::string concatedBinCode;

            for (size_t i = 0; i < symbol.length(); i++)
            {
                if (!std::isdigit(symbol[i]))
                {
                    isNumber = false;
                }
            }

            if (isNumber)
            {
                symbol = std::bitset<15>(std::stoi(symbol)).to_string();
            }
            else
            {
                if (!symbolTable.contains(symbol))
                {
                    symbolTable.addEntry(symbol, ramAddress);
                    symbol = std::bitset<15>(ramAddress).to_string();
                    ramAddress++;
                }
                else if (symbolTable.contains(symbol))
                {
                    int number = symbolTable.getAdress(symbol);
                    symbol = std::bitset<15>(number).to_string();
                }
            }

            concatedBinCode = "0" + symbol;
            file << concatedBinCode + "\n";
        }

        // C
        if (type == C_COMMAND)
        {
            std::string dest = parser.dest();
            std::string comp = parser.comp();
            std::string jump = parser.jump();

            std::string binCodeComp = code.comp(comp);
            std::string binCodeDest = code.dest(dest);
            std::string binCodejump = code.jump(jump);

            std::string concatedBinCode = "111" + binCodeComp + binCodeDest + binCodejump;
            file << concatedBinCode + "\n";
        }
    }

    file.close();
    return 0;
}