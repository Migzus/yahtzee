#include "yahtzee.h"

int main() {
    bool exitGame{ false };

    srand(static_cast<unsigned int>(time(nullptr)));

    do {
        YahtzeeCore* yahtzee = new YahtzeeCore;

        exitGame = false;

        std::cout << "Choose player count(max 10): ";
        std::cin >> yahtzee->playerCount;

        clamp(&yahtzee->playerCount, static_cast<unsigned short>(1), static_cast<unsigned short>(10));

        system("cls");

        yahtzee->NamePlayers();
        HideCursor();

        yahtzee->Tutorial(80, 4);
        yahtzee->Run();

        system("cls");

        yahtzee->EndGame(&exitGame);

        system("cls");

        delete yahtzee;

    } while (!exitGame);

    return 0;
}
