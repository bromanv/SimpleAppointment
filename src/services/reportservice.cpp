#include "reportService.h"
#include "services/fileReaderService.h"
#include "ResourceManager.h"
#include "constants.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <iomanip>
#include <cctype>  // para std::toupper

using namespace Project2;
using json = nlohmann::json;

void ReportService::generateReportByDoctor() const
{
    while (true)
    {
        int doctorId;
        std::cout << ResourceManager::getMessage("ENTER_DOCTOR_ID");
        Utils::safeInput(doctorId, 0);

        // Leer datos desde los archivos
        std::vector<Appointment> appointments = readAppointments(Constants::APPOINTMENTS_FILENAME);
        std::vector<Client> clients = readClients(Constants::CLIENTS_FILENAME);
        std::vector<Doctor> doctors = readDoctors(Constants::DOCTORS_FILENAME);

        // Obtener el doctor por ID
        Doctor doctor = getDoctorById(doctorId, doctors);
        if (doctor.getId() == -1)
        {
            std::cout << ResourceManager::getMessage("NO_DOCTOR_FOUND") << std::endl;
            char choice;
            std::cout << ResourceManager::getMessage("PROMPT_RETRY") << " (S/N): ";
            Utils::safeInput(choice, 'N');
            if (std::toupper(choice) != 'S')
            {
                return;  // Termina el método si el usuario no desea reintentar
            }
            continue;  // Reintentar el ingreso del ID del doctor
        }

        // Filtrar citas por doctorId
        std::vector<Appointment> doctorAppointments;
        std::copy_if(appointments.begin(), appointments.end(), std::back_inserter(doctorAppointments),
                     [doctorId](const Appointment& appointment)
        {
            return appointment.getDoctorId() == doctorId;
        });

        if (doctorAppointments.empty())
        {
            std::cout << ResourceManager::getMessage("NO_APPOINTMENTS_FOUND") << std::endl;
        }
        else
        {
            printReport(ResourceManager::getMessage("REPORT_TITLE_DOCTOR"), "DOCTOR_ID", "DOCTOR_NAME", doctorId, doctor.getFullName(), doctorAppointments, clients);
        }
        return;  // Termina el método después de generar el reporte
    }
}

void ReportService::generateReportByClient() const
{
    while (true)
    {
        int clientId;
        std::cout << ResourceManager::getMessage("ENTER_CLIENT_ID");
        Utils::safeInput(clientId, 0);

        // Leer datos desde los archivos
        std::vector<Appointment> appointments = readAppointments(Constants::APPOINTMENTS_FILENAME);
        std::vector<Client> clients = readClients(Constants::CLIENTS_FILENAME);
        std::vector<Doctor> doctors = readDoctors(Constants::DOCTORS_FILENAME);

        // Obtener el cliente por ID
        Client client = getClientById(clientId, clients);
        if (client.getId() == -1)
        {
            std::cout << ResourceManager::getMessage("NO_CLIENT_FOUND") << std::endl;
            char choice;
            std::cout << ResourceManager::getMessage("PROMPT_RETRY") << " (S/N): ";
            Utils::safeInput(choice, 'N');
            if (std::toupper(choice) != 'S')
            {
                return;  // Termina el método si el usuario no desea reintentar
            }
            continue;  // Reintentar el ingreso del ID del cliente
        }

        // Filtrar citas por clientId
        std::vector<Appointment> clientAppointments;
        std::copy_if(appointments.begin(), appointments.end(), std::back_inserter(clientAppointments),
                     [clientId](const Appointment& appointment)
        {
            return appointment.getClientId() == clientId;
        });

        if (clientAppointments.empty())
        {
            std::cout << ResourceManager::getMessage("NO_APPOINTMENTS_FOUND") << std::endl;
        }
        else
        {
            printReport(ResourceManager::getMessage("REPORT_TITLE_CLIENT"), "CLIENT_ID", "CLIENT_NAME", clientId, client.getFullName(), clientAppointments, clients);
        }
        return;  // Termina el método después de generar el reporte
    }
}

std::vector<Appointment> ReportService::readAppointments(const std::string& filename) const
{
    return FileReaderService::readAppointments(filename);
}

std::vector<Client> ReportService::readClients(const std::string& filename) const
{
    return FileReaderService::readClients(filename);
}

std::vector<Doctor> ReportService::readDoctors(const std::string& filename) const
{
    return FileReaderService::readDoctors(filename);
}

Doctor ReportService::getDoctorById(int doctorId, const std::vector<Doctor>& doctors) const
{
    auto it = std::find_if(doctors.begin(), doctors.end(), [doctorId](const Doctor& doctor)
    {
        return doctor.getId() == doctorId;
    });
    return it != doctors.end() ? *it : Doctor();
}

Client ReportService::getClientById(int clientId, const std::vector<Client>& clients) const
{
    auto it = std::find_if(clients.begin(), clients.end(), [clientId](const Client& client)
    {
        return client.getId() == clientId;
    });
    return it != clients.end() ? *it : Client();
}

