#include "services/fileReaderService.h"
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace Project2;

std::vector<Client> FileReaderService::readClients(const std::string& filename)
{
    std::vector<Client> clients;
    std::ifstream inFile(filename);
    if (inFile.is_open() && checkFileNotEmpty(inFile))
    {
        json j;
        inFile >> j;
        inFile.close();

        for (const auto& item : j.items())
        {
            Client c;
            from_json(item.value(), c); // Utiliza la función from_json definida en Client
            clients.push_back(c);
        }

    }
    return clients;

}

std::vector<Doctor> FileReaderService::readDoctors(const std::string& filename)
{
    std::vector<Doctor> doctors;
    std::ifstream inFile(filename);
    if (inFile.is_open() && checkFileNotEmpty(inFile))
    {
        json j;
        inFile >> j;
        inFile.close();

        for (const auto& item : j.items())
        {
            Doctor d;
            from_json(item.value(), d); // Utiliza la función from_json definida en Doctor
            doctors.push_back(d);
        }
    }
    return doctors;
}

std::vector<Appointment> FileReaderService::readAppointments(const std::string& filename)
{
    std::vector<Appointment> appointments;
    std::ifstream inFile(filename);
    if (inFile.is_open() && checkFileNotEmpty(inFile))
    {
        json j;
        inFile >> j;
        inFile.close();

        for (const auto& item : j.items())
        {
            Appointment a;
            from_json(item.value(), a); // Utiliza la función from_json definida en Appointment
            appointments.push_back(a);
        }
    }

    return appointments;
}
bool FileReaderService::checkFileNotEmpty(std::ifstream& inFile)
{
    inFile.seekg(0, std::ios::end);
    if (inFile.tellg() == 0)
    {
        return false;
    }
    inFile.seekg(0, std::ios::beg);
    return true;
}
