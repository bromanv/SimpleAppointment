#ifndef ENTITYBASE_H
#define ENTITYBASE_H

#include "inull.h"
#include <string>
#include <nlohmann/json.hpp>
namespace Project2
{
class EntityBase: public INull
{
public:
    EntityBase()
    {
        setValid(true);
    }

    int getId() const;
    virtual void setId(int id);
    /**
     * @brief Método toString virtual para convertir a JSON y retornar como cadena.
     * @return Representación JSON de la persona como cadena.
     */
    virtual std::string toString() const;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(EntityBase, id);

    virtual bool isValid() const override
    {
        return this->getValid();
    }
protected:
    int id;
private:
};
}
#endif // ENTITYBASE_H