void ReportService::drawSeparator(const int columnWidths[], int numColumns) const
{
    for (int i = 0; i < numColumns; ++i)
    {
        std::cout << "+";
        for (int j = 0; j < columnWidths[i] + 2; ++j)
        {
            std::cout << "-";
        }
    }
    std::cout << "+" << std::endl;
}

void ReportService::drawRow(const std::vector<std::string>& row, const int columnWidths[], int numColumns) const
{
    for (int i = 0; i < numColumns; ++i)
    {
        int padding = (columnWidths[i] - row[i].length()) / 2;
        std::cout << "| " << std::setw(padding) << "" << std::left << std::setw(columnWidths[i] - padding) << row[i] << " ";
    }
    std::cout << "|" << std::endl;
}

void ReportService::printReport(const std::string& title, const std::string& idLabel, const std::string& nameLabel,
                                int id, const std::string& name, const std::vector<Appointment>& appointments,
                                const std::vector<Client>& clients) const
{
    // Definir anchos de columna
    static constexpr int APPOINTMENT_NUM_WIDTH = 12;
    static constexpr int DATE_WIDTH = 10;
    static constexpr int TIME_WIDTH = 10;
    static constexpr int PET_NAME_WIDTH = 16;
    static constexpr int PET_TYPE_WIDTH = 16;
    static constexpr int OBSERVATION_WIDTH = 36;
    static constexpr int NUM_COLUMNS = 6;
    const int columnWidths[NUM_COLUMNS] = { APPOINTMENT_NUM_WIDTH, DATE_WIDTH, TIME_WIDTH, PET_NAME_WIDTH, PET_TYPE_WIDTH, OBSERVATION_WIDTH };

    int totalWidth = APPOINTMENT_NUM_WIDTH + DATE_WIDTH + TIME_WIDTH + PET_NAME_WIDTH + PET_TYPE_WIDTH + OBSERVATION_WIDTH + NUM_COLUMNS * 2 + 2;
    int headerColumnWidths[NUM_COLUMNS] = { totalWidth };

    // Imprimir encabezados del reporte
    drawRow(std::vector<std::string> {title}, headerColumnWidths, 1);
    drawSeparator(headerColumnWidths, 1);
    std::string strLine = ResourceManager::getMessage(idLabel) + ": " + std::to_string(id);
    Utils::padTo(strLine, totalWidth - 2);
    drawRow(std::vector<std::string> {strLine}, headerColumnWidths, 1);

    strLine = ResourceManager::getMessage(nameLabel) + ": " + name;
    Utils::padTo(strLine, totalWidth - 2);
    drawRow(std::vector<std::string> {strLine}, headerColumnWidths, 1);

    drawSeparator(headerColumnWidths, 1);
    // Imprimir encabezados de la tabla
    std::vector<std::string> headers =
    {
        ResourceManager::getMessage("APPOINTMENT_NUM"),
        ResourceManager::getMessage("DATE_TITLE"),
        ResourceManager::getMessage("TIME_TITLE"),
        ResourceManager::getMessage("PET_NAME"),
        ResourceManager::getMessage("PET_TYPE"),
        ResourceManager::getMessage("OBSERVATION")
    };

    drawSeparator(columnWidths, NUM_COLUMNS);
    drawRow(headers, columnWidths, NUM_COLUMNS);
    drawSeparator(columnWidths, NUM_COLUMNS);

    // Imprimir citas
    for (const auto& appointment : appointments)
    {
        Client client = getClientById(appointment.getClientId(), clients);
        std::string petName = client.getPetName();
        std::string petTypeDescription = client.getPetTypeDescription();
        std::string observation = appointment.getObservation();

        // Dividir el texto en líneas si excede el ancho máximo
        std::string date = appointment.getDate();
        std::string time = appointment.getTime();
        std::string petNameLine = petName.substr(0, PET_NAME_WIDTH);
        std::string petTypeLine = petTypeDescription.substr(0, PET_TYPE_WIDTH);
        std::string observationLine = observation.substr(0, OBSERVATION_WIDTH);
        int appointmentNum = appointment.getAppointmentCode();

        while (!petName.empty() || !petTypeDescription.empty() || !observation.empty())
        {
            std::vector<std::string> row =
            {
                std::to_string(appointmentNum),
                date,
                time,
                petNameLine,
                petTypeLine,
                observationLine
            };
            drawRow(row, columnWidths, NUM_COLUMNS);

            // Actualizar el texto para la siguiente línea
            petName = petName.length() > PET_NAME_WIDTH ? petName.substr(PET_NAME_WIDTH) : "";
            petTypeDescription = petTypeDescription.length() > PET_TYPE_WIDTH ? petTypeDescription.substr(PET_TYPE_WIDTH) : "";
            observation = observation.length() > OBSERVATION_WIDTH ? observation.substr(OBSERVATION_WIDTH) : "";

            date = "";

            time = "";
            petNameLine = petName.substr(0, PET_NAME_WIDTH);
            petTypeLine = petTypeDescription.substr(0, PET_TYPE_WIDTH);
            observationLine = observation.substr(0, OBSERVATION_WIDTH);
        }
        drawSeparator(columnWidths, NUM_COLUMNS);
    }
}
