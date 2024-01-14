#include "YahtzeeScoreCard.h"
#include <numeric>
#include <algorithm>

YahtzeeScoreCard::YahtzeeScoreCard() {
    scores.resize(13, -1); 
    categoryNames = { "1. Ones", "2. Twos", "3. Threes", "4. Fours", "5. Fives", "6. Sixes",
                     "7. Three of a Kind", "8. Four of a Kind", "9. Full House",
                     "10. Small Straight", "11. Large Straight", "12. Yahtzee", "13. Chance" };
}

YahtzeeScoreCard::~YahtzeeScoreCard() {}

void YahtzeeScoreCard::displayScoreCard() const {
    std::cout << "Yahtzee Score Card\n";
    for (unsigned int i = 0; i < scores.size(); ++i) {
        if (scores[i] == -1) {
            std::cout << categoryNames[i] << ": Not marked\n";
        } else {
            std::cout << categoryNames[i] << ": " << scores[i] << " points\n";
        }
    }
}

bool YahtzeeScoreCard::markScore(int category, const std::vector<int>& diceValues) {
   while(!isValidCategory(category)){
        std::cout << "Invalid category.\n";
        std::cout << "Please choose an open category (1-13): ";
        std::cin >> category;
    }
    
   while (scores[category - 1] != -1) {
       std::cout << "Category already marked.\n";
       std::cout << "Please choose an open category (1-13): ";
       std::cin >> category;
   }
    
    int points = 0;
    switch (category) {
        case 1: 
        case 2: 
        case 3: 
        case 4: 
        case 5:  
        case 6:  
            for (int value : diceValues) {
                if (value == category) {
                    points += value;
                }
            }
            break;

        case THREE_OF_A_KIND:
            for (int i = 1; i <= 6; ++i) {
                if (std::count(diceValues.begin(), diceValues.end(), i) >= 3) {
                    points = std::accumulate(diceValues.begin(), diceValues.end(), 0);
                    break;
                }
            }
            break;

        case FOUR_OF_A_KIND:
            for (int i = 1; i <= 6; ++i) {
                if (std::count(diceValues.begin(), diceValues.end(), i) >= 4) {
                    points = std::accumulate(diceValues.begin(), diceValues.end(), 0);
                    break;
                }
            }
            break;

        case FULL_HOUSE:
            {
                std::vector<int> sortedValues = diceValues;
                std::sort(sortedValues.begin(), sortedValues.end());
                if ((sortedValues[0] == sortedValues[1] && sortedValues[1] == sortedValues[2] &&
                     sortedValues[3] == sortedValues[4]) ||
                    (sortedValues[0] == sortedValues[1] && sortedValues[2] == sortedValues[3] &&
                     sortedValues[3] == sortedValues[4])) {
                    points = 25;
                }
            }
            break;

        case SMALL_STRAIGHT:
            {
                std::vector<int> sortedValues = diceValues;
                std::sort(sortedValues.begin(), sortedValues.end());
                for (int i = 0; i < 2; ++i) {
                    if (sortedValues[i] + 1 == sortedValues[i + 1] &&
                        sortedValues[i + 1] + 1 == sortedValues[i + 2] &&
                        sortedValues[i + 2] + 1 == sortedValues[i + 3]) {
                        points = 30;
                        break;
                    }
                }
            }
            break;

        case LARGE_STRAIGHT:
            {
                std::vector<int> sortedValues = diceValues;
                std::sort(sortedValues.begin(), sortedValues.end());
                if ((sortedValues[0] + 1 == sortedValues[1] && sortedValues[1] + 1 == sortedValues[2] &&
                     sortedValues[2] + 1 == sortedValues[3] && sortedValues[3] + 1 == sortedValues[4]) ||
                    (sortedValues[0] == 1 && sortedValues[1] == 2 && sortedValues[2] == 3 &&
                     sortedValues[3] == 4 && sortedValues[4] == 5)) {
                    points = 40;
                }
            }
            break;

        case YAHTZEE:
            for (int i = 1; i <= 6; ++i) {
                if (std::count(diceValues.begin(), diceValues.end(), i) == 5) {
                    points = 50;
                    break;
                }
            }
            break;
        case CHANCE:
            points = std::accumulate(diceValues.begin(), diceValues.end(), 0);
            break;

        default:
            std::cout << "Invalid category.\n";
            return false;
    }

    auto it = const_cast<std::vector<int>&>(diceValues).begin();
    std::advance(it, 0);

    scores[category - 1] = points;
    return true;
}

int YahtzeeScoreCard::calculateTotalScore() const { 
    int totalScore = 0;
        for (int categoryScore : scores) {
        if (categoryScore > 0) {
            totalScore += categoryScore;
        }
    }

    totalScore += calculateUpperSectionBonus();


    return totalScore;
}

bool YahtzeeScoreCard::isValidCategory(int category) const {
    return category >= 1 && category <= 13;
}

int YahtzeeScoreCard::calculateUpperSectionBonus() const {
    int upperSectionScore = std::accumulate(scores.begin(), scores.begin() + 6, 0);
    return (upperSectionScore >= 63) ? 35 : 0;
}
