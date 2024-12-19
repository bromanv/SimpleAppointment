#include "entities/doctor.h"
#include "ResourceManager.h"
#include <stdexcept>

using namespace std;
using json = nlohmann::json;
using namespace Project2;

string Doctor::toString() const
{
    return  nlohmann::json(*this).dump();
}

Doctor::Doctor()
{
    setValid(false);
}
// Constructor de la clase Doctor
Doctor::Doctor(int id, const string& firstName, const string& lastName, Speciality speciality)
    : Person(id, firstName, lastName)
{
    setSpeciality(speciality);
    setValid(true);
}

// Getter para la especialidad
Speciality Doctor::getSpeciality() const
{
    return speciality;
}

// Getter para la descripción de la especialidad
string Doctor::getSpecialityDescription() const
{
    switch (speciality)
    {
    case Speciality::GeneralMedicine:
        return ResourceManager::getMessage("DOCTOR_SPECIALITY_GENERAL");
    case Speciality::Oncology:
        return ResourceManager::getMessage("DOCTOR_SPECIALITY_ONCOLOGY");
    case Speciality::Physiotherapy:
        return ResourceManager::getMessage("DOCTOR_SPECIALITY_PHYSIOTHERAPY");
    case Speciality::Wildlife:
        return ResourceManager::getMessage("DOCTOR_SPECIALITY_WILDLIFE");
    default:
        throw invalid_argument(ResourceManager::getMessage("ERROR_INVALID_SPECIALITY"));
    }
}

// Setter para la especialidad
void Doctor::setSpeciality(Speciality speciality)
{
    this->speciality = speciality;
}
