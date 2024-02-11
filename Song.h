#pragma once
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
struct Song
{
	TagLib::String title;
	TagLib::String artist;
	TagLib::String album;
	TagLib::String albumArtist;

	int year;
	fs::path oldpath;
	fs::path NewPath;
};