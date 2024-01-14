#pragma once

#include "Player.h"

class YahtzeeGame {
public:
    YahtzeeGame();
    ~YahtzeeGame();

    void playGame();

private:
    std::vector<Player> players;
    int currentPlayerIndex;

    void initializeGame();
    void playRound();
};