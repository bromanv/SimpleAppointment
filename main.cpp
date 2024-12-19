#include "menu.h" // Incluimos el archivo de encabezado que contiene las constantes utilizadas

#include "services/doctorService.h"
#include "services/clientService.h"
#include "services/appointmentService.h"
#include "services/reportservice.h"

#include "constants.h"
#include "utils.h"
#include "ResourceManager.h"


#include <iostream>
#include <map>
#include <functional>
#include <cstdlib>

#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <stdexcept> // Biblioteca estándar que contiene definiciones de excepciones
#include <winnls.h>
#include <windows.h>
using namespace std;
using namespace Project2;

int main()
{
    // https://stackoverflow.com/questions/2492077/output-unicode-strings-in-windows-console
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    DoctorService doctorService;
    ClientService clientService;
    AppointmentService appointmentService;
    ReportService reportService;

    // Cargar mensajes en diferentes idiomas
    ResourceManager::loadMessages("resources/messages_en.json");
    ResourceManager::loadMessages("resources/messages_es.json");

    // Establecer el idioma actual (por ejemplo, "es" para español)
    ResourceManager::setLanguage("es");

    do
    {
        try
        {
            Menu menu;
            //Esta clase es de mi autoria y permite de forma mas flexible agregar  opciones, e iniciar nuevos proyectos
            menu.addOption(1, ResourceManager::getMessage("MENU_OPTION_1"), std::bind(&DoctorService::registerObject, &doctorService));
            menu.addOption(2, ResourceManager::getMessage("MENU_OPTION_2"), std::bind(&ClientService::registerObject, &clientService));
            menu.addOption(3, ResourceManager::getMessage("MENU_OPTION_3"), std::bind(&AppointmentService::registerObject, &appointmentService));
            menu.addOption(4, ResourceManager::getMessage("MENU_OPTION_4"), std::bind(&ReportService::generateReportByDoctor, &reportService));
            menu.addOption(5, ResourceManager::getMessage("MENU_OPTION_5"), std::bind(&ReportService::generateReportByClient, &reportService));
            menu.addOption(6, ResourceManager::getMessage("MENU_OPTION_6"), nullptr);

            menu.display();
            return 0;
        }
        catch (const std::runtime_error& e)
        {
            std::cout << "Ha ocurrido un error no controlado: " << e.what() << std::endl;
            std::cout << ResourceManager::getMessage("PROMPT_CONTINUE")<<std::endl;
        }
    }
    while(true);
    return 0;
}
