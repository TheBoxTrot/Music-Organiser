#include "ConfigReader.h"
#include <iostream>
#include <fstream>
#include <filesystem>
std::map<std::string, std::string> config;
std::map<std::string, std::string> ReadConfig()
{
	
	std::ifstream configFile("config.txt");
	if (!configFile.is_open()) {

		std::cerr << "Failed to open the configuration file." << std::endl;
		exit(-1);
	}
	std::string line;
	while (std::getline(configFile, line)) 
	{
		size_t delimiterPos = line.find("=");
		std::string key = line.substr(0, delimiterPos);
		std::string value = line.substr(delimiterPos + 1);

		// Trim leading and trailing whitespaces
		key.erase(0, key.find_first_not_of(" \t"));
		key.erase(key.find_last_not_of(" \t") + 1);
		value.erase(0, value.find_first_not_of(" \t"));
		value.erase(value.find_last_not_of(" \t") + 1);

		// Store the key-value pair in the configuration map
		config[key] = value;
		
	}
	configFile.close();

	// Access configuration values
	
	for (const auto& pair : config) {
		const std::string& key = pair.first;
		const std::string& value = pair.second;
		std::cout << "Key: " << key << ", Value: " << value << std::endl;
	}
	return config;
}

bool doesConfigExist()
{
	std::filesystem::path filePath = "config.txt";

	// Check if the file exists
	if (std::filesystem::exists(filePath)) {
		return true;
	}
	else {
		return false;
	}
}

void createDefaultConfig()
{
	// Open a file named "example.txt" in write mode
	std::ofstream file("config.txt");

	// Check if the file is opened successfully
	if (file.is_open()) {
		// Write some content to the file
		file << "FileTypes = .mp3,.flac\n";
		file << "Copyinstead of move = false\n";
		file << "Dir layout = `ALBUMARTIST`/`ALBUM` (`YEAR`)/\n";
		

		// Close the file
		file.close();
		std::cout << "File created successfully.\n";
	}
	else {
		// Print an error message if the file couldn't be opened
		std::cerr << "Error: Unable to create the file.\n";
	}
}
