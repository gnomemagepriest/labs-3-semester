#include "Logger.h"

Logger::Logger() {
	
}

void Logger::addLine(std::string newLine) {
	if (newLine[newLine.size() - 1] != '\n') {
		newLine += '\n';
	}
	logs.push_back(newLine);
}

std::string Logger::getLastEvents() {
	if (logs.empty())
		return "";

	std::string result;
	
	try {
		std::string result = logs[logs.size() - 2];
	}
	catch (...) {
		
	}

	result += logs[logs.size() - 1];

	return result;
}
