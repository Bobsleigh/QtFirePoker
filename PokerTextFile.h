#ifndef POKERTEXTFILE_H
#define POKERTEXTFILE_H

#include "Hand.h"
#include <vector>


class PokerTextFile
{
    public:
    PokerTextFile();
    void load(std::string fileName, std::string activePlayer);
    Hand readSingleHand(std::ifstream* txtFile, std::string activePlayer);

    void readHandStartingLine(std::string textLine, Hand* currentHand);
    int readHandSeatLine(std::string textLine, std::string activePlayer, Hand* currentHand);
    bool readBlindLine(std::string textLine, std::string activePlayer, Hand* currentHand);
    void readHoleCardsLine(std::string textLine, Hand* currentHand);
    int readBetLine(std::string textLine, std::string activePlayer);
    std::string getNextNumber(std::string textLine, size_t* startPos, size_t* endPos, std::string cutOffChar);
    bool seekNextHand(std::ifstream* txtFile);


    private:
    std::vector<Hand> m_hands;
    std::string m_name;


};

#endif // POKERTEXTFILE_H
