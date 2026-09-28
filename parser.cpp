#include "Parser.h"
#include <iostream>

Parser::Parser(std::string filename)
{
    file.open(filename);
}

Parser::~Parser()
{
    file.close();
}

bool Parser::hasMoreLines()
{
    if (file.eof())
    {
        return false;
    }
    return true;
}

void Parser::advance()
{
    while (getline(file, currentCommand))
    {

        std::string cleantext = "";
        for (char c : currentCommand)
        {
            if (c != ' ' && c != '\t' && c != '\r')
            {
                cleantext += c;
            }
        }
        currentCommand = cleantext;

        size_t commentPos = currentCommand.find("//");
        if (commentPos != std::string::npos)
        {
            currentCommand = currentCommand.substr(0, commentPos);
        }

        if (!currentCommand.empty())
        {
            // std::cout << currentCommand + "\n";
            break;
        }
    }
}

CommandType Parser::instructionType()
{

    if (currentCommand.empty())
        return EMPTY_COMMAND;
    if (currentCommand[0] == '@')
        return A_COMMAND;
    if (currentCommand[0] == '(' && currentCommand[currentCommand.length() - 1] == ')')
        return L_COMMAND;
    else
        return C_COMMAND;
}

std::string Parser::symbol()
{
    if (currentCommand.empty())
        return "";

    // @xxx  ->  xxx
    if (currentCommand.front() == '@')
        return currentCommand.substr(1);

    // (xxx) ->  xxx
    if (currentCommand.front() == '(' && currentCommand.back() == ')')
        return currentCommand.substr(1, currentCommand.length() - 2);

    return currentCommand;
}

std::string Parser::dest()
{
    size_t destOpPos = currentCommand.find('=');
    std::string dest;
    if (destOpPos != std::string::npos)
    {
        dest = currentCommand.substr(0, destOpPos);
        return dest;
    }
    return "";
}

std::string Parser::comp()
{
    size_t startPos = currentCommand.find('=');
    size_t finishPos = currentCommand.find(';');
    std::string comp;
    if (startPos != std::string::npos && finishPos != std::string::npos)
    {
        size_t lenght = finishPos - (startPos + 1);
        comp = currentCommand.substr(startPos + 1, lenght);
        return comp;
    }

    if (startPos != std::string::npos && finishPos == std::string::npos)
    {
        comp = currentCommand.substr(startPos + 1);
        return comp;
    }

    if (startPos == std::string::npos && finishPos != std::string::npos)
    {
        comp = currentCommand.substr(0, finishPos);
        return comp;
    }

    return "";
}

std::string Parser::jump()
{
    size_t jumpPos = currentCommand.find(';');
    if (jumpPos != std::string::npos)
    {
        std::string jump = currentCommand.substr(jumpPos + 1);
        return jump;
    }
    return "";
}

void Parser::reset()
{
    file.clear();
    file.seekg(0);
    currentCommand = "";
}