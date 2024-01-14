#pragma once

#define THREE_OF_A_KIND 7
#define FOUR_OF_A_KIND 8
#define FULL_HOUSE 9
#define SMALL_STRAIGHT 10
#define LARGE_STRAIGHT 11
#define YAHTZEE 12
#define CHANCE 13
#include <iostream>
#include <vector>
#include <string>

class YahtzeeScoreCard {
public:
    YahtzeeScoreCard();
    ~YahtzeeScoreCard();

    void displayScoreCard() const;
    bool markScore(int category, const std::vector<int>& diceValues);
    int calculateTotalScore() const;

private:
    std::vector<int> scores;
    std::vector<std::string> categoryNames;    

    bool isValidCategory(int category) const;
    int calculateUpperSectionBonus() const;
};