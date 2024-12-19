#ifndef REPORTSERVICE_H
#define REPORTSERVICE_H

#include "entities/appointment.h"
#include "entities/client.h"
#include "entities/doctor.h"
#include <vector>
#include <string>

namespace Project2
{

class ReportService
{
public:
    void generateReportByDoctor() const;
    void generateReportByClient() const;

private:
    std::vector<Appointment> readAppointments(const std::string& filename) const;
    std::vector<Client> readClients(const std::string& filename) const;
    std::vector<Doctor> readDoctors(const std::string& filename) const;
    void printReport(const std::string& title, const std::string& idLabel, const std::string& nameLabel,
                     int id, const std::string& name, const std::vector<Appointment>& appointments,
                     const std::vector<Client>& clients) const;
    Doctor getDoctorById(int doctorId, const std::vector<Doctor>& doctors) const;
    Client getClientById(int clientId, const std::vector<Client>& clients) const;

    // Funciones auxiliares para dibujar la tabla
    void drawSeparator(const int columnWidths[], int numColumns) const;
    void drawRow(const std::vector<std::string>& row, const int columnWidths[], int numColumns) const;
};

} // namespace Project2

#endif // REPORTSERVICE_H
