#include "menu.h"       // Incluimos el archivo de encabezado de la clase Menu
#include "constants.h"  // Incluimos el archivo de encabezado que contiene las constantes utilizadas
#include "utils.h"
#include <iostream>
#include <map>
#include <functional>
#include <cstdlib>
#include <limits> // This is important!

using namespace std;


//Esta clase no es un plagio la hice buscando conceptos como KeyValuePair en C++, delegate on C++ y dictionary
//delegate on C++ https://stackoverflow.com/questions/9568150/what-is-a-c-delegate
//dictionary on c++ https://stackoverflow.com/questions/15151480/simple-dictionary-in-c
//c++ key value pair class https://www.geeksforgeeks.org/pair-in-cpp-stl/

void Menu::addOption(int number, const string& description, function<void()> action)
{
    options[number] = make_pair(description, action); // Asignamos una descripción y una acción a la opción con su número correspondiente
}

// Método para mostrar el menú y manejar las selecciones del usuario
void Menu::display()
{
    display([this](int input)
    {
        return this->byDelegate(input);
    });
}

void Menu::display(std::function<bool(int)> delegate)
{
    char choice;
    do
    {
        system("cls"); // Limpiamos la pantalla (compatible con Windows)

        std::cout << ResourceManager::getMessage("MENU_TITLE") << std::endl;

        // Recorremos las opciones del menú y las mostramos en pantalla
        for (const auto& option : options)
        {
            std::cout << option.first << ". " << option.second.first << std::endl;
        }

        // Solicitamos al usuario que ingrese el número de la opción deseada
        std::cout << ResourceManager::getMessage("PROMPT_OPTION");
        int input = 0;
        Utils::safeInput(input, -1);
        system("cls");

        bool tryOther = delegate(input);
        if (tryOther)
        {
            // Preguntamos al usuario si desea hacer algo más y validamos su respuesta
            do
            {
                std::cout << ResourceManager::getMessage("PROMPT_CONTINUE");
                Utils::safeInput(choice, 'd');
                choice = toupper(choice); // Convertimos la respuesta a mayúsculas
            }
            while (choice != 'S' && choice != 'N');   // Repetimos hasta que la respuesta sea válida
        }
        else
        {
            return;
        }
    }
    while (choice == 'S');   // Repetimos el bucle si el usuario desea hacer algo más
}
///busca en las opciones el menú a utilizar y llamar al delegado
bool Menu::byDelegate(int input)
{
    // Buscamos la opción seleccionada en el mapa de opciones
    auto selectedOption = options.find(input);
    if (selectedOption != options.end())   // si se encuentra la opción
    {
        // Ejecutamos la acción asociada a la opción seleccionada
        if (selectedOption->second.second != nullptr)
        {
            selectedOption->second.second();
        }
        else
        {
            return false; // Salimos del bucle si no hay una acción asociada (opción de salida)
        }
    }
    else     // Si la opción es inválida
    {
        std::cout << ResourceManager::getMessage("INVALID_OPTION") << std::endl; // Mostramos un mensaje de error
    }
    return true;
}

