#include "TabGraph.h"
#include "Parsing/PokerTextFile.h"

TabGraph::TabGraph()
{
    //Tab1 (Graph)
    m_sessionPlot = new QCustomPlot();
    //sessionPlot->setMinimumSize(QSize(300,300));

    // create graph and assign data to it:
    m_sessionPlot->addGraph();

    // give the axes some labels:
    m_sessionPlot->xAxis->setLabel("Hands");
    m_sessionPlot->yAxis->setLabel("Chips");
    // set axes ranges, so we see all data:
    m_sessionPlot->xAxis->setRange(-1, 1);
    m_sessionPlot->yAxis->setRange(0, 1);
    m_sessionPlot->replot();

    m_lbTournamentNb = new QLabel("Tournament Number: ");
    m_lbNbOfHands = new QLabel("Hands: ");
    m_lbNetGain = new QLabel("Net Gain: ");
    m_lbAvgGain = new QLabel("Average Gain: ");

    QGridLayout* layoutTab1 = new QGridLayout;
    layoutTab1->addWidget(m_sessionPlot, 0,0,4,2);
    layoutTab1->addWidget(m_lbTournamentNb,0,2);
    layoutTab1->addWidget(m_lbNbOfHands, 1,2);
    layoutTab1->addWidget(m_lbNetGain, 2,2);
    layoutTab1->addWidget(m_lbAvgGain, 3,2);

    this->setLayout(layoutTab1);
    //tabWidget->addTab(tab1, "Graph");

}

void TabGraph::updateGraph(std::vector<Hand> handsVector)
{
    int bleh = handsVector.size()+1;

    QVector<double> x(bleh), y(handsVector.size()+1);
    x[0] = 0;
    y[0] = 0;
    x[1] = 1;
    y[1] = handsVector[1].net();

    for(size_t i=2; i<handsVector.size()+1; i++)
    {
        x[i] = i;
        y[i] = y[i-1] + handsVector[i-2].net();
    }

    m_sessionPlot->graph(0)->setData(x, y);
    m_sessionPlot->rescaleAxes();
    m_sessionPlot->replot();

    m_lbTournamentNb->setText("Tournament Number: " + QString::number((handsVector.back()).tournamentNumber()));
    m_lbNbOfHands->setText("Hands: " + QString::number(handsVector.size()));
    m_lbNetGain->setText("Net Gain: " + QString::number(y[handsVector.size()]));
    m_lbAvgGain->setText("Average Gain: "+ QString::number(y[handsVector.size()]/handsVector.size()));
}

