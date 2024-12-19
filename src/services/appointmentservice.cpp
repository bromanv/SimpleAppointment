#include "services/appointmentService.h"
#include "services/fileReaderService.h"
#include "constants.h"
#include "ResourceManager.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <nlohmann/json.hpp>

using namespace std;
using namespace Project2;
using json = nlohmann::json;

Appointment AppointmentService::createObject()
{
    Appointment empty;
    // Leer los códigos de citas existentes
    vector<int> existingCodes;

    // Leer los clientes y doctores existentes
    vector<Client> clients = FileReaderService::readClients(Constants::CLIENTS_FILENAME);
    vector<Doctor> doctors = FileReaderService::readDoctors(Constants::DOCTORS_FILENAME);

    if (clients.empty())
    {
        cout << ResourceManager::getMessage("ERROR_NO_CLIENTS") << endl;
        return empty;
    }

    if (doctors.empty())
    {
        cout << ResourceManager::getMessage("ERROR_NO_DOCTORS") << endl;
        return empty;
    }
    vector<Appointment> appointments = FileReaderService::readAppointments(Constants::APPOINTMENTS_FILENAME);
    if (!appointments.empty())
    {
        for (const Appointment& item : appointments)
        {
            existingCodes.push_back(item.getAppointmentCode());
        }
    }

    // Obtener los IDs de los clientes y doctores existentes
    vector<int> clientIds;
    for (const auto& client : clients)
    {
        clientIds.push_back(client.getId());
    }

    vector<int> doctorIds;
    for (const auto& doctor : doctors)
    {
        doctorIds.push_back(doctor.getId());
    }

    int appointmentCode = getAppointmentCodeInput(existingCodes);
    if (appointmentCode == -1) return empty; // Usuario decidió no continuar
    int clientId = getIdInputWithRetry(ResourceManager::getMessage("PROMPT_CLIENT_ID"), clientIds, ResourceManager::getMessage("ERROR_INVALID_ID"), ResourceManager::getMessage("NOT_FOUND"));
    if (clientId == -1) return empty; // Usuario decidió no continuar

    int doctorId = getIdInputWithRetry(ResourceManager::getMessage("PROMPT_DOCTOR_ID"), doctorIds, ResourceManager::getMessage("ERROR_INVALID_ID"),ResourceManager::getMessage("NOT_FOUND"));
    if (doctorId == -1) return empty; // Usuario decidió no continuar

    string date = getDateInput();
    string time = getTimeInput();
    string observation = getObservationInput();

    return Appointment(appointmentCode, clientId, doctorId, date, time, observation);
}

int AppointmentService::getAppointmentCodeInput(const vector<int>& existingCodes)
{
    while (true)
    {
        int code;
        cout << ResourceManager::getMessage("PROMPT_APPOINTMENT_CODE");
        Utils::safeInput(code, -1);
        if (code >= 1000 && find(existingCodes.begin(), existingCodes.end(), code) == existingCodes.end())
        {
            return code;
        }
        else
        {
            cout << ResourceManager::getMessage("ERROR_INVALID_APPOINTMENT_CODE") << endl;
        }
        char choice;
        cout << ResourceManager::getMessage("PROMPT_RETRY") << " (S/N): ";
        Utils::safeInput(choice, 'N');
        if (toupper(choice) == 'N')
        {
            return -1; // Usuario decidió no continuar
        }
    }
}

string AppointmentService::getDateInput()
{
    while (true)
    {
        string date = getInput(ResourceManager::getMessage("PROMPT_DATE"));
        if (Utils::isValidDate(date))
        {
            return date;
        }
        else
        {
            cout << ResourceManager::getMessage("ERROR_INVALID_DATE") << endl;
        }
    }
}

string AppointmentService::getTimeInput()
{
    while (true)
    {
        string time = getInput(ResourceManager::getMessage("PROMPT_TIME"));
        if (Utils::isValidTime(time))
        {
            return time;
        }
        else
        {
            cout << ResourceManager::getMessage("ERROR_INVALID_TIME") << endl;
        }
    }
}

int AppointmentService::getIdInputWithRetry(const string& prompt, const vector<int>& existingIds, string error1, string erro2)
{
    while (true)
    {
        int id;
        cout << prompt;
        Utils::safeInput(id, -1);
        if (id <= 100000000 || id >= 999999999)
        {
            cout << error1 << endl;
        }
        else if(find(existingIds.begin(), existingIds.end(), id) == existingIds.end())
        {
            cout << erro2 << endl;
        }
        else
        {
            return id;
        }
        char choice;
        cout << ResourceManager::getMessage("PROMPT_RETRY") << " (S/N): ";
        Utils::safeInput(choice, 'N');
        if (toupper(choice) == 'N')
        {
            return -1; // Usuario decidió no continuar
        }
    }
}

string AppointmentService::getObservationInput()
{
    return getInput(ResourceManager::getMessage("PROMPT_OBSERVATION"));
}
