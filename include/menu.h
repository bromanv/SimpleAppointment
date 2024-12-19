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
    /// Mapa que almacena las opciones del men�. Cada opci�n tiene un n�mero, una descripci�n y una funci�n asociada.
    std::map<int, std::pair<std::string, std::function<void()>>> options;
    void display(std::function<bool(int)> delegate);
    /// Controla el men� mediante un delegado
    /// - input valor seleccionado por el usuario.
    bool byDelegate(int input);

public:
    /// M�todo para a�adir una opci�n al men�
    /// Par�metros:
    /// - number: N�mero de la opci�n
    /// - description: Descripci�n de la opci�n, se le muestra al usuario.
    /// - action: Funci�n que se ejecuta al seleccionar la opci�n
    void addOption(int number, const std::string& description, std::function<void()> action);
    /// M�todo para mostrar el men� en pantalla
    void display();
};

#endif // MENU_H
