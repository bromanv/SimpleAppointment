#include "entities/person.h"
#include "ResourceManager.h"
#include <stdexcept>

using namespace std;
using json = nlohmann::json;
using namespace Project2;

string Person::toString() const
{
    return  nlohmann::json(*this).dump();
}
Person::Person()
{
    setValid(false);
}
// Constructor de la clase Person
Person::Person(int id, const string& firstName, const string& lastName)
{
    setId(id);
    setFirstName(firstName);
    setLastName(lastName);
    setValid(true);
}

void Person::setId(int id)
{
    if (id < 100000000 || id > 999999999)
    {
        throw invalid_argument(ResourceManager::getMessage("ERROR_INVALID_ID"));
    }
    this->id = id;
}

string Person::getFullName() const
{
    return firstName + " " + lastName;
}
string Person::getFirstName() const
{
    return firstName;
}
string Person::getLastName() const
{
    return firstName + " " + lastName;
}

// Setters con validación


void Person::setFirstName(const string& firstName)
{
    if (firstName.empty())
    {
        throw invalid_argument(ResourceManager::getMessage("ERROR_EMPTY_FIRST_NAME"));
    }
    this->firstName = firstName;
}

void Person::setLastName(const string& lastName)
{
    if (lastName.empty())
    {
        throw invalid_argument(ResourceManager::getMessage("ERROR_EMPTY_LAST_NAME"));
    }
    this->lastName = lastName;
}
