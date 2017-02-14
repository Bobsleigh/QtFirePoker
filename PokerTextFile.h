#ifndef POKERTEXTFILE_H
#define POKERTEXTFILE_H

#include "Hand.h"
#include <vector>


class PokerTextFile
{
    public:
    PokerTextFile();
    void load(std::string fileName, std::string activePlayer);
    Hand readSingleHand(std::ifstream* txtFile, std::string activePlayer, bool& stillReading);

    void readHandStartingLine(std::string textLine);
    void readHandSeatLine(std::string textLine, std::string activePlayer);
    void readBlindLine(std::string textLine, std::string activePlayer);
    void readHoleCardsLine(std::string textLine, std::string activePlayer);
    void readBetLine(std::string textLine, std::string activePlayer);

    private:
    std::vector<Hand> m_hands;
    std::string m_name;
};

#endif // POKERTEXTFILE_H
