#include "ResourceManager.h"
#include <fstream>
#include <nlohmann/json.hpp> // Usar JSON para cargar mensajes
#include <iostream>
#include <string>

using json = nlohmann::json;
using namespace std;

string ResourceManager::currentLanguage = "en";
unordered_map<string, unordered_map<string, string>> ResourceManager::messages;

void ResourceManager::setLanguage(const std::string& language)
{
    currentLanguage = language;
}

std::string ResourceManager::getMessage(const std::string& key)
{
    // Verificar si el idioma y la clave existen en el mapa de mensajes
    if (messages.find(currentLanguage) != messages.end() &&
            messages[currentLanguage].find(key) != messages[currentLanguage].end())
    {
        return messages[currentLanguage][key];
    }
    // Devolver la clave si no se encuentra el mensaje
    return key;
}

void ResourceManager::loadMessages(const std::string& filename)
{
    try
    {
        loadMessagesFromFile(filename);
    }
    catch (const ifstream::failure& e)
    {
        cerr << "Error al abrir el archivo de mensajes: " << filename << ". " << e.what() << endl;
    }
    catch (const json::parse_error& e)
    {
        cerr << "Error al parsear el archivo JSON: " << filename << ". " << e.what() << endl;
    }
    catch (const exception& e)
    {
        cerr << "Error inesperado al cargar el archivo de mensajes: " << filename << ". " << e.what() << endl;
    }
}

void ResourceManager::loadMessagesFromFile(const std::string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw ifstream::failure("No se pudo abrir el archivo.");
    }
    json j;
    file >> j;
    for (const auto& lang : j.items())
    {
        for (const auto& message : lang.value().items())
        {
            messages[lang.key()][message.key()] = message.value();
        }
    }
    file.close();
}
