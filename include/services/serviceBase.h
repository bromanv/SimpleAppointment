#ifndef SERVICEBASE_H
#define SERVICEBASE_H

#include "ResourceManager.h"
#include "inull.h"
#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp> // Biblioteca para manejo de JSON

using json = nlohmann::json;

namespace Project2
{
/**
 * @class ServiceBase
 * @brief Clase plantilla base para manejar servicios de registro de objetos.
 */
template <typename T>
class ServiceBase
{

public:
    /**
     * @brief M�todo para registrar un objeto.
     */
    void registerObject();

protected:
    /**
     * @brief M�todo virtual puro para obtener el nombre del archivo.
     * @return Nombre del archivo.
     */
    virtual std::string getFilename() const = 0;

    /**
     * @brief M�todo virtual puro para obtener el mensaje de �xito.
     * @return Mensaje de �xito.
     */
    virtual std::string getSuccessMessage() const = 0;

    /**
     * @brief M�todo virtual puro para crear el objeto.
     * @return Objeto creado.
     */
    virtual T createObject()=0;

    /**
     * @brief M�todos auxiliares para solicitar y validar datos.
     * @param prompt Mensaje de solicitud.
     * @return Entrada del usuario.
     */
    std::string getInput(const std::string& prompt);

    /**
     * @brief M�todo para solicitar y validar el ID.
     * @return ID validado.
     */
    int getIdInput();

    /**
     * @brief M�todo para solicitar y validar el primer nombre.
     * @return Primer nombre validado.
     */
    std::string getFirstNameInput();

    /**
     * @brief M�todo para solicitar y validar el apellido.
     * @return Apellido validado.
     */
    std::string getLastNameInput();

    /**
     * @brief M�todo para guardar los datos del objeto en un archivo.
     * @param obj Objeto a guardar.
     */
    void saveObjectToFile(const T& obj);
};

template <typename T>
void ServiceBase<T>::registerObject()
{
    try
    {
        T obj = createObject();
        if (obj.isValid())
        {
            saveObjectToFile(obj);
            std::cout << getSuccessMessage();
        }
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (const std::exception& e)      // Captura de excepci�n base para imprimir el mensaje de what()
    {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << ResourceManager::getMessage("MESSAGE_UNEXPECTED_ERROR");
    }
}

template <typename T>
void ServiceBase<T>::saveObjectToFile(const T& obj)
{
    json j;

    // Leer el contenido existente del archivo
    std::ifstream inFile(getFilename());
    if (inFile.is_open())
    {
        try
        {
            inFile >> j;
        }
        catch (const json::parse_error&)
        {
            // Si el archivo est� vac�o o no es un JSON v�lido, inicializamos como un arreglo vac�o
            j = json::array();
        }
        inFile.close();
    }
    else
    {
        // Si el archivo no existe o no se puede abrir, inicializamos el JSON como un arreglo vac�o
        j = json::array();
    }

    // Convertir el objeto a JSON y agregarlo al arreglo
    j.push_back(json::parse(obj.toString()));

    // Escribir todo el contenido de nuevo al archivo
    std::ofstream outFile(getFilename());
    if (outFile.is_open())
    {
        outFile << j.dump(4) << std::endl; // Formateamos el JSON con una indentaci�n de 4 espacios
        outFile.close();
    }
    else
    {
        std::cerr << ResourceManager::getMessage("MESSAGE_FILE_ERROR");
    }
}

template <typename T>
std::string ServiceBase<T>::getInput(const std::string& prompt)
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

template <typename T>
int ServiceBase<T>::getIdInput()
{
    while (true)
    {
        try
        {
            std::string input = getInput(ResourceManager::getMessage("PROMPT_ID"));
            // https://en.cppreference.com/w/cpp/string/basic_string/stol
            int id = std::stol(input);
            if (id < 100000000 || id > 999999999)
            {
                throw std::invalid_argument(ResourceManager::getMessage("ERROR_INVALID_ID"));
            }
            return id;
        }
        catch (const std::invalid_argument&)
        {
            std::cerr << ResourceManager::getMessage("ERROR_INVALID_ID") << std::endl;
        }
    }
}

template <typename T>
std::string ServiceBase<T>::getFirstNameInput()
{
    while (true)
    {
        std::string input = getInput(ResourceManager::getMessage("PROMPT_FIRST_NAME"));
        if (!input.empty())
        {
            return input;
        }
        else
        {
            std::cerr << ResourceManager::getMessage("ERROR_EMPTY_FIRST_NAME") << std::endl;
        }
    }
}

template <typename T>
std::string ServiceBase<T>::getLastNameInput()
{
    while (true)
    {
        std::string input = getInput(ResourceManager::getMessage("PROMPT_LAST_NAME"));
        if (!input.empty())
        {
            return input;
        }
        else
        {
            std::cerr << ResourceManager::getMessage("ERROR_EMPTY_LAST_NAME") << std::endl;
        }
    }
}

}
#endif // SERVICEBASE_H
