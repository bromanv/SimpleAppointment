#ifndef DOCTOR_H
#define DOCTOR_H

#include "person.h"
#include <string>
#include <cstdlib>
#include <nlohmann/json.hpp>
namespace Project2
{

/**
 * @enum Speciality
 * @brief Enumeraci�n para las especialidades m�dicas.
 */
enum Speciality
{
    GeneralMedicine,
    Oncology,
    Physiotherapy,
    Wildlife
};
NLOHMANN_JSON_SERIALIZE_ENUM( Speciality,
{
    {GeneralMedicine, 1},
    {Oncology, 2},
    {Physiotherapy, 3},
    {Wildlife, 4}
})
/**
 * @class Doctor
 * @brief Clase que representa a un doctor.
 */
class Doctor : public Person
{
public:
    Doctor();
    /**
     * @brief Constructor de la clase Doctor.
     * @param id N�mero de identificaci�n.
     * @param firstName Nombre.
     * @param lastName Apellido.
     * @param speciality Especialidad.
     */
    Doctor(int id, const std::string& firstName, const std::string& lastName, Speciality speciality);

    // Getters
    Speciality getSpeciality() const;
    std::string getSpecialityDescription() const; // M�todo constante, no modifica el objeto

    // Setters con validaci�n
    void setSpeciality(Speciality speciality);
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Doctor, id, firstName, lastName,speciality);
    /**
     * @brief M�todo toString virtual para convertir a JSON y retornar como cadena.
     * @return Representaci�n JSON de la persona como cadena.
     */
    virtual std::string toString() const;
private:
    Speciality speciality;
    /**
     * @brief Funci�n  para deserializar un objeto Doctor desde un objeto JSON.
     * @param j Objeto JSON desde el cual deserializar.
     * @param c Objeto Doctor que se va a deserializar.
     *
     */
    void from_json(const nlohmann::json& j, Doctor& c);

    /**
     * @brief Funci�n  para serializar un objeto Doctor a un objeto JSON.
     * @param j Objeto JSON al cual serializar.
     * @param c Objeto Doctor que se va a serializar.
     *
     */
    void to_json(nlohmann::json& j, const Doctor& c);
};


}
#endif // DOCTOR_H
