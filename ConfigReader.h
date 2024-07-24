#pragma once
#include <string>
#include "Config.h"
#include <map>
std::map<std::string, std::string>  ReadConfig();
bool doesConfigExist();
void createDefaultConfig();
