#ifndef TABGRAPH_H
#define TABGRAPH_H

#include "GUI/qcustomplot.h"
#include "Parsing/Hand.h"

class TabGraph : public QWidget
{
public:
    TabGraph();
    void updateGraph(std::vector<Hand> handsVector);

private:
    QCustomPlot* m_sessionPlot;
    QLabel* m_lbTournamentNb;
    QLabel* m_lbNbOfHands;
    QLabel* m_lbNetGain;
    QLabel* m_lbAvgGain;
};

#endif // TABGRAPH_H
