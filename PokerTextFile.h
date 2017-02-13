#ifndef POKERTEXTFILE_H
#define POKERTEXTFILE_H

#include <QVector>
#include <QString>


class PokerTextFile
{
    public:
    PokerTextFile();
    void load(QString fileName, QString activePlayer);
    int readSingleHand(std::ifstream* txtFile, QString activePlayer, bool& stillReading);

    private:
    QVector<int> m_hands;
    QString m_name;

};

#endif // POKERTEXTFILE_H
