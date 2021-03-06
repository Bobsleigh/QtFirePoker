#include "Parsing/PokerTextFile.h"
#include "Parsing/Hand.h"
#include <fstream>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <istream>

PokerTextFile::PokerTextFile() : m_name("")
{
    nbOfHoleCardsPerRankReset();
}

std::vector<Hand> PokerTextFile::getFileHands()
{
    return m_hands;
}

void PokerTextFile::nbOfHoleCardsPerRankReset()
{
    for (int i=0;i<14;i++)
    {
        for (int j=0;j<14;j++)
        {
            for (int k=0;k<2;k++)
            {
                m_nbOfHoleCardsPerRank[i][j][k].reset();
            }
        }
    }
}


bool PokerTextFile::load(std::string fileName, Player* activePlayer)
{
    m_name = fileName;
    m_hands.clear();
    nbOfHoleCardsPerRankReset();

    std::ifstream txtFile(fileName);

    if (txtFile)
    {
        while (true)
        {
            m_hands.push_back(readSingleHand(&txtFile, activePlayer));

            if (seekNextHand(&txtFile) == false)
            {
                break;
            }
        }
    }

    return txtFile.is_open();
}

Hand PokerTextFile::readSingleHand(std::ifstream* txtFile, Player* activePlayer)
{
    int playerStack = -1;
    Hand currentHand;

    std::string textLine;
    std::istream::streampos filePosition(0);


    //STEP 0 - READ HEADER
    getline(*txtFile, textLine);
    readHandStartingLine(textLine, &currentHand);

    //STEP 1 - READ SEATS
    getline(*txtFile, textLine); //TODO: Don't skip Table line but parse it
    while(true)
    {
        filePosition = txtFile->tellg();
        getline(*txtFile, textLine);

        playerStack = readHandSeatLine(textLine, activePlayer, &currentHand);
        if (playerStack == -1) //Special value when done reading hand seat lines
        {
            txtFile->seekg(filePosition);
            break;
        }
    }

    //STEP 2 - READ BLINDS AND ANTES
    while(true)
    {
        getline(*txtFile, textLine);

        int finished = readBlindLine(textLine, activePlayer, &currentHand);

        if (finished) //When done reading blind lines
        {
            break;
        }
    }

    //STEP 3 - READ HOLE CARDS
    getline(*txtFile, textLine);
    readHoleCardsLine(textLine, &currentHand);

    //STEP 4 - READ BETS
    Street currentStreet = Street::PREFLOP;
    while(true)
    {
        getline(*txtFile, textLine);
        int value = readBetLine(textLine, activePlayer, &currentHand, &currentStreet);

        if (value == 0)
        {
            continue;
        }
        else if (value == -1)
        {
            break;
        }
        else if (value < 0)
        {
            currentHand.setLoss(currentHand.loss() - value); //hand.loss is always positive and currently value < 0, so we must substract value to increase loss
        }
        else
        {
            currentHand.setGain(currentHand.gain() + value);
        }
    }
    return currentHand;
}

void PokerTextFile::readHandStartingLine(std::string textLine, Hand* currentHand)
{
    std::string handNumber = "";
    std::string tournamentNumber = "";
    std::string smallBlind = "";
    std::string bigBlind = "";
    std::string year = "";
    std::string month = "";
    std::string day = "";

    //bool skipBuyin = false;  TODO: Implement skipBuyin for cash game cases
    size_t startPos = 0;
    size_t endPos = 0;

    handNumber = getNextNumber(textLine, &startPos, &endPos, ":");
    tournamentNumber = getNextNumber(textLine, &startPos, &endPos, ",");

    //TODO: GET BUY IN PRIZE POOL

    smallBlind = getNextNumber(textLine, &startPos, &endPos, "/");
    bigBlind = getNextNumber(textLine, &startPos, &endPos, ")");
    year = getNextNumber(textLine, &startPos, &endPos, "/");
    month = getNextNumber(textLine, &startPos, &endPos, "/");
    day = getNextNumber(textLine, &startPos, &endPos, " ");

    //TODO: STEP 9 GET TIME

    //FILL currentHand WITH CONVERTED INFO
    currentHand->setHandNumber(std::stoll(handNumber));
    currentHand->setTournamentNumber(std::stoll(tournamentNumber));
    currentHand->setSmallBlind(std::stoi(smallBlind));
    currentHand->setBigBlind(std::stoi(bigBlind));
    currentHand->setYear(std::stoi(year));
    currentHand->setMonth(std::stoi(month));
    currentHand->setDay(std::stoi(day));

}

int PokerTextFile::readHandSeatLine(std::string textLine, Player* activePlayer, Hand* currentHand)
{
    std::string stack;

    if (textLine.find("posts small") != textLine.npos || textLine.find("posts the ante") != textLine.npos)
    {
        return -1; //Special value to indicate we are no longer in seat lines
    }

    if (textLine.find(activePlayer->name()) != textLine.npos)
    {
        size_t startPos = textLine.find_first_of("(");
        size_t endPos = startPos;
        stack = getNextNumber(textLine, &startPos, &endPos, " ");
        return std::stoi(stack);
    }
    int a = currentHand->gain(); //TODO: implement player seat position recording in currentHand

    return a*0;
}

