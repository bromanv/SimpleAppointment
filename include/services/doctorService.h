#ifndef DOCTORSERVICE_H
#define DOCTORSERVICE_H

#include "constants.h"
#include "serviceBase.h"
#include "entities/doctor.h"
#include <cstdlib>
namespace Project2
{

/**
 * @class DoctorService
 * @brief Clase para manejar los servicios relacionados con los doctores.
 */
class DoctorService : public ServiceBase<Doctor>
{
protected:
    /**
     * @brief Método para obtener el nombre del archivo donde se guardan los datos de los doctores.
     * @return Nombre del archivo.
     */
    std::string getFilename() const override
    {
        return Constants::DOCTORS_FILENAME;
    }

    /**
     * @brief Método para obtener el mensaje de éxito después de registrar un doctor.
     * @return Mensaje de éxito.
     */
    std::string getSuccessMessage() const override
    {
        return ResourceManager::getMessage("MESSAGE_DOCTOR_REGISTERED");
    }

    /**
     * @brief Método para crear un objeto Doctor.
     * @return Objeto Doctor creado.
     */
    Doctor createObject() override;

    /**
     * @brief Método para obtener y validar la entrada de la especialidad del doctor.
     * @return Especialidad del doctor.
     */
    Speciality getSpecialityInput();
};
}
#endif // DOCTORSERVICE_H
