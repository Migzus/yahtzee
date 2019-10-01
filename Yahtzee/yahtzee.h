#pragma once

#include <iostream>
#include <conio.h>
#include <vector>
#include <random>
#include <time.h>

enum class DICE_NUM : int {
    _NULL,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX
};

class Dice {
public:
    const int length{ 5 };

    const std::vector<DICE_NUM>& get_Die() const;
    void ThrowDie();
private:
    std::vector<DICE_NUM> m_die;
};

class Player {
public:
    unsigned int currentScore{ 0 };
};

class YahtzeeCore {
public:
    std::vector<Player> players;
    unsigned short playerCount{ 0 };
};
