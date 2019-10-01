#include "yahtzee.h"

const std::vector<DICE_NUM>& Dice::get_Die() const {
    return m_die;
}

void Dice::ThrowDie() {
    m_die.clear();

    for (int i{ 0 }; i <= length; i++) {
        int _randomThrow = (rand() % 6) + 1;

        //std::cout << "Random: " << _randomThrow << '\n';

        switch (_randomThrow) {
        case 1:
            m_die.push_back(DICE_NUM::ONE);
            //std::cout << "one\n";
            //die->push_back(DICE::ONE);
            break;
        case 2:
            m_die.push_back(DICE_NUM::TWO);
            //std::cout << "two\n";
            break;
        case 3:
            m_die.push_back(DICE_NUM::THREE);
            //std::cout << "three\n";
            break;
        case 4:
            m_die.push_back(DICE_NUM::FOUR);
            //std::cout << "four\n";
            break;
        case 5:
            m_die.push_back(DICE_NUM::FIVE);
            //std::cout << "five\n";
            break;
        case 6:
            m_die.push_back(DICE_NUM::SIX);
            //std::cout << "six\n";
            break;
        default:
            m_die.push_back(DICE_NUM::_NULL);
            std::cout << "A dice number was not properly assigned";
            break;
        }
    }
}
