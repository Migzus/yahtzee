#include "yahtzee.h"

void gotoxy(short x, short y) {
    static HANDLE _h = nullptr;

    if (!_h) {
        _h = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    COORD _c = { x, y };
    SetConsoleCursorPosition(_h, _c);
}

void HideCursor() {
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = false;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void YahtzeeCore::Tutorial(short offsetX, short offsetY) const {
    gotoxy(offsetX, offsetY);
    std::cout << "     TUTORIAL";
    gotoxy(offsetX, offsetY + 1);
    std::cout << "    ‾‾‾‾‾‾‾‾‾‾";
    gotoxy(offsetX, offsetY + 3);
    std::cout << "Select with " << RED << 'w' << WHITE << " and " << RED << 's' << WHITE;
    gotoxy(offsetX, offsetY + 4);
    std::cout << "Select die, " << RED << 'a' << WHITE << " and " << RED << 'd' << WHITE;
    gotoxy(offsetX, offsetY + 5);
    std::cout << "Keep die with " << BLUE << "SPACE" << WHITE;
    gotoxy(offsetX, offsetY + 6);
    std::cout << "Roll with " << RED << 'r' << WHITE;
    gotoxy(offsetX, offsetY + 7);
    std::cout << "Continue with " << GREEN << 'y' << WHITE;
}

void YahtzeeCore::DrawMap(bool* updateUpperSum) const {
    gotoxy(0, 0);

    // prepare the upper border

    std::cout << WHITE << "╒";

    for (int i{ 0 }; i < nameLength; i++) {
        std::cout << "═";
    }

    for (int i{ 0 }; i < playerCount; i++) {
        std::cout << "╤";

        for (int j{ 0 }; j < PLAYER_NAME_LENGTH; j++) {
            std::cout << "═";
        }
    }

    std::cout << "╕";
    gotoxy(0, 1);
    std::cout << "│ Players";
    gotoxy(short(nameLength) + 1, 1);

    for (size_t i{ 0 }; i < playerCount; i++) {
        std::cout << "│" << players[i].name;
        gotoxy(nameLength + 1 + short(i + 1) * (PLAYER_NAME_LENGTH + 1), 1);
    }

    std::cout << "│\n├";

    for (int i{ 0 }; i < nameLength; i++) {
        std::cout << "─";
    }

    for (int i{ 0 }; i < playerCount; i++) {
        std::cout << "┼";

        for (int j{ 0 }; j < PLAYER_NAME_LENGTH; j++) {
            std::cout << "─";
        }
    }

    // print the upper rows

    std::cout << "┤\n";

    for (size_t y{ 0 }; y < n_upperSection.size(); y++) {
        std::cout << "│" << n_upperSection[y];

        gotoxy(short(nameLength + 1), short(y + 3));

        for (size_t x{ 0 }; x < playerCount; x++) {
            std::cout << "│" << (x == currentPlayer && y == size_t(currentBet) ? YELLOW_REVERSED : WHITE);

            if (players[x].scores[y] != 0) {
                if (players[x].scores[y] == -1) {
                    std::cout << " -- " << WHITE;
                }
                else {
                    std::string _spacing{ "" }, _number{ std::to_string(players[x].scores[y]) };

                    _spacing.resize(PLAYER_NAME_LENGTH - _number.size(), ' ');

                    std::cout << _spacing + _number << WHITE;
                }
            }
            else {
                std::cout << "    " << WHITE;
            }
        }

        std::cout << "│\n";
    }

    // print the sum
    std::cout << "├";

    for (int i{ 0 }; i < nameLength; i++) {
        std::cout << "─";
    }

    for (int i{ 0 }; i < playerCount; i++) {
        std::cout << "┼";

        for (int j{ 0 }; j < PLAYER_NAME_LENGTH; j++) {
            std::cout << "─";
        }
    }

    std::cout << "┤\n│ Sum";
    gotoxy(short(nameLength) + 1, short(n_upperSection.size()) + 4);

    for (size_t i{ 0 }; i < playerCount; i++) {
        if (*updateUpperSum) {
            std::cout << "│" << players[i].CalculateScore();
        }
        gotoxy(nameLength + 6 + short(i) * (PLAYER_NAME_LENGTH + 1), short(n_upperSection.size()) + 4);
    }

    std::cout << "│\n╞";

    for (int i{ 0 }; i < nameLength; i++) {
        std::cout << "═";
    }

    for (int i{ 0 }; i < playerCount; i++) {
        std::cout << "╪";

        for (int j{ 0 }; j < PLAYER_NAME_LENGTH; j++) {
            std::cout << "═";
        }
    }

    std::cout << "╡\n";

    // print lower section

    for (size_t y{ 0 }; y < n_lowerSection.size(); y++) {
        std::cout << "│" << n_lowerSection[y];

        size_t _extraHeight { y + n_upperSection.size() };

        gotoxy(short(nameLength + 1), short(_extraHeight + 6));

        for (size_t x{ 0 }; x < playerCount; x++) {
            std::cout << "│" << (x == currentPlayer && _extraHeight == size_t(currentBet) ? YELLOW_REVERSED : WHITE);

            if (players[x].scores[_extraHeight] != 0) {
                if (players[x].scores[_extraHeight] == -1) {
                    std::cout << " -- " << WHITE;
                }
                else {
                    std::string _spacing{ "" }, _number{ std::to_string(players[x].scores[_extraHeight]) };

                    _spacing.resize(PLAYER_NAME_LENGTH - _number.size(), ' ');

                    std::cout << _spacing + _number << WHITE;
                }
            }
            else {
                std::cout << "    " << WHITE;
            }
        }

        std::cout << "│\n";
    }

    // final Sum
    std::cout << "├";

    for (int i{ 0 }; i < nameLength; i++) {
        std::cout << "─";
    }

    for (int i{ 0 }; i < playerCount; i++) {
        std::cout << "┼";

        for (int j{ 0 }; j < PLAYER_NAME_LENGTH; j++) {
            std::cout << "─";
        }
    }

    std::cout << "┤\n│ Sum";
    gotoxy(short(nameLength) + 1, short(n_upperSection.size() + n_lowerSection.size()) + 7);

    for (size_t i{ 0 }; i < playerCount; i++) {
        std::cout << "│" << players[i].CalculateScore();
        gotoxy(nameLength + 6 + short(i) * (PLAYER_NAME_LENGTH + 1), short(n_upperSection.size() + n_lowerSection.size()) + 7);
    }

    std::cout << "│\n╘";

    for (int i{ 0 }; i < nameLength; i++) {
        std::cout << "═";
    }

    for (int i{ 0 }; i < playerCount; i++) {
        std::cout << "╧";

        for (int j{ 0 }; j < PLAYER_NAME_LENGTH; j++) {
            std::cout << "═";
        }
    }

    std::cout << "╛";

    gotoxy(0, 0);
}

void YahtzeeCore::NamePlayers() {
    for (int i{ 0 }; i < playerCount; i++) {
        Player _assignPlayer;

        std::cout << "Name for Player " << i + 1 << ": ";
        std::cin >> _assignPlayer.name;

        _assignPlayer.name.resize(PLAYER_NAME_LENGTH);

        players.push_back(_assignPlayer);

        system("cls");
    }

    set_scoreVectorLength();
}

void YahtzeeCore::set_scoreVectorLength() {
    for (size_t i{ 0 }; i < players.size(); i++) {
        players[i].scores.resize(n_upperSection.size() + n_lowerSection.size());
    }
}

void YahtzeeCore::Run() {
    size_t currentTurn{ 0 };
    bool nextPlayer{ false };

    // game loop
    while (true) {
        bool _isInLowerSection{ currentTurn < n_upperSection.size() };

        if (dice.turnsRemaining == 0) {
            gotoxy(0, 25);
            std::cout << "Press y for next player";
            nextPlayer = true;
        }

        // clamp current bet i beween the current section
        clamp(&currentBet, int(_isInLowerSection ? 0 : n_upperSection.size()), int(_isInLowerSection ? n_upperSection.size() - 1 : n_lowerSection.size() + n_upperSection.size() - 1));

        // update the yahtzee sheet
        DrawMap(&_isInLowerSection);

        switch (_getch()) {
        case 'r':
            // roll all of the non keep die
            if (!nextPlayer) {
                dice.ThrowDie();
                dice.turnsRemaining--;
            }
            break;
        case 'w':
            // bet go up
            currentBet--;

            if (players[currentPlayer].scores[size_t(currentBet)] != 0) {
                StayAwayFromOccupiedValues(-1, &_isInLowerSection);
            }
            break;
        case 's':
            // bet go down
            currentBet++;

            if (players[currentPlayer].scores[size_t(currentBet)] != 0) {
                StayAwayFromOccupiedValues(1, &_isInLowerSection);
            }
            break;
        case 'a':
            // dice to left
            dice.currentDice--;
            break;
        case 'd':
            // dice to right
            dice.currentDice++;
            break;
        case 'y':
            // goto next player
            if (nextPlayer) {
                dice.set_keepDieToFalse();
                players[currentPlayer].scores[size_t(currentBet)] = Calculate(&_isInLowerSection);
                dice.set_dieToZero();

                DrawMap(&_isInLowerSection);

                // clear the text that says press y for the next player
                gotoxy(0, 25);
                std::cout << "                       ";

                // check if we are done with all the players
                if (currentPlayer >= playerCount - 1) {
                    currentTurn++;
                    //isGameRunning = currentTurn == 0;
                    currentPlayer = 0;
                }
                else {
                    currentPlayer++;
                }

                dice.turnsRemaining = 3;

                // dynamically move the current bet to the closest slot whos score is empty
                for (size_t i{ 0 }; i < n_upperSection.size() + n_lowerSection.size() ; i++) {
                    if (players[currentPlayer].scores[i] == 0) {
                        currentBet = int(i);
                        break;
                    }
                }

                nextPlayer = false;
            }
            break;
        case ' ':
            // keep dice
            dice.m_die[size_t(dice.currentDice)].keepThisDie = !dice.m_die[size_t(dice.currentDice)].keepThisDie;
            break;
        }

        clamp(&dice.currentDice, 0, dice.length - 1);

        DrawDie();

        if (currentTurn >= n_lowerSection.size() + n_upperSection.size()) {
            break;
        }
    }
}

void YahtzeeCore::DrawPoll(short offsetX, short offsetY, std::vector<PlayerInfo> info) const {
    gotoxy(offsetX + 5, offsetY);
    std::cout << YELLOW_REVERSED << info[0].name << WHITE;

    gotoxy(offsetX, offsetY + 1);
    std::cout << "    ┌───┐";

    if (info.size() > 1) {
        gotoxy(offsetX, offsetY + 1);
        std::cout << info[1].name;
    }

    gotoxy(offsetX, offsetY + 2);
    std::cout << "┌───┘ 1 │";

    if (info.size() > 2)
        std::cout << info[2].name;

    gotoxy(offsetX, offsetY + 3);
    std::cout << "│ 2     └───┐";
    gotoxy(offsetX, offsetY + 4);
    std::cout << "│         3 │";

    short y{ 0 };

    for (PlayerInfo i : info) {
        gotoxy(offsetX, offsetY + y + 6);
        std::cout << i.name << "\t: " << i.score << '\n';

        y++;
    }
}

void YahtzeeCore::EndGame(bool* endGame) {
    std::vector<PlayerInfo> playerScoreSums;

    for (size_t i{ 0 }; i < playerCount; i++) {
        PlayerInfo _info{};

        _info.name = players[i].name;
        _info.score = players[i].CalculateScore();

        playerScoreSums.push_back(_info);
    }

    std::sort(playerScoreSums.begin(), playerScoreSums.end(), customPlayerSort);
    std::reverse(playerScoreSums.begin(), playerScoreSums.end());

    std::cout << "Press Y to play again, any other button quits the application: ";

    DrawPoll(6, 10, playerScoreSums);

    std::cout << "\n\n";

    switch (_getch()) {
    case 'y':
    case 'Y':
        break;
    default:
        *endGame = true;
        break;
    }
}

void YahtzeeCore::DrawDie() const {
    for (size_t i{ 0 }; i < dice.m_die.size(); i++) {
        if (dice.m_die[i].keepThisDie) {
            std::cout << (int(i) == dice.currentDice ? RED : GREEN);
        }
        else {
            std::cout << (int(i) == dice.currentDice ? BLUE : WHITE);
        }

        dice.DrawDiceResult(static_cast<int>(dice.m_die[i].dieNumber), short(playerCount * (PLAYER_NAME_LENGTH + 1) + nameLength + 3), short(i) * 5);
    }
}

void YahtzeeCore::StayAwayFromOccupiedValues(int direction, bool* isInLowerSection) {
    int _i{ currentBet };
    const int _length{ (direction == 1 ? int(n_upperSection.size() + (isInLowerSection ? n_lowerSection.size() : 0)) : -1) };

    while (_i != _length) {
        if (players[currentPlayer].scores[size_t(_i)] == 0) {
            currentBet = _i;
            return;
        }

        _i += direction;
    }

    currentBet -= direction;
}

int YahtzeeCore::DiceAlike(const int diceAlikeAmount) {
    for (size_t i{ 1 }; i <= 6; i++) {
        int _diceAmount{ 0 };

        for (size_t j{ 0 }; j < dice.length; j++) {
            if (size_t(dice.m_die[j].dieNumber) == i) {
                _diceAmount++;
            }

            if (_diceAmount >= diceAlikeAmount) {
                return int(dice.m_die[j].dieNumber) * diceAlikeAmount;
            }
        }
    }

    return -1;
}

int YahtzeeCore::Calculate(bool* isAtUpperSection) {
    int _retValue{ 0 };

    if (*isAtUpperSection) {
        for (size_t i{ 0 }; i < dice.length; i++) {
            if (currentBet + 1 == int(dice.m_die[i].dieNumber)) {
                _retValue += int(dice.m_die[i].dieNumber);
            }
        }

        if (_retValue == 0) {
            _retValue = -1;
        }
    }
    else {
        bool _returnNothing{ true };

        switch (currentBet - int(n_upperSection.size())) {
        case 0:
            // one pair
            std::sort(dice.m_die.begin(), dice.m_die.end(), customSort);

            for (size_t i{ 0 }; i < dice.length - 1; i++) {
                if (dice.m_die[i].dieNumber == dice.m_die[i + 1].dieNumber) {
                    _retValue = int(dice.m_die[i].dieNumber) * 2;
                    _returnNothing = false;
                }
            }

            if (_returnNothing) {
                _retValue = -1;
            }
            break;
        case 1:
            // two pairs
            std::sort(dice.m_die.begin(), dice.m_die.end(), customSort);

            if (dice.m_die[0].dieNumber == dice.m_die[1].dieNumber && dice.m_die[2].dieNumber == dice.m_die[3].dieNumber) {
                 _retValue += (int(dice.m_die[0].dieNumber) + int(dice.m_die[2].dieNumber)) * 2;
            }
            else if (dice.m_die[1].dieNumber == dice.m_die[2].dieNumber && dice.m_die[3].dieNumber == dice.m_die[4].dieNumber) {
                _retValue += (int(dice.m_die[1].dieNumber) + int(dice.m_die[3].dieNumber)) * 2;
            }
            else if (dice.m_die[0].dieNumber == dice.m_die[1].dieNumber && dice.m_die[3].dieNumber == dice.m_die[4].dieNumber) {
                _retValue += (int(dice.m_die[0].dieNumber) + int(dice.m_die[3].dieNumber)) * 2;
            }
            else {
                _retValue = -1;
            }
            break;
        case 2:
            // 3 of a kind
            _retValue = DiceAlike(3);
            break;
        case 3:
            // 4 of a kind
            _retValue = DiceAlike(4);
            break;
        case 4:
            // house
            std::sort(dice.m_die.begin(), dice.m_die.end(), customSort);

            if ((dice.m_die[0].dieNumber == dice.m_die[1].dieNumber && dice.m_die[1].dieNumber == dice.m_die[2].dieNumber && dice.m_die[3].dieNumber == dice.m_die[4].dieNumber) ||
                (dice.m_die[0].dieNumber == dice.m_die[1].dieNumber && dice.m_die[2].dieNumber == dice.m_die[3].dieNumber && dice.m_die[3].dieNumber == dice.m_die[4].dieNumber)) {
                for (size_t i{ 0 }; i < dice.length; i++) {
                    _retValue += int(dice.m_die[i].dieNumber);
                }
            }
            else {
                _retValue = -1;
            }
            break;
        case 5:
            // small straight
            std::sort(dice.m_die.begin(), dice.m_die.end(), customSort);

            for (size_t i{ 0 }; i < dice.length; i++) {
                if (size_t(dice.m_die[i].dieNumber) == i + 1) {
                    _retValue += i + 1;
                }
                else {
                    _retValue = -1;
                    break;
                }
            }
            break;
        case 6:
            // large straight
            std::sort(dice.m_die.begin(), dice.m_die.end(), customSort);

            for (size_t i{ 0 }; i < dice.length; i++) {
                if (size_t(dice.m_die[i].dieNumber) == i + 2) {
                    _retValue += i + 2;
                }
                else {
                    _retValue = -1;
                    break;
                }
            }
            break;
        case 7:
            // chance
            for (size_t i{ 0 }; i < dice.length; i++) {
                _retValue += int(dice.m_die[i].dieNumber);
            }
            break;
        case 8:
            // yahtzee
            for (size_t i{ 0 }; i < dice.length - 1; i++) {
                if (dice.m_die[i].dieNumber == dice.m_die[i + 1].dieNumber) {
                    _retValue = 50;
                }
                else {
                    _retValue = -1;
                    break;
                }
            }
            break;
        default:
            _retValue = -1;
            break;
        }
    }

    return  _retValue;
}