bool PokerTextFile::readBlindLine(std::string textLine, Player* activePlayer, Hand* currentHand)
{
    std::string blind;



    if (textLine.find(activePlayer->name()) != textLine.npos)
    {
        size_t startPos = textLine.find_first_of(":");
        size_t endPos = startPos;
        blind = getNextNumber(textLine, &startPos, &endPos, " ");
        currentHand->setLoss(currentHand->loss() + std::stoi(blind));
    }
    else if (textLine.find("*** HOLE CARDS ***") != textLine.npos)
    {
        return true;
    }

    return false;
}

void PokerTextFile::readHoleCardsLine(std::string textLine, Hand* currentHand)
{
    size_t startPos = textLine.find_first_of("[");
    std::string cardLine = textLine.substr(startPos+1, 5);
    currentHand->setHoleCards(Card(cardLine.substr(0,1), cardLine.substr(1,1)), Card(cardLine.substr(3,1), cardLine.substr(4,1)));
    setHoleCardsRank(currentHand);
}

void PokerTextFile::setHoleCardsRank(Hand* currentHand)
{
    if (currentHand->holeCards().firstCard().value() > currentHand->holeCards().secondCard().value())
    {
        m_nbOfHoleCardsPerRank[currentHand->holeCards().firstCard().value()][currentHand->holeCards().secondCard().value()][currentHand->holeCards().isSuited()];
    }
}

int PokerTextFile::readBetLine(std::string textLine, Player* activePlayer, Hand* currentHand, Street* currentStreet)
{
    size_t startPos = textLine.find_first_of(":");
    size_t endPos = startPos;

    //TODO: Account for the case where a player name has one of the keywords in it

    if (textLine.find(activePlayer->name()) != textLine.npos)
    {
        if (textLine.find("bets") != textLine.npos)
        {
            return -std::stoi(getNextNumber(textLine, &startPos, &endPos, " "));
        }
        else if (textLine.find("calls") != textLine.npos)
        {
            return -std::stoi(getNextNumber(textLine, &startPos, &endPos, " "));
        }
        else if (textLine.find("raises") != textLine.npos)
        {
            return -std::stoi(getNextNumber(textLine, &startPos, &endPos, " "));
        }
        else if (textLine.find("folds") != textLine.npos)
        {
            m_nbOfHoleCardsPerRank[currentHand->holeCards().higherValue()][currentHand->holeCards().lowerValue()][currentHand->holeCards().isSuited()].incrFold(*currentStreet); //Count a win for this card rank
            return -1; //TODO: Find another special value to return
        }
        else if (textLine.find("collected") != textLine.npos)
        {
            startPos = textLine.find_first_of(" ");
            endPos = startPos;
            m_nbOfHoleCardsPerRank[currentHand->holeCards().higherValue()][currentHand->holeCards().lowerValue()][currentHand->holeCards().isSuited()].incrWins(); //Count a win for this card rank
            return std::stoi(getNextNumber(textLine, &startPos, &endPos, " "));
        }
        else if (textLine.find("checks") != textLine.npos)
        {
            return 0;
        }
        else if (textLine.find("checks") != textLine.npos)
        {
            return 0;
        }
        else if (textLine.find("returned to") != textLine.npos)
        {
            startPos = textLine.find_first_of("(");
            endPos = startPos;
            return std::stoi(getNextNumber(textLine, &startPos, &endPos, " "));;
        }
        else
        {
            return 0;
        }
    }
    else if (textLine.find("*** FLOP ***") != textLine.npos)
    {
        *currentStreet = Street::FLOP;
    }
    else if (textLine.find("*** TURN ***") != textLine.npos)
    {
        *currentStreet = Street::TURN;
    }
    else if (textLine.find("*** RIVER ***") != textLine.npos)
    {
        *currentStreet = Street::RIVER;
    }
    else if (textLine.find("*** SHOW DOWN ***") != textLine.npos)
    {
        *currentStreet = Street::SHOWDOWN;
    }
    else if (textLine.find("SUMMARY") != textLine.npos)
    {
        return -1; //TODO: Change this special value at the same time than folds
    }

    return 0;

}

bool PokerTextFile::seekNextHand(std::ifstream* txtFile)
{
    std::string line = "";

    while (true)
    {
        int currentPos = txtFile->tellg();
        getline(*txtFile, line);

        if (line.find("PokerStars") != line.npos)
        {
            txtFile->seekg(currentPos);
            break;
        }
        else if (txtFile->eof())
        {
            return false;
        }
    }

    return true;
}

std::string PokerTextFile::getNextNumber(std::string textLine, size_t* startPos, size_t* endPos, std::string cutOffChar)
{
    *startPos = textLine.find_first_of("0123456789", *endPos);
    *endPos = textLine.find_first_of(cutOffChar, *startPos);
    return textLine.substr(*startPos, *endPos - *startPos);
}

StatsCounter PokerTextFile::nbOfHoleCardsPerRank(int firstCardRank, int secondCardRank, int suited)
{
    return m_nbOfHoleCardsPerRank[firstCardRank][secondCardRank][suited];
}
