#include "Dice.h"


Dice::Dice() : gen(rd()), distribution(1, 6) {
}

Dice::~Dice() {}


Dice::Dice(const Dice& other) : value(other.value), rd(), gen(rd()), distribution(1, 6) {
}

void Dice::roll() {
    value = distribution(gen);
}

int Dice::getValue() const {
    return this->value;
}

Dice& Dice::operator=(const Dice& other) {
    if (this != &other) {  
        value = other.value;
    }
    return *this;
}
