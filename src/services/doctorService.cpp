#include "services/doctorService.h"
#include "ResourceManager.h"
#include "utils.h"
#include <iostream>

using namespace std;
using namespace Project2;

Doctor DoctorService::createObject() {
    int id = getIdInput();
    string firstName = getFirstNameInput();
    string lastName = getLastNameInput();
    Speciality speciality = getSpecialityInput();

    return Doctor(id, firstName, lastName, speciality);
}

Speciality DoctorService::getSpecialityInput() {
    while (true) {
        cout << ResourceManager::getMessage("PROMPT_DOCTOR_SPECIALITY")
             << "1. " << ResourceManager::getMessage("DOCTOR_SPECIALITY_GENERAL") << endl
             << "2. " << ResourceManager::getMessage("DOCTOR_SPECIALITY_ONCOLOGY") << endl
             << "3. " << ResourceManager::getMessage("DOCTOR_SPECIALITY_PHYSIOTHERAPY") << endl
             << "4. " << ResourceManager::getMessage("DOCTOR_SPECIALITY_WILDLIFE") << endl
             << ResourceManager::getMessage("PROMPT_DOCTOR_SPECIALITY_OPTION");
        int choice;
        Utils::safeInput(choice, 0);
        switch (choice) {
            case 1: return Speciality::GeneralMedicine;
            case 2: return Speciality::Oncology;
            case 3: return Speciality::Physiotherapy;
            case 4: return Speciality::Wildlife;
            default:
                cerr << ResourceManager::getMessage("ERROR_INVALID_SPECIALITY") << endl;
        }
    }
}
