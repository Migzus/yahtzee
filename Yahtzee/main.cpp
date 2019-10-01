#include "yahtzee.h"

int main()
{
    Dice die;

    srand(static_cast<unsigned int>(time(nullptr)));

    switch (_getch()) {
    case 'a':
        die.ThrowDie();
        break;
    }

    for (unsigned long long i = 0; i < 5; i++) {
        printf("%i", die.get_Die().at(i));
        std::cout << std::endl;
    }

    return 0;
}
