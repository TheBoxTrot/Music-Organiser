#include "SongOperations.h"
#include <fileref.h>
#include <sstream>
#include <taglib/tpropertymap.h>
#include "FileHandler.h"
std::vector<Song> importMusic(std::vector<fs::path> songpaths, std::string destinationFolderPath)
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


                currentsong.title = tag->title();
                currentsong.artist = tag->artist();
                currentsong.album = tag->album();
                currentsong.albumArtist = fileRef.file()->properties()["ALBUMARTIST"].front();
                std::cout << currentsong.albumArtist << std::endl;
                std::cout << "year: " << currentsong.album << std::endl;
                currentsong.year = tag->year();
                currentsong.oldpath = songpaths[i];
                ss << destinationFolderPath << "\\";
                if (currentsong.albumArtist.isEmpty())

                {
                    ss << currentsong.artist;
                }
                else
                {
                    ss << currentsong.albumArtist;
                }
                ss << "\\" << currentsong.album << ' ' << '(' << currentsong.year << ')' << "\\";
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
