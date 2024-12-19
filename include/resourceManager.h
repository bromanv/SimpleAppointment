#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <cstdlib>

/**
 * @class ResourceManager
 * @brief Clase para manejar recursos multilingües.
 *
 * Esta clase proporciona métodos para cargar mensajes de recursos desde archivos,
 * establecer el idioma actual y obtener mensajes por clave.
 */
class ResourceManager
{
public:
    /**
     * @brief Establece el idioma actual.
     * @param language Código del idioma (por ejemplo, "en" para inglés, "es" para español).
     */
    static void setLanguage(const std::string& language);

    /**
     * @brief Obtiene el mensaje correspondiente a una clave.
     * @param key Clave del mensaje.
     * @return Mensaje correspondiente a la clave. Si no se encuentra el mensaje, se devuelve la clave.
     */
    static std::string getMessage(const std::string& key);

    /**
     * @brief Carga los mensajes de un archivo JSON.
     * @param filename Nombre del archivo JSON que contiene los mensajes.
     */
    static void loadMessages(const std::string& filename);

private:
    static std::string currentLanguage;
    static std::unordered_map<std::string, std::unordered_map<std::string, std::string>> messages;
    /**
     * @brief Carga los mensajes desde un archivo JSON.
     * @param filename Nombre del archivo JSON que contiene los mensajes.
     */
    static void loadMessagesFromFile(const std::string& filename);
};

#endif // RESOURCEMANAGER_H
