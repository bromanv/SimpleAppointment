#include "services/clientService.h"
#include "ResourceManager.h"
#include "utils.h"
#include <iostream>

using namespace std;
using namespace Project2;

Client ClientService::createObject() {
    int id = getIdInput();
    string ownerFirstName = getFirstNameInput();
    string ownerLastName = getLastNameInput();
    string petName = getPetNameInput();
    PetType petType = getPetTypeInput();
    string breed = getBreedInput();
    float weight = getWeightInput();
    int age = getAgeInput();

    return Client(id, ownerFirstName, ownerLastName, petName, petType, breed, weight, age);
}

std::string ClientService::getPetNameInput() {
    while (true) {
        std::string input = getInput(ResourceManager::getMessage("PROMPT_OWNER_PET_NAME"));
        if (!input.empty()) {
            return input;
        } else {
            std::cerr << ResourceManager::getMessage("ERROR_EMPTY_PET_NAME") << std::endl;
        }
    }
}

PetType ClientService::getPetTypeInput() {
    while (true) {
        cout << ResourceManager::getMessage("PROMPT_OWNER_PET_TYPE")
             << "1. " << ResourceManager::getMessage("PET_TYPE_CAT") << endl
             << "2. " << ResourceManager::getMessage("PET_TYPE_DOG") << endl
             << ResourceManager::getMessage("PROMPT_OWNER_PET_TYPE_OPTION");
        int choice;
        Utils::safeInput(choice, 0);
        switch (choice) {
            case 1: return PetType::Cat;
            case 2: return PetType::Dog;
            default:
                cerr << ResourceManager::getMessage("ERROR_INVALID_PET_TYPE") << endl;
        }
    }
}

std::string ClientService::getBreedInput() {
    while (true) {
        std::string input = getInput(ResourceManager::getMessage("PROMPT_OWNER_BREED"));
        if (!input.empty()) {
            return input;
        } else {
            std::cerr << ResourceManager::getMessage("ERROR_EMPTY_BREED") << std::endl;
        }
    }
}

float ClientService::getWeightInput() {
    while (true) {
        try {
            std::string input = getInput(ResourceManager::getMessage("PROMPT_OWNER_WEIGHT"));
            float weight = std::stof(input);
            if (weight > 0) {
                return weight;
            } else {
                std::cerr << ResourceManager::getMessage("ERROR_INVALID_WEIGHT") << std::endl;
            }
        } catch (const std::invalid_argument&) {
            std::cerr << ResourceManager::getMessage("ERROR_INVALID_WEIGHT") << std::endl;
        }
    }
}

int ClientService::getAgeInput() {
    while (true) {
        try {
            std::string input = getInput(ResourceManager::getMessage("PROMPT_OWNER_AGE"));
            int age = std::stoi(input);
            if (age >= 0) {
                return age;
            } else {
                std::cerr << ResourceManager::getMessage("ERROR_INVALID_AGE") << std::endl;
            }
        } catch (const std::invalid_argument&) {
            std::cerr << ResourceManager::getMessage("ERROR_INVALID_AGE") << std::endl;
        }
    }
}
