#pragma once

#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <windows.h>

const char WHITE[9]{ 0x1b, '[', '0', '0', ';', '3', '7', 'm', 0 };
const char GREEN[9]{ 0x1b, '[', '0', '0', ';', '3', '2', 'm', 0 };
const char BLUE[9]{ 0x1b, '[', '0', '0', ';', '3', '4', 'm', 0 };
const char RED[9]{ 0x1b, '[', '0', '1', ';', '3', '1', 'm', 0 };
const char YELLOW_REVERSED[9]{ 0x1b, '[', '0', '7', ';', '3', '3', 'm', 0 };
const int PLAYER_NAME_LENGTH{ 4 };

template<class T> void clamp(T* value, const T min, const T max) {
    *value = (*value < min ? min : (*value > max ? max : *value));
}

enum class DICE_NUM : int {
    _NULL,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX
};

void gotoxy(short x, short y);
void HideCursor();

struct PlayerInfo {
    std::string name{ "" };
    int score{ 0 };

    bool operator()(PlayerInfo a, PlayerInfo b){
        return a.score < b.score;
    }
};

struct {
    bool operator()(PlayerInfo a, PlayerInfo b){
        return a.score < b.score;
    }
} customPlayerSort;

struct Die {
    DICE_NUM dieNumber;
    bool keepThisDie{ false };
};

struct {
    bool operator()(Die a, Die b) {
        return a.dieNumber < b.dieNumber;
    }
} customSort;

class Dice {
public:
    int currentDice{ 0 };
    unsigned int turnsRemaining{ 3 };
    const static auto length{ 5 };
    std::vector<Die> m_die;

    Dice() {
        m_die.resize(length);
    }

    void ThrowDie();
    void DrawDiceResult(int number, short offsetX, short offsetY) const;
    void set_keepDieToFalse();
    void set_dieToZero();
};

class Player {
public:
    unsigned int currentScore{ 0 };
    std::string name;
    std::vector<int> scores;

    int CalculateScore() const {
        int _retVal{ 0 };

        for (size_t i{ 0 }; i < scores.size(); i++) {
            if (scores[i] >= 0) {
                _retVal += scores[i];
            }
        }

        return  _retVal;
    }
};

class YahtzeeCore {
public:
    unsigned short playerCount{ 0 };

    YahtzeeCore() {
        n_upperSection.push_back("Aces");
        n_upperSection.push_back("Twos");
        n_upperSection.push_back("Threes");
        n_upperSection.push_back("Fours");
        n_upperSection.push_back("Fives");
        n_upperSection.push_back("Sixs");

        n_lowerSection.push_back("One pair");
        n_lowerSection.push_back("Two pairs");
        n_lowerSection.push_back("3 of a kind");
        n_lowerSection.push_back("4 of a kind");
        n_lowerSection.push_back("House");
        n_lowerSection.push_back("Sm. straight");
        n_lowerSection.push_back("Lg. straight");
        n_lowerSection.push_back("Chance");
        n_lowerSection.push_back("Yahtzee");

        playerCount = 1;
    }

    void NamePlayers();
    void Run();
    void EndGame(bool* endGame);
    void Tutorial(short, short) const;

private:
    Dice dice;
    std::vector<Player> players;
    int currentBet{ 0 };
    unsigned short currentPlayer{ 0 };
    const unsigned short nameLength{ 12 };
    std::vector<std::string> n_upperSection;
    std::vector<std::string> n_lowerSection;

    void set_scoreVectorLength();
    void DrawMap(bool*) const;
    void DrawPoll(short, short, std::vector<PlayerInfo>) const;
    void DrawDie() const;
    void StayAwayFromOccupiedValues(int, bool*);
    int DiceAlike(const int);
    int Calculate(bool*);
};
