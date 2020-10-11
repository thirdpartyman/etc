#pragma once

#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>

std::ostream& operator<< (std::ostream& out, const likee::time& point)
{
	std::time_t time = std::chrono::system_clock::to_time_t(point);

	return out << std::put_time(std::localtime(&time), "%c %Z");
}