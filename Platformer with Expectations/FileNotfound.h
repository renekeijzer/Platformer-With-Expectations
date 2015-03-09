#pragma once 
#include <exception>
#include <string>

class FileNotFound : public std::exception{

public:
	FileNotFound(std::string file) : message(std::string("File not found: " + file)){}
	const char * what(){ return message.c_str(); }
private:	
	std::string message;

};