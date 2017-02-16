// MaFenetre.cpp

#include "MaFenetre.h"
#include "PokerTextFile.h"
#include <string>
#include <QDebug>
#include "qcustomplot.h"
#include <QHBoxLayout>


MaFenetre::MaFenetre() : QWidget()
{
    m_fileName = "";
    setFixedSize(400,400);

    m_boutonDialogue = new QPushButton("Ouvrir la boîte de dialogue", this);

    QCustomPlot* pokerPlot = new QCustomPlot(this);
    //pokerPlot->setGeometry(0,0,400,400);

    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    pokerPlot->addGraph();
    pokerPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    pokerPlot->xAxis->setLabel("x");
    pokerPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    pokerPlot->xAxis->setRange(-1, 1);
    pokerPlot->yAxis->setRange(0, 1);
    pokerPlot->replot();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(pokerPlot);
    layout->addWidget(m_boutonDialogue);
    setLayout(layout);

    QObject::connect(m_boutonDialogue, SIGNAL(clicked()), this, SLOT(ouvrirDialogue()));
}

void MaFenetre::ouvrirDialogue()
{
    m_fileName = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Texte (*.txt)");
    pokerTextFile.load(m_fileName.toStdString(), "Bobsleigh");
}
