#include "PokerTextFile.h"
#include "Hand.h"
#include <fstream>
#include <QMessageBox>
#include "MaFenetre.h"
#include <QDebug>



PokerTextFile::PokerTextFile() : m_name("")
{
}


void PokerTextFile::load(std::string fileName, std::string activePlayer)
{
    m_name = fileName;

    std::ifstream txtFile(fileName);

    if (txtFile)
    {
        bool stillReading(true);
        while(stillReading)
        {
            m_hands.push_back(readSingleHand(&txtFile, activePlayer, stillReading));
        }
    }
}

Hand PokerTextFile::readSingleHand(std::ifstream* txtFile, std::string activePlayer, bool& stillReading)
{
    int playerStack = -1;
    Hand currentHand;

    std::string textLine;
    int filePosition(0);

    getline(*txtFile, textLine);
    readHandStartingLine(textLine);

    //STEP 1 - READ SEATS
    while(true)
    {
        filePosition = txtFile->tellg();
        getline(*txtFile, textLine);

        //playerStack = readHandSeatLine(textLine, activePlayer);
        if (playerStack == -1) //Special value when done reading hand seat lines
        {
            txtFile->seekg(filePosition);
            break;
        }
    }

    //STEP 2 - READ BLINDS
    while(true)
    {
        getline(*txtFile, textLine);

        //int loss = readBlindLine(textLine, activePlayer);
        int loss = -1;
        if (loss == -1) //Special value when done reading blind lines
        {
            break;
        }
        currentHand.setLoss(currentHand.loss() + loss);
    }

    //STEP 3 - READ HOLE CARDS
    getline(*txtFile, textLine);
    //currentHand.setHoleCards(readHoleCardsLine(textLine, activePlayer));

    //STEP 4 - READ BETS
    while(true)
    {
        getline(*txtFile, textLine);
        int value(0);
        //int value = readBetLine(textLine, activePlayer);

        if (value == 0)
        {
            break;
        }
        else if (value == -1)
        {
            continue;
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

    //TODO: stack line missing

    stillReading = false;

    return currentHand;
}

void PokerTextFile::readHandStartingLine(std::string textLine)
{

}

void readHandSeatLine(std::string textLine, std::string activePlayer)
{
    std::string stringChips;

}
