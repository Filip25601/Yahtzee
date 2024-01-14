#pragma once

#include <iostream>
#include <random>


class Dice {
public:
    Dice();
    ~Dice();

    void roll();
    int getValue() const;

    Dice(const Dice& other);  
    Dice& operator=(const Dice& other);   

private:
    int value;
    std::random_device rd; 
    std::mt19937 gen; 
    std::uniform_int_distribution<int> distribution;  
};