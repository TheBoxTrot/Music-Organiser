// musicorg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include "SongOperations.h"
#include "Song.h"
#include <iostream>
#include <string>
#include "FileHandler.h"
#include <sstream>






 // Set of desired file extensions
std::set<std::string> fileExtensions = { ".flac", ".mp3", ".mp4" };
void removeExtent()
{

    std::string ss;
    std::cout << "removing:\n";
    std::cin >> ss;
    fileExtensions.erase(ss);

}
void AddExtent()
{
    
    std::string ss;
    std::cout << "adding:\n";
    std::cin >> ss;
	fileExtensions.insert(ss);
 
}
void fileExtensionsSettings()
{
    
	int choice;
    bool loop = true;
    std::set<std::string>::iterator itr;
    while (loop == true)
    {
        std::cout << "What Files do you want searched (include the .)\n";
        std::cout << "Currnet Files:";
        for (itr = fileExtensions.begin();
            itr != fileExtensions.end(); itr++)
        {
            std::cout << *itr << ",";
        }
        std::cout << "what would you like to adjust\n";
        std::cout << "1. Enter New Extension\n";
        std::cout << "2. Remove Extension\n";
        std::cout << "3. Enter 0 to exit\n";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            AddExtent();
            break;
        case 2:
            removeExtent();
            break;
        case 3:
            loop = false;
            break;
        default:
            break;
        }
    }



   
}


int main()
{
    bool loop = true;
    int choice;
    std::cout << "Welcome\n1.Start\n2.Extention settings\n"<<std::endl;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        loop = false;
        break;
    case 2:
        fileExtensionsSettings();
        break;
    default:
        break;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::vector<fs::path> songpaths;
    
    std::string sourceFolderPath;
    std::string destinationFolderPath;
    try {
   

        std::cout << "Enter the source folder path: ";
        std::getline(std::cin, sourceFolderPath);

        std::cout << "Enter the destination folder path: ";
        std::getline(std::cin, destinationFolderPath);

        fs::path sourceDir(sourceFolderPath);
        fs::path destinationDir(destinationFolderPath);

        if (!fs::exists(sourceDir) || !fs::is_directory(sourceDir) ||
            !fs::exists(destinationDir) || !fs::is_directory(destinationDir)) {
            std::cerr << "Invalid source or destination folder." << std::endl;
            return 1;
        }

       

        songpaths= findFiles(sourceDir, fileExtensions);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
 
	
    std::vector<Song> songs = importMusic(songpaths,destinationFolderPath);
  AttemptMove(songs);

    ///convert to .sound
    




    // Get the tag of the file

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
