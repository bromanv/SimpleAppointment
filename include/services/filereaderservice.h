#ifndef FILEREADERSERVICE_H
#define FILEREADERSERVICE_H

#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "entities/client.h"
#include "entities/doctor.h"
#include "entities/appointment.h"
namespace Project2
{

/**
 * @class FileReaderService
 * @brief Servicio para leer archivos JSON y convertir su contenido a vectores de objetos espec�ficos.
 */
class FileReaderService
{
public:
    /**
     * @brief Lee un archivo y convierte su contenido a un vector de objetos Client.
     * @param filename Nombre del archivo a leer.
     * @return Vector de objetos Client le�dos del archivo.
     */
    static std::vector<Client> readClients(const std::string& filename);

    /**
     * @brief Lee un archivo y convierte su contenido a un vector de objetos Doctor.
     * @param filename Nombre del archivo a leer.
     * @return Vector de objetos Doctor le�dos del archivo.
     */
    static std::vector<Doctor> readDoctors(const std::string& filename);

    /**
     * @brief Lee un archivo y convierte su contenido a un vector de objetos Appointment.
     * @param filename Nombre del archivo a leer.
     * @return Vector de objetos Appointment le�dos del archivo.
     */
    static std::vector<Appointment> readAppointments(const std::string& filename);
private:
    static bool checkFileNotEmpty(std::ifstream& inFile);
};
}
#endif // FILEREADERSERVICE_H
