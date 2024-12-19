#include "utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <sstream>

using namespace std;

bool Utils::isValidDate(const std::string& date)
{
    std::regex datePattern(R"((0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/([0-9]{4}))");
    if (!std::regex_match(date, datePattern))
    {
        return false;
    }

    std::istringstream iss(date);
    std::string dayStr, monthStr, yearStr;
    std::getline(iss, dayStr, '/');
    std::getline(iss, monthStr, '/');
    std::getline(iss, yearStr, '/');

    int day = std::stoi(dayStr);
    int month = std::stoi(monthStr);
    int year = std::stoi(yearStr);

    if (month == 2)
    {
        if (isLeapYear(year))
        {
            return day <= 29;
        }
        else
        {
            return day <= 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return day <= 30;
    }
    else
    {
        return day <= 31;
    }
}

bool Utils::isValidTime(const std::string& time)
{
    std::regex timePattern(R"((0[1-9]|1[0-2]):[0-5][0-9] (AM|PM))");
    if (!std::regex_match(time, timePattern))
    {
        return false;
    }

    int hour = std::stoi(time.substr(0, 2));
    int minute = std::stoi(time.substr(3, 2));
    std::string period = time.substr(6, 2);

    // Validar si la hora está dentro del rango permitido
    if ((period == "AM" && hour >= 7 && hour <= 11) ||
            (period == "PM" && ((hour == 12) || (hour >= 1 && hour < 7))))
    {
        return true;
    }

    // Exactamente las 7:00 PM es válido, pero no otras horas cercanas a 7 PM.
    if (period == "PM" && hour == 7 && minute == 0)
    {
        return true;
    }

    return false;
}

bool Utils::isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
void Utils::padTo(std::string &str, const size_t num)
{
    char paddingChar = ' ';
    if(num > str.size())
        str.insert(str.size(), num - str.size(), paddingChar);
}

