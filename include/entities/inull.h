#ifndef INULL_H
#define INULL_H


class INull
{
public:
    INull();
    virtual bool isValid() const = 0;

protected:
    int getValid() const;
    void setValid(bool value);
private:
    bool valid;
};


#endif // INULL_H
