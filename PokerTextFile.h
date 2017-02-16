#ifndef POKERTEXTFILE_H
#define POKERTEXTFILE_H

#include "Hand.h"
#include <vector>
#include "player.h"


class PokerTextFile
{
    public:
    PokerTextFile();
    bool load(std::string fileName, Player* activePlayer);
    Hand readSingleHand(std::ifstream* txtFile, Player* activePlayer);
    std::vector<Hand> getFileHands();

    void readHandStartingLine(std::string textLine, Hand* currentHand);
    int readHandSeatLine(std::string textLine, Player* activePlayer, Hand* currentHand);
    bool readBlindLine(std::string textLine, Player* activePlayer, Hand* currentHand);
    void readHoleCardsLine(std::string textLine, Hand* currentHand);
    int readBetLine(std::string textLine, Player* activePlayer);
    std::string getNextNumber(std::string textLine, size_t* startPos, size_t* endPos, std::string cutOffChar);
    bool seekNextHand(std::ifstream* txtFile);

    private:
    std::vector<Hand> m_hands;
    std::string m_name;


};

#endif // POKERTEXTFILE_H
