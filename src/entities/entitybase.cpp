#include "entities/entitybase.h"
#include "ResourceManager.h"

using namespace std;
using json = nlohmann::json;
using namespace Project2;

string EntityBase::toString() const
{
    return  nlohmann::json(*this).dump();
}

// Getters
int EntityBase::getId() const
{
    return id;
}
void EntityBase::setId(int id)
{
    this->id = id;
}
