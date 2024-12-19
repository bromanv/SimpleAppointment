#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "entitybase.h"
#include <string>
#include <nlohmann/json.hpp>

namespace Project2
{
/**
 * @class Appointment
 * @brief Clase que representa una cita.
 */
class Appointment : public EntityBase
{
public:
    Appointment();
    /**
     * @brief Constructor de la clase Appointment.
     * @param appointmentCode C�digo de la cita.
     * @param clientId N�mero de c�dula del due�o o encargado de la mascota.
     * @param doctorId N�mero de c�dula del doctor.
     * @param date Fecha de la cita en formato DD/MM/YYYY.
     * @param time Hora de la cita en formato ##:## AM/PM.
     * @param observation Observaci�n de la cita.
     */
    Appointment(int appointmentCode, int clientId, int doctorId, const std::string& date, const std::string& time, const std::string& observation);

    // Getters
    int getAppointmentCode() const;
    int getClientId() const;
    int getDoctorId() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getObservation() const;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Appointment, id, appointmentCode, clientId,doctorId,date,time,observation);
    /**
     * @brief M�todo toString virtual para convertir a JSON y retornar como cadena.
     * @return Representaci�n JSON de la persona como cadena.
     */
    virtual std::string toString() const;
private:
    int appointmentCode;
    int clientId;
    int doctorId;
    std::string date;
    std::string time;
    std::string observation;
};

}
#endif // APPOINTMENT_H
