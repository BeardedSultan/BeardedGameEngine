#pragma once

#include <string>
//#include <fstream>

namespace beardedGameEngine {

	std::string read_file(const char* filepath)
	{
		FILE* file = fopen(filepath, "rt"); //read text file
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char* data = new char[length + 1]; //+1 for termination character
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}

}
