#ifndef CLIENT_H
#define CLIENT_H

#include "person.h"
#include <string>
#include <cstdlib>
#include <nlohmann/json.hpp>

namespace Project2
{
/**
 * @enum PetType
 * @brief Enumeraci�n para los tipos de mascota.
 */
enum PetType
{
    Cat,
    Dog
};
NLOHMANN_JSON_SERIALIZE_ENUM( PetType,
{
    {Cat, 1},
    {Dog, 2}
})
/**
 * @class Client
 * @brief Clase que representa a un cliente.
 */
class Client : public Person
{
public:
    Client();
    /**
     * @brief Constructor de la clase Client.
     * @param id N�mero de identificaci�n.
     * @param ownerFirstName Nombre del due�o.
     * @param ownerLastName Apellido del due�o.
     * @param petName Nombre de la mascota.
     * @param petType Tipo de mascota.
     * @param breed Raza de la mascota.
     * @param weight Peso de la mascota.
     * @param age Edad de la mascota.
     */
    Client(int id, const std::string& ownerFirstName, const std::string& ownerLastName, const std::string& petName, PetType petType, const std::string& breed, float weight, int age);

    // Getters
    std::string getPetName() const; // M�todo constante, no modifica el objeto
    PetType getPetType() const; // M�todo constante, no modifica el objeto
    std::string getBreed() const; // M�todo constante, no modifica el objeto
    float getWeight() const; // M�todo constante, no modifica el objeto
    int getAge() const; // M�todo constante, no modifica el objeto
    std::string getPetTypeDescription() const; // M�todo constante, no modifica el objeto

    // Setters con validaci�n
    void setPetName(const std::string& petName);
    void setPetType(PetType petType);
    void setBreed(const std::string& breed);
    void setWeight(float weight);
    void setAge(int age);

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Client, id, firstName, lastName,petName,petType,breed,weight,age);
    /**
     * @brief M�todo toString virtual para convertir a JSON y retornar como cadena.
     * @return Representaci�n JSON de la persona como cadena.
     */
    virtual std::string toString() const;
private:
    std::string petName;
    PetType petType;
    std::string breed;
    float weight;
    int age;

};

}


#endif // CLIENT_H
