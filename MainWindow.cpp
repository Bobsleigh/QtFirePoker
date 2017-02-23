#include "MainWindow.h"


MainWindow::MainWindow() : m_activePlayer(0), m_loadButton(0), m_sessionPlot(0), m_lbTournamentNb(0), m_lbNbOfHands(0), m_lbNetGain(0), m_lbAvgGain(0)
{

    m_fileName = "";
    m_activePlayer = new Player("Bobsleigh", 1500);

    setMinimumSize(QSize(1000,600));

    m_loadButton = new QPushButton("Load PokerStars file", this);

    QGridLayout* centralLayout = new QGridLayout;
    centralLayout->addWidget(m_loadButton,1,2);

    QWidget* centralZone = new QWidget;
    centralZone->setLayout(centralLayout);
    setCentralWidget(centralZone);

    QTabWidget* tabWidget = new QTabWidget(centralZone);
    tabWidget->setGeometry(10,10,300,300);
    centralLayout->addWidget(tabWidget, 0,0, 1, 3);

    QWidget* tab1 = new QWidget();
    QWidget* tab2 = new QWidget();

    //Tab1 (Stats)
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

    tab1->setLayout(layoutTab1);
    tabWidget->addTab(tab1, "Stats");

    //Tab2 (In Construction)


    QLineEdit* cardRankInput = new QLineEdit();
    QPushButton* testButton = new QPushButton("In construction");
    QHBoxLayout* layoutTab2 = new QHBoxLayout;

    //Left part
    QGridLayout* layoutRankButtons = new QGridLayout;
    layoutRankButtons->addWidget(cardRankInput);
    QWidget* widgetRankButtons = new QWidget;
    widgetRankButtons->setLayout(layoutRankButtons);

    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(1);
    widgetRankButtons->setSizePolicy(spLeft);

    //Right part
    QGridLayout* layoutStatsLabels = new QGridLayout;
    layoutStatsLabels->addWidget(testButton);
    QWidget* widgetStatsLabels = new QWidget;
    widgetStatsLabels->setLayout(layoutStatsLabels);

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(1);
    widgetStatsLabels->setSizePolicy(spRight);

    layoutTab2->addWidget(widgetRankButtons);
    layoutTab2->addWidget(widgetStatsLabels);
    tab2->setLayout(layoutTab2);
    tabWidget->addTab(tab2, "In construction");

    QObject::connect(m_loadButton, SIGNAL(clicked()), this, SLOT(loadButtonClicked()));

    //Build the menu bar
    QMenu* fileMenu = menuBar()->addMenu("&File");
    QAction* loadAction = new QAction("&Load File", this);
    fileMenu->addAction(loadAction);
    QAction* quitAction = new QAction("&Quit", this);
    fileMenu->addAction(quitAction);

    QObject::connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(loadAction, SIGNAL(triggered()), this, SLOT(loadButtonClicked()));

}

MainWindow::~MainWindow()
{
    delete m_activePlayer;
}

void MainWindow::loadButtonClicked()
{
    m_fileName = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Texte (*.txt)");
    if (m_pokerTextFile.load(m_fileName.toStdString(), m_activePlayer))
    {
        displaySessionPlot();
        m_sessionPlot->replot();

    }
}

void MainWindow::displaySessionPlot()
{
    std::vector<Hand> handsVector = m_pokerTextFile.getFileHands();

    int bleh = handsVector.size()+1;

    QVector<double> x(bleh), y(handsVector.size()+1);
    x[0] = 0;
    y[0] = 0;
    x[1] = 1;
    y[1] = handsVector[1].net();

    for(int i=2; i<handsVector.size()+1; i++)
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
