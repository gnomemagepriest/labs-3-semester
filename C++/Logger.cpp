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
    if (logs.size() >= 2) {
        result += logs[logs.size() - 2]; // Добавляем предпоследний элемент и перенос строки
    }
    result += logs[logs.size() - 1];

    return result;
}