#pragma once

#include <iostream>
#include <vector>
#include "Dice.h"
#include "YahtzeeScoreCard.h"

class Player {
public:
    Player();  
    Player(const std::string& name);
    virtual ~Player();

    const std::string& getName() const;

    void rollDice();
    void displayScoreCard() const;
    int calculateScore() const;
    bool markScore(int category);

    void keepDice();       
    void rerollDice();     
    std::vector<int> getDiceValues() const;    
    void printDice() const;
    void displayFinalScore();

private:
    std::string playerName;
    std::vector<Dice> diceSet;
    std::vector<bool> diceToKeep;     
    YahtzeeScoreCard scoreCard;

};