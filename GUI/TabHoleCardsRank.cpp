#include "TabHoleCardsRank.h"

TabHoleCardsRank::TabHoleCardsRank() : m_pokerTextFile(0)
{
    TabHoleCardsRank(m_pokerTextFile);
}

TabHoleCardsRank::TabHoleCardsRank(PokerTextFile* textFile) : m_pokerTextFile(textFile)
{
    //Tab2 (Hole cards rank stats)
    m_cardRankInput = new QLineEdit();
    m_cardRankInput->setMaxLength(3);

    QHBoxLayout* layoutTab2 = new QHBoxLayout;

    //Left part
    QLabel* lbInputBox = new QLabel("Hole Cards Ranking:");
    QLabel* lbInputInfo = new QLabel("Type a hole cards rank in the box above to display related stats. A hole cards rank must be in the standard format of [HigherCard][LowerCard][OffsuitOrSuited]. Use 'o' or 's' for the suit character. Ten, Jack, Queen, King and Ace must be written as a letter. Pokets must exclude the suit character. Valid examples: A2s, T4o, AA, QJs, 97o, 22");
    lbInputInfo->setWordWrap(true);
    QGridLayout* layoutRankButtons = new QGridLayout;
    layoutRankButtons->addWidget(lbInputInfo, 1, 0, 1, 2);
    layoutRankButtons->addWidget(lbInputBox, 0, 0);
    layoutRankButtons->addWidget(m_cardRankInput, 0, 1);
    QWidget* widgetRankButtons = new QWidget;
    widgetRankButtons->setLayout(layoutRankButtons);

    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(1);
    widgetRankButtons->setSizePolicy(spLeft);

    //Right part
    m_lbTotal = new QLabel("Hands: ");
    m_lbWinRate = new QLabel("% win: ");
    m_lbFoldPreFlop = new QLabel("% fold preflop: ");
    m_lbFoldFlop = new QLabel("% fold flop: ");
    m_lbFoldTurn = new QLabel("% fold turn: ");
    m_lbFoldRiver = new QLabel("% fold river: ");
    m_lbShowdown = new QLabel("% to showdown: ");

    QGridLayout* layoutStatsLabels = new QGridLayout;
    layoutStatsLabels->addWidget(m_lbTotal);
    layoutStatsLabels->addWidget(m_lbWinRate);
    layoutStatsLabels->addWidget(m_lbFoldPreFlop);
    layoutStatsLabels->addWidget(m_lbFoldFlop);
    layoutStatsLabels->addWidget(m_lbFoldTurn);
    layoutStatsLabels->addWidget(m_lbFoldRiver);
    layoutStatsLabels->addWidget(m_lbShowdown);

    QWidget* widgetStatsLabels = new QWidget;
    widgetStatsLabels->setLayout(layoutStatsLabels);

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(1);
    widgetStatsLabels->setSizePolicy(spRight);

    layoutTab2->addWidget(widgetRankButtons);
    layoutTab2->addWidget(widgetStatsLabels);
    this->setLayout(layoutTab2);

    QObject::connect(m_cardRankInput, SIGNAL(returnPressed()), this, SLOT(cardRankEntered()));
}


void TabHoleCardsRank::cardRankEntered()
{
    int firstCardRank = Card::cardLetterToNumber(m_cardRankInput->text().left(1).toStdString());
    int secondCardRank = Card::cardLetterToNumber(m_cardRankInput->text().mid(1,1).toStdString());
    int suited = Card::cardSuitToNumber(m_cardRankInput->text().right(1).toStdString());

    if (firstCardRank == secondCardRank)
    {
        suited = 0;
    }
    else if (firstCardRank < secondCardRank)
    {
        int temp = firstCardRank;
        firstCardRank = secondCardRank;
        secondCardRank = temp;
    }

    if (firstCardRank == -1 || secondCardRank == -1 || suited == -1)
    {
        QMessageBox::critical(this, "Erreur", "Utilisez un format valide (exemples: KQs, A2o, T8s, JJ)");

        m_cardRankInput->clear();
    }
    else
    {
        StatsCounter stats = m_pokerTextFile->nbOfHoleCardsPerRank(firstCardRank, secondCardRank, suited);
        m_lbTotal->setText("Hands: " + QString::number(stats.total()));

        if (stats.total() != 0)
        {
            m_lbWinRate->setText("% win: " + QString::number(stats.wins()/stats.total()));
            m_lbFoldPreFlop->setText("% fold preflop: " + QString::number(stats.foldPreflop()/stats.total()));
            m_lbFoldFlop->setText("% fold flop: " + QString::number(stats.foldFlop()/stats.total()));
            m_lbFoldTurn->setText("% fold turn: " + QString::number(stats.foldTurn()/stats.total()));
            m_lbFoldRiver->setText("% fold river: " + QString::number(stats.foldRiver()/stats.total()));
            m_lbShowdown->setText("% to showdown: " + QString::number(stats.showdowns()/stats.total()));
        }
        else
        {
            m_lbWinRate->setText("% win: 0");
            m_lbFoldPreFlop->setText("% fold preflop: 0");
            m_lbFoldFlop->setText("% fold flop: 0");
            m_lbFoldTurn->setText("% fold turn: 0");
            m_lbFoldRiver->setText("% fold river: 0");
            m_lbShowdown->setText("% to showdown: 0");
        }
    }
}

