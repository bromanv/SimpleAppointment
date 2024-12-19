#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <map>
#include <functional>
#include <cstdlib>
#include "ResourceManager.h"

// Gestor del Menu
class Menu
{
private:
    /// Mapa que almacena las opciones del menú. Cada opción tiene un número, una descripción y una función asociada.
    std::map<int, std::pair<std::string, std::function<void()>>> options;
    void display(std::function<bool(int)> delegate);
    /// Controla el menú mediante un delegado
    /// - input valor seleccionado por el usuario.
    bool byDelegate(int input);

public:
    /// Método para añadir una opción al menú
    /// Parámetros:
    /// - number: Número de la opción
    /// - description: Descripción de la opción, se le muestra al usuario.
    /// - action: Función que se ejecuta al seleccionar la opción
    void addOption(int number, const std::string& description, std::function<void()> action);
    /// Método para mostrar el menú en pantalla
    void display();
};

#endif // MENU_H
