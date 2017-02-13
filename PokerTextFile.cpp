#include "PokerTextFile.h"
#include <fstream>
#include <QMessageBox>
#include "MaFenetre.h"
#include <QDebug>



PokerTextFile::PokerTextFile() : m_name("")
{
}

int PokerTextFile::readSingleHand(std::ifstream* txtFile, QString activePlayer, bool& stillReading)
{
    qDebug() << m_name;
    stillReading = false;
    return 1;
}

void PokerTextFile::load(QString fileName, QString activePlayer)
{
    m_name = fileName;

    std::ifstream txtFile(fileName.toStdString());

    if (txtFile)
    {
        bool stillReading(true);
        while(stillReading)
        {
            m_hands.push_back(readSingleHand(&txtFile, activePlayer, stillReading));
        }
    }
}



