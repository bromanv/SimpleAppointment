#include "entities/appointment.h"

using namespace std;
using json = nlohmann::json;
using namespace Project2;

string Appointment::toString() const
{
    return  nlohmann::json(*this).dump();
}
Appointment::Appointment()
{
    setValid(false);
}
Appointment::Appointment(int appointmentCode, int clientId, int doctorId, const std::string& date, const std::string& time, const std::string& observation)
    : appointmentCode(appointmentCode), clientId(clientId), doctorId(doctorId), date(date), time(time), observation(observation)
{
    setValid(true);
}

int Appointment::getAppointmentCode() const
{
    return appointmentCode;
}

int Appointment::getClientId() const
{
    return clientId;
}

int Appointment::getDoctorId() const
{
    return doctorId;
}

std::string Appointment::getDate() const
{
    return date;
}

std::string Appointment::getTime() const
{
    return time;
}

std::string Appointment::getObservation() const
{
    return observation;
}

