#include "SongOperations.h"
#include <fileref.h>
#include <sstream>
#include <taglib/tpropertymap.h>
#include "FileHandler.h"
#include "Song.h"
#include <iostream>
#include <string>

std::vector<Song> importMusic(std::vector<fs::path> songpaths, std::string destinationFolderPath, std::string configstring)
{
	{
		std::vector<Song> songs;
		for (int i = 0;i < songpaths.size();i++)
		{
			Song currentsong;
			std::stringstream ss;
			TagLib::FileRef fileRef(songpaths[i].string().c_str());
			TagLib::Tag* tag = fileRef.tag();
			if (fileRef.isNull()) {
				std::cerr << "Error opening file." << std::endl;
			}
			else
			{


				//currentsong.title = tag->title();
				//currentsong.artist = tag->artist();
				//currentsong.album = tag->album();
				//currentsong.albumArtist = fileRef.file()->properties()["ALBUMARTIST"].front();
				//std::cout << currentsong.albumArtist << std::endl;
				//std::cout << "year: " << currentsong.album << std::endl;
				//currentsong.year = tag->year();
				currentsong.oldpath = songpaths[i];
				ss << destinationFolderPath << "\\" << convertConfigStringToSongString(configstring, fileRef);
				/*    if (currentsong.albumArtist.isEmpty())

					{
						ss << currentsong.artist;
					}
					else
					{
						ss << currentsong.albumArtist;
					}*/
					// ss << "\\" << currentsong.album << ' ' << '(' << currentsong.year << ')' << "\\";
				currentsong.NewPath = ss.str();
				songs.push_back(currentsong);
			}
		}
		return songs;
	}
}

void AttemptMove(std::vector<Song> songs)
{
	{
		fs::path oldpath;
		for (int i = 0;i < songs.size();i++)
		{
			///weird bullshit if you have a ' it will become ↓
			oldpath = songs[i].oldpath;
			oldpath.replace_extension(".lrc");
			if (fs::exists(oldpath))
			{
				moveFile(oldpath.string(), songs[i].NewPath.string());
			}


			moveFile(songs[i].oldpath.string(), songs[i].NewPath.string());
		}
	}
}

std::string convertConfigStringToSongString(std::string configstring, TagLib::FileRef& fileRef)
{
	std::cout << fileRef.file()->tag()->title() << std::endl;
	std::string songstring;
	std::string newstring;
	bool insidebracket = false;
	std::stringstream ss(configstring);
	///outside a $ $ bracket
	while (std::getline(ss, songstring, '`'))
	{
		newstring.append(songstring);
		if (!ss.eof()) {
			///inside a $ $ bracket
			std::getline(ss, songstring, '`');
			std::string a;
			TagLib::String b;
			try {

				///hardcoded cause who wants the whole date
				if (songstring == "YEAR")
				{
					if (fileRef.file()->properties()["DATE"].isEmpty())
						throw std::exception("Date is empty");



					b = fileRef.file()->properties()["DATE"].front();
					// Rest of the code when the property exists



					std::stringstream ss(b.to8Bit());
					std::getline(ss, a, '-');

				}
				else
				{
					if (fileRef.file()->properties()[songstring].isEmpty())
						throw std::exception("Property is empty");

					b = fileRef.file()->properties()[songstring].front();
					a = b.to8Bit();
				}
				newstring.append(a);
			}
			catch (const std::exception& e) {
				newstring.append("NA");
			}
		}

	}
	return newstring;
	///inside a $ $ bracket
}
