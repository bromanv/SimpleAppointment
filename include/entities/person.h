#ifndef PERSON_H
#define PERSON_H

#include "entitybase.h"
#include <string>
#include <nlohmann/json.hpp>
namespace Project2
{
/**
 * @class Person
 * @brief Clase base para representar una persona.
 */
class Person: public EntityBase
{
public:
    Person();
    /**
     * @brief Constructor de la clase Person.
     * @param id Número de identificación.
     * @param firstName Nombre.
     * @param lastName Apellido.
     */
    Person(int id, const std::string& firstName, const std::string& lastName);

    // Getters
    //Cuando ves const al final de un método, significa que el método no puede modificar ningún dato miembro de la clase.
    //El método es de solo lectura y garantiza que no alterará el estado del objeto.

    std::string getFullName() const;
    std::string getFirstName() const;
    std::string getLastName() const;

    // Setters con validación
    void setId(int id) override;
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Person, id, firstName, lastName);
    /**
         * @brief Método toString virtual para convertir a JSON y retornar como cadena.
         * @return Representación JSON de la persona como cadena.
         */
    virtual std::string toString() const;
protected:
    std::string firstName;
    std::string lastName;
};
}
#endif // PERSON_H
