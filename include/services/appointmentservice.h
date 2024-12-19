#ifndef APPOINTMENTSERVICE_H
#define APPOINTMENTSERVICE_H

#include "constants.h"
#include "serviceBase.h"
#include "appointment.h"
#include "fileReaderService.h"
#include "client.h"
#include "doctor.h"
#include <vector>
namespace Project2
{
/**
 * @class AppointmentService
 * @brief Clase para manejar los servicios relacionados con las citas.
 */
class AppointmentService : public ServiceBase<Appointment>
{
protected:
    /**
     * @brief Método para obtener el nombre del archivo donde se guardan los datos de las citas.
     * @return Nombre del archivo.
     */
    std::string getFilename() const override
    {
        return Constants::APPOINTMENTS_FILENAME ;
    }

    /**
     * @brief Método para obtener el mensaje de éxito después de registrar una cita.
     * @return Mensaje de éxito.
     */
    std::string getSuccessMessage() const override
    {
        return ResourceManager::getMessage("MESSAGE_APPOINTMENT_REGISTERED");
    }

    /**
     * @brief Método para crear un objeto Appointment.
     * @return Objeto Appointment creado.
     */
    Appointment createObject() override;

    /**
     * @brief Método para validar y obtener el código de la cita.
     * @param existingCodes Vector con los códigos de citas existentes.
     * @return Código de la cita validado.
     */
    int getAppointmentCodeInput(const std::vector<int>& existingCodes);

    /**
     * @brief Método para validar y obtener la fecha de la cita.
     * @return Fecha de la cita validada.
     */
    std::string getDateInput();

    /**
     * @brief Método para validar y obtener la hora de la cita.
     * @return Hora de la cita validada.
     */
    std::string getTimeInput();

    /**
     * @brief Método para validar y obtener la observación de la cita.
     * @return Observación validada.
     */
    std::string getObservationInput();
    /**
     * @brief Método para validar y obtener el número de cédula.
     * @param prompt Mensaje de solicitud.
     * @param existingIds Vector con los números de cédula existentes.
     * @return Número de cédula validado.
     */
    getIdInputWithRetry(const std::string& prompt, const std::vector<int>& existingIds, std::string error1, std::string erro2);
};
}
#endif // APPOINTMENTSERVICE_H
