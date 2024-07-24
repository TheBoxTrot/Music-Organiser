#include "FileHandler.h"
#include <thread>
#include <chrono>
#include <iostream>
std::vector<fs::path> findFiles(fs::path path, const std::set<std::string>& fileExtensions)
{
	std::vector<fs::path> ab;
	fs::path folderPath = path;
	try {
		for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {
			if (fs::is_regular_file(entry)) {
				std::string fileExtension = entry.path().extension().string();
				if (fileExtensions.find(fileExtension) != fileExtensions.end()) {
					ab.push_back(entry.path());
				}
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return ab;
}

void moveFile(const std::string source, const std::string destination) {
	try {
		fs::path sourcePath = source; // Replace with the actual source file path
		fs::path destinationPath = destination; // Replace with the actual destination path

		// Check if the source file exists
		if (fs::exists(sourcePath)) {
			// Create the entire destination directory structure if it doesn't exist
			if (!fs::exists(destinationPath)) {
				fs::create_directories(destinationPath);

			}

			// Append the source file name to the destination path
			destinationPath /= sourcePath.filename();
			fs::rename(sourcePath, destinationPath);
			// Move the file
		   /// fs::copy_file(sourcePath, destinationPath, fs::copy_options::overwrite_existing);
			///check if you have lyric data



			std::cout << "File moved successfully!" << std::endl;
		}
		else {
			std::cerr << "Source file not found." << std::endl;
		}
	}

	catch (const fs::filesystem_error& e) {
		std::cerr << "Filesystem error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void copyFile(std::string source, std::string destination)
{
	try {
		fs::path sourcePath = source; // Replace with the actual source file path
		fs::path destinationDir = destination; // Replace with the actual destination directory path

		// Check if the source file exists
		if (fs::exists(sourcePath)) {
			// Create the destination directory if it doesn't exist
			if (!fs::exists(destinationDir)) {
				fs::create_directories(destinationDir);
			}

			// Construct the destination path by combining the destination directory and the source file name
			fs::path destinationPath = destinationDir / sourcePath.filename();

			// Copy the file
			fs::copy_file(sourcePath, destinationPath);

			std::cout << "File copied successfully!" << std::endl;
		}
		else {
			std::cerr << "Source file not found." << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
