#include "../../public/Logger/RdrLogger.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <iosfwd>
#include <sstream>
#include "../../public/native/types.h"
#include <mutex>

std::ofstream file;


std::unordered_map<std::string, RdrLogger*> RdrLogger::instances;

RdrLogger::RdrLogger(const char* fileName, LogLevel level)
{
	set_file_name(fileName);
	this->level_ = level;
}

void RdrLogger::info(const char* msg)
{
	this->log(msg, LogLevel::INFO);
}

void RdrLogger::info(stringstream str)
{
	info(str.str().c_str());
}

void RdrLogger::debug(const char* str)
{
	this->log(str, LogLevel::DEBUG);
}

void RdrLogger::warning(const char* msg)
{
	this->log(msg, LogLevel::WARNING);
}

void RdrLogger::fatal(const char* msg)
{
	this->log(msg, LogLevel::FATAL);
}

void RdrLogger::log_vector(Vector3 vector)
{
	stringstream position;
	position << "Vector is { X = " << vector.x << ", Y = " << vector.y << ", Z = " << vector.z;
	this->info(position.str().c_str());
	
}

RdrLogger *RdrLogger::get_logger(const char* fileName, LogLevel level)
{
	std::string file_name_as_string(fileName); 
	auto it = instances.find(file_name_as_string);
	if (it == instances.end())
	{
		it = instances.emplace(file_name_as_string, new RdrLogger(fileName, level)).first;
	}
	
	return it->second;
}

void RdrLogger::raw_write_to_log(const char* msg)
{
	{
		std::lock_guard<std::mutex> lock(log_mutex_);
		file.open(this->file_name, std::ios_base::app);
		if (file.is_open())
		{
			file << msg << "\n";
			file.close();
		}
	}	
}

void RdrLogger::write_to_log(const char* msg)
{
	auto nowTimestamp = std::chrono::system_clock::now();
	auto nowTime = std::chrono::system_clock::to_time_t(nowTimestamp);
	auto nowMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(nowTimestamp.time_since_epoch()).count() % 1000;

    tm now;
    localtime_s(&now, &nowTime);

	std::stringstream txt;
    txt << std::setfill('0') << std::setw(2) << now.tm_mday
        << "/" << std::setfill('0') << std::setw(2) << now.tm_mon + 1 // tm_mon is 0-based
        << "/" << now.tm_year + 1900
        << " " << std::setfill('0') << std::setw(2) << now.tm_hour
        << ":" << std::setfill('0') << std::setw(2) << now.tm_min
        << ":" << std::setfill('0') << std::setw(2) << now.tm_sec
		<< "." << std::setfill('0') << std::setw(3) << nowMilliseconds
		<< " " << msg;

	raw_write_to_log(txt.str().c_str());
}

std::string RdrLogger::getLogLevelString(LogLevel level)
{
	switch (level) {
	case LogLevel::INFO:
		return "INFO";
	case LogLevel::WARNING:
		return "WARNING";
	case LogLevel::FATAL:
		return "FATAL";
	case LogLevel::DEBUG:
		return "DEBUG";
	default:
		return "UNKNOWN";
	}
}

void RdrLogger::log(const char* msg, LogLevel level)
{
	if (!file)
	{
		return;
	}
	if (level >= this->level_)
	{
		stringstream msg_stream;
		msg_stream << getLogLevelString(level) << " " << msg;
		write_to_log(msg_stream.str().c_str());			
	}
}

void RdrLogger::log(Vector3 position, LogLevel level)
{
	std::stringstream output;
	output << position.x << ", " << position.y << ", " << position.z;
	log(output.str().c_str(), level);	
}

void RdrLogger::log(string msg, LogLevel level)
{
	log(msg.c_str(), level);
}

void RdrLogger::set_level(LogLevel level)
{
	this->level_ = level;
}

void RdrLogger::set_file_name(const char* fileName)
{
	this->file_name = fileName;
}

void displayDebugText(const char* text, float offset)
{
	UIDEBUG::_BG_SET_TEXT_SCALE(0.3f, 0.3f);
	UIDEBUG::_BG_DISPLAY_TEXT((char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text), 0, 0.1);
}