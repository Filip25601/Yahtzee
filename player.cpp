#include "player.h"

Player::Player() : playerName("Unnamed Player") {  
    diceSet.resize(5);
    diceToKeep.resize(5, false);
}

Player::Player(const std::string& name) : playerName(name) {
    diceSet.resize(5);
    diceToKeep.resize(5, false);
}

Player::~Player() {}

void Player::rollDice() {
    for (unsigned int i = 0; i < diceSet.size(); ++i) {
        if (!diceToKeep[i]) {
            diceSet[i].roll();
        }
    }
    std::fill(diceToKeep.begin(), diceToKeep.end(), false);
}

const std::string& Player::getName() const {
    return playerName;
}

void Player::displayScoreCard() const {
    std::cout << "Player: " << playerName << "\n";
    std::cout << "Score: " << calculateScore() << "\n";
    scoreCard.displayScoreCard();
}

int Player::calculateScore() const {
    return scoreCard.calculateTotalScore();
}

bool Player::markScore(int category) {
    return scoreCard.markScore(category, getDiceValues());
}

void Player::keepDice() {
    std::cout << "How many dice do you want to keep? Enter 0 to keep none: ";
    int numDiceToKeep;
    std::cin >> numDiceToKeep;

    while (numDiceToKeep < 0 || numDiceToKeep > 5)
    {
        std::cout << "Invalid input. Enter a number between 0 and 5: " << '\n';
        std::cin >> numDiceToKeep;
        
    }

    if (numDiceToKeep == 0) {
        std::fill(diceToKeep.begin(), diceToKeep.end(), false);
    }
    else if (numDiceToKeep == 5) {
        std::fill(diceToKeep.begin(), diceToKeep.end(), true);
    }
    else {
        std::cout << "Enter the positions of the dice you want to keep (1-5), separated by spaces: ";
        for (int i = 0; i < numDiceToKeep; ++i) {
            int position;
            std::cin >> position;

            while (position < 1 || position > 5) {
                std::cout << "Invalid input. Enter a number between 1 and 5: ";
                std::cin >> position;
            }

            diceToKeep[position - 1] = true;
        }
    }
}


void Player::rerollDice() {
    for (unsigned int i = 0; i < diceSet.size(); ++i) {
        if (!diceToKeep[i]) {
            diceSet[i].roll();
        }
    }

    for (unsigned int i = 0; i < diceSet.size(); ++i) {
        if (!diceToKeep[i]) {
            diceSet[i].roll();
        }
    }
    printDice();
}


std::vector<int> Player::getDiceValues() const {
    std::vector<int> values;
    for (const Dice& die : diceSet) {
        values.push_back(die.getValue());
    }
    return values;
}

void Player::printDice() const {
    std::cout << "Dice values: ";
    std::vector<int> diceValues = getDiceValues();
    for (int value : diceValues) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

void Player::displayFinalScore() {
    std::cout << "Final score for " << playerName << ": " << calculateScore() << " points\n";
}
