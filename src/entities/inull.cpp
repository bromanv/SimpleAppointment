#include "inull.h"
INull::INull() : valid(false) {}

int INull::getValid() const {
    return valid;
}

void INull::setValid(bool value) {
    valid = value;
}
