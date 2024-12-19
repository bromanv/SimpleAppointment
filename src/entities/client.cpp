#include "entities/client.h"
#include "ResourceManager.h"
#include <stdexcept>

using namespace std;
using json = nlohmann::json;
using namespace Project2;

string Client::toString() const
{
    return  nlohmann::json(*this).dump();
}

Client::Client()
{
    setValid(false);
}

// Constructor de la clase Client
Client::Client(int id, const string& ownerFirstName, const string& ownerLastName, const string& petName, PetType petType, const string& breed, float weight, int age)
    : Person(id, ownerFirstName, ownerLastName)
{
    setPetName(petName);
    setPetType(petType);
    setBreed(breed);
    setWeight(weight);
    setAge(age);
    setValid(true);
}

// Getters
string Client::getPetName() const
{
    return petName;
}
PetType Client::getPetType() const
{
    return petType;
}
string Client::getBreed() const
{
    return breed;
}
float Client::getWeight() const
{
    return weight;
}
int Client::getAge() const
{
    return age;
}
string Client::getPetTypeDescription() const
{
    switch (petType)
    {
    case PetType::Cat:
        return ResourceManager::getMessage("PET_TYPE_CAT");
    case PetType::Dog:
        return ResourceManager::getMessage("PET_TYPE_DOG");
    default:
        throw invalid_argument(ResourceManager::getMessage("ERROR_INVALID_PET_TYPE"));
    }
}

// Setters con validación
void Client::setPetName(const string& petName)
{
    if (petName.empty())
    {
        throw invalid_argument(ResourceManager::getMessage("ERROR_EMPTY_PET_NAME"));
    }
    this->petName = petName;
}

void Client::setPetType(PetType petType)
{
    this->petType = petType;
}

void Client::setBreed(const string& breed)
{
    if (breed.empty())
    {
        throw invalid_argument(ResourceManager::getMessage("ERROR_EMPTY_BREED"));
    }
    this->breed = breed;
}

void Client::setWeight(float weight)
{
    if (weight <= 0)
    {
        throw invalid_argument(ResourceManager::getMessage("ERROR_INVALID_WEIGHT"));
    }
    this->weight = weight;
}

void Client::setAge(int age)
{
    if (age < 0)
    {
        throw invalid_argument(ResourceManager::getMessage("ERROR_INVALID_AGE"));
    }
    this->age = age;
}
