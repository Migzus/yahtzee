#include "yahtzee.h"

void Dice::ThrowDie() {
    for (size_t i{ 0 }; i < length; i++) {
        int _randomThrow = (rand() % 6) + 1;

        if (m_die.at(i).keepThisDie) {
            continue;
        }

        m_die.at(i).dieNumber = DICE_NUM(_randomThrow);
    }
}

void Dice::DrawDiceResult(int number, short offsetX, short offsetY) const {
    if (number <= 0 || number > 6) {
        gotoxy(offsetX, offsetY);
        std::cout << "         ";
        gotoxy(offsetX, offsetY + 1);
        std::cout << "         ";
        gotoxy(offsetX, offsetY + 2);
        std::cout << "         ";
        gotoxy(offsetX, offsetY + 3);
        std::cout << "         ";
        gotoxy(offsetX, offsetY + 4);
        std::cout << "         ";
    }
    else {
        gotoxy(offsetX, offsetY);
        std::cout << "╭───────╮\n";
        gotoxy(offsetX, offsetY + 1);
        std::cout << "│ " << (number >= 4 && number <= 6 ? "●" : " ") <<
                     "   " << (number >= 2 && number <= 6 ? "●" : " ") << " │\n";
        gotoxy(offsetX, offsetY + 2);
        std::cout << "│ " << (number == 6 ? "●" : " ") <<
                     ' ' << (number == 1 || number == 3 || number == 5 ? "●" : " ") <<
                     ' ' << (number == 6 ? "●" : " ") << " │\n";
        gotoxy(offsetX, offsetY + 3);
        std::cout << "│ " << (number >= 2 && number <= 6 ? "●" : " ") <<
                     "   " << (number >= 4 && number <= 6 ? "●" : " ") << " │\n";
        gotoxy(offsetX, offsetY + 4);
        std::cout << "╰───────╯" << WHITE;
    }
}

void Dice::set_keepDieToFalse() {
    for (size_t i{ 0 }; i < m_die.size(); i++) {
        m_die[i].keepThisDie = false;
    }
}

void Dice::set_dieToZero() {
    for (size_t i{ 0 }; i < m_die.size(); i++) {
        m_die[i].dieNumber = DICE_NUM::_NULL;
    }
}
