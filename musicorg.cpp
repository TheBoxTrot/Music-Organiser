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
#include "ConfigReader.h"





 // Set of desired file extensions
std::set<std::string> fileExtensions;

void seperateExtensions(std::string extensions, std::set<std::string>& fileExtensions)
{
	std::stringstream ss(extensions);
	std::string token;
	while (std::getline(ss, token, ','))
	{
		fileExtensions.insert(token);
	}
}

int main()
{


	if (!doesConfigExist())
	{
		createDefaultConfig();
	}
	//std::cout << "asda" << std::endl;
	std::map<std::string, std::string> config = ReadConfig();
	seperateExtensions(config["FileTypes"], fileExtensions);

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



		songpaths = findFiles(sourceDir, fileExtensions);
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}


	std::vector<Song> songs = importMusic(songpaths, destinationFolderPath, config["Dir layout"]);
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
