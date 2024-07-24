#pragma once
#include "Song.h"
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>

std::vector<Song> importMusic(std::vector<fs::path> songpaths, std::string destinationFolderPath, std::string configstring);
void AttemptMove(std::vector<Song> songs);
std::string convertConfigStringToSongString(std::string configstring, TagLib::FileRef& fileRef);