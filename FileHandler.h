#pragma once
#include <filesystem>
#include <set>
#include <vector>
namespace fs = std::filesystem;
std::vector<fs::path> findFiles(fs::path path, const std::set<std::string>& fileExtensions);
void moveFile(std::string source, std::string destination);
void copyFile(std::string source, std::string destination);