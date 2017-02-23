#ifndef TABHOLECARDSRANK_H
#define TABHOLECARDSRANK_H

#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include "Parsing/PokerTextFile.h"

class TabHoleCardsRank : public QWidget
{
    Q_OBJECT

public:
    TabHoleCardsRank();
    TabHoleCardsRank(PokerTextFile* textFile);

public slots:
    void cardRankEntered();

private:
    QLineEdit* m_cardRankInput;
    QLabel* m_lbTotal;
    QLabel* m_lbWinRate;
    QLabel* m_lbShowdown;
    QLabel* m_lbFoldPreFlop;
    QLabel* m_lbFoldFlop;
    QLabel* m_lbFoldTurn;
    QLabel* m_lbFoldRiver;

    PokerTextFile* m_pokerTextFile;

};

#endif // TABHOLECARDSRANK_H
