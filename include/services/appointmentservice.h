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
     * @brief M�todo para obtener el nombre del archivo donde se guardan los datos de las citas.
     * @return Nombre del archivo.
     */
    std::string getFilename() const override
    {
        return Constants::APPOINTMENTS_FILENAME ;
    }

    /**
     * @brief M�todo para obtener el mensaje de �xito despu�s de registrar una cita.
     * @return Mensaje de �xito.
     */
    std::string getSuccessMessage() const override
    {
        return ResourceManager::getMessage("MESSAGE_APPOINTMENT_REGISTERED");
    }

    /**
     * @brief M�todo para crear un objeto Appointment.
     * @return Objeto Appointment creado.
     */
    Appointment createObject() override;

    /**
     * @brief M�todo para validar y obtener el c�digo de la cita.
     * @param existingCodes Vector con los c�digos de citas existentes.
     * @return C�digo de la cita validado.
     */
    int getAppointmentCodeInput(const std::vector<int>& existingCodes);

    /**
     * @brief M�todo para validar y obtener la fecha de la cita.
     * @return Fecha de la cita validada.
     */
    std::string getDateInput();

    /**
     * @brief M�todo para validar y obtener la hora de la cita.
     * @return Hora de la cita validada.
     */
    std::string getTimeInput();

    /**
     * @brief M�todo para validar y obtener la observaci�n de la cita.
     * @return Observaci�n validada.
     */
    std::string getObservationInput();
    /**
     * @brief M�todo para validar y obtener el n�mero de c�dula.
     * @param prompt Mensaje de solicitud.
     * @param existingIds Vector con los n�meros de c�dula existentes.
     * @return N�mero de c�dula validado.
     */
    getIdInputWithRetry(const std::string& prompt, const std::vector<int>& existingIds, std::string error1, std::string erro2);
};
}
#endif // APPOINTMENTSERVICE_H
