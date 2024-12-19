#ifndef CLIENTSERVICE_H
#define CLIENTSERVICE_H
#include "constants.h"
#include "serviceBase.h"
#include "entities/client.h"
#include <cstdlib>
namespace Project2
{

/**
 * @class ClientService
 * @brief Clase para manejar los servicios relacionados con los clientes.
 */

class ClientService : public ServiceBase<Client>
{
protected:
    /**
     * @brief Método para obtener el nombre del archivo donde se guardan los datos de los clientes.
     * @return Nombre del archivo.
     */
    std::string getFilename() const override
    {
        return Constants::CLIENTS_FILENAME;
    }

    /**
     * @brief Método para obtener el mensaje de éxito después de registrar un cliente.
     * @return Mensaje de éxito.
     */
    std::string getSuccessMessage() const override
    {
        return ResourceManager::getMessage("MESSAGE_CLIENT_REGISTERED");
    }

    /**
     * @brief Método para crear un objeto Client.
     * @return Objeto Client creado.
     */
    Client createObject() override;

    /**
     * @brief Método para obtener y validar la entrada del nombre de la mascota.
     * @return Nombre de la mascota.
     */
    std::string getPetNameInput();

    /**
     * @brief Método para obtener y validar la entrada del tipo de mascota.
     * @return Tipo de mascota.
     */
    PetType getPetTypeInput();

    /**
     * @brief Método para obtener y validar la entrada de la raza de la mascota.
     * @return Raza de la mascota.
     */
    std::string getBreedInput();

    /**
     * @brief Método para obtener y validar la entrada del peso de la mascota.
     * @return Peso de la mascota.
     */
    float getWeightInput();

    /**
     * @brief Método para obtener y validar la entrada de la edad de la mascota.
     * @return Edad de la mascota.
     */
    int getAgeInput();
};
}
#endif // CLIENTSERVICE_H
