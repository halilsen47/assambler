#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>

// Komut tiplerini belirlediğimiz yapı
enum CommandType
{
    A_COMMAND,
    C_COMMAND,
    L_COMMAND,
    EMPTY_COMMAND
};

class Parser
{
private:
    std::ifstream file;         // 📁 Dosyayı okuyacak nesnemiz
    std::string currentCommand; // O an üzerinde çalıştığımız temizlenmiş satır

public:
    Parser(std::string filename);

    ~Parser();

    bool hasMoreLines();
    void advance();
    CommandType instructionType();
    std::string symbol();
    std::string dest();
    std::string comp();
    std::string jump();
    void reset();
};

#endif