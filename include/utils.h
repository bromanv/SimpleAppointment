#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <regex>

class Utils
{
public:
    template <typename T>
    static void safeInput(T& input, T defaultValue)
    {
        while (!(std::cin >> input))
        {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input, please try again: ";
            input = defaultValue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard any extra input
    }

    static bool isValidDate(const std::string& date);
    static bool isValidTime(const std::string& time);
    static void padTo(std::string &str, const size_t num);
private:
    static bool isLeapYear(int year);
};

#endif // UTILS_H
