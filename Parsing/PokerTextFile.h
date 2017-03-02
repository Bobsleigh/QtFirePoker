#ifndef POKERTEXTFILE_H
#define POKERTEXTFILE_H

#include "Hand.h"
#include <vector>
#include "Parsing/player.h"
#include "Parsing/StatsCounter.h"

class PokerTextFile
{
    public:
    PokerTextFile();

    void nbOfHoleCardsPerRankReset();
    bool load(std::string fileName, Player* activePlayer);
    Hand readSingleHand(std::ifstream* txtFile, Player* activePlayer);
    std::vector<Hand> getFileHands();

    void readHandStartingLine(std::string textLine, Hand* currentHand);
    int readHandSeatLine(std::string textLine, Player* activePlayer, Hand* currentHand);
    bool readBlindLine(std::string textLine, Player* activePlayer, Hand* currentHand);
    void readHoleCardsLine(std::string textLine, Hand* currentHand);
    int readBetLine(std::string textLine, Player* activePlayer, Hand* currentHand, Street* currentStreet);
    std::string getNextNumber(std::string textLine, size_t* startPos, size_t* endPos, std::string cutOffChar);
    bool seekNextHand(std::ifstream* txtFile);
    void setHoleCardsRank(Hand* currentHand);

    StatsCounter nbOfHoleCardsPerRank(int firstCardRank, int secondCardRank, int suited);

    private:
    std::vector<Hand> m_hands;
    std::string m_name;

    //Array storing card rank info (i.e. ATo, 98s)
    //The third dimension is 0 = offsuit, 1 = suited
    StatsCounter m_nbOfHoleCardsPerRank[14][14][2]; //Note: for clarity, 0 indices are left empty and have no meaning.


};



#endif // POKERTEXTFILE_H
