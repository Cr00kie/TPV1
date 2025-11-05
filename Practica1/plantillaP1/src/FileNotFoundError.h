#pragma once
#include "GameError.h"
#include <string>
using namespace std::string_literals;
class FileNotFoundError : public GameError
{
public:
    FileNotFoundError(const std::string& fileName) : GameError("No se ha podido abrir el archivo: "s + fileName){}
};

