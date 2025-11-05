#pragma once
#include "GameError.h"
#include <string>

using namespace std::string_literals;
class FileFormatError : public GameError
{
public:
    FileFormatError(const std::string& fileName, int line) : GameError("Error leyendo el archivo: "s + fileName + ", en la linea "s + std::to_string(line)){}
};

