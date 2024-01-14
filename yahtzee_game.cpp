#include "yahtzee_game.h"
#include <cctype>  
YahtzeeGame::YahtzeeGame() : currentPlayerIndex(1) {}

YahtzeeGame::~YahtzeeGame() {}

void YahtzeeGame::initializeGame() {
    int numPlayers;
    std::cout << "Enter the number of players,from 1-5: ";
    std::cin >> numPlayers;
    while(true) 
    {
        if (std::cin.good() && numPlayers >= 1 && numPlayers <= 5)
        {
            break;
        }
        std::cin.clear();
        std::cout << "Please try again!Enter the number of players,from 1-5: "<<std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> numPlayers;
             
    }

    std::cout << "This will be a game for " << numPlayers << " players!" << std::endl;
    players.resize(numPlayers);
    std::cout << "Enter the player names!" << std::endl;
    for (size_t i = 0; i < numPlayers; ++i) 
    {
        std::string playerName;
        std::cout << "Enter name for Player " << i + 1 << ": ";
        std::cin >> playerName;
        players[i] = Player(playerName);
        system("cls");
    }
}

void YahtzeeGame::playRound() {
    for (auto& player : players) {
        std::cout << "\n" << player.getName() << "'s turn:\n";
        player.rollDice();
        player.printDice();
        player.keepDice(); 
        player.rerollDice();  
        player.keepDice();
        player.rerollDice();
        player.displayScoreCard();
        int category;
        std::cout << "Enter the category to mark: ";
        std::cin >> category;
        player.markScore(category);
        std::cout << "\n\n";
        system("cls");
        player.rollDice();
    }
}

void YahtzeeGame::playGame() {
    initializeGame();

    for (int round = 0; round < 13; ++round) {
        std::cout << "\nRound " << round + 1 << ":\n";
        playRound();

    }

    std::cout << "\nFinal Scores:\n";
    
    for (auto& player : players) {
        player.displayFinalScore();
    }
    
    auto maxScorePlayer = std::max_element(players.begin(), players.end(),
        [](const Player& a, const Player& b) {
            return a.calculateScore() < b.calculateScore();
        });

    if (maxScorePlayer != players.end()) {
        std::cout << "\nPlayer with the highest final score:\n";
        std::cout << "Name: " << maxScorePlayer->getName() << "\n";
        std::cout << "Final Score: " << maxScorePlayer->calculateScore() << "\n";
    }
    }