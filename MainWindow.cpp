#include "MainWindow.h"


MainWindow::MainWindow() : m_activePlayer(0), m_loadButton(0), m_sessionPlot(0), m_lbTournamentNb(0), m_lbNbOfHands(0), m_lbNetGain(0)
{

    m_fileName = "";
    m_activePlayer = new Player("Bobsleigh", 1500);

    setMinimumSize(QSize(600,400));

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

    //Tab1
    m_sessionPlot = new QCustomPlot();
    //sessionPlot->setMinimumSize(QSize(300,300));
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    m_sessionPlot->addGraph();
    m_sessionPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    m_sessionPlot->xAxis->setLabel("x");
    m_sessionPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    m_sessionPlot->xAxis->setRange(-1, 1);
    m_sessionPlot->yAxis->setRange(0, 1);
    m_sessionPlot->replot();

    m_lbTournamentNb = new QLabel("Tournament Number: ");
    m_lbNbOfHands = new QLabel("Hands: ");
    m_lbNetGain = new QLabel("Net Gain: ");

    QGridLayout* layoutTab1 = new QGridLayout;
    layoutTab1->addWidget(m_sessionPlot, 0,0,3,2);
    layoutTab1->addWidget(m_lbTournamentNb,0,2);
    layoutTab1->addWidget(m_lbNbOfHands, 1,2);
    layoutTab1->addWidget(m_lbNetGain, 2,2);
    tab1->setLayout(layoutTab1);
    tabWidget->addTab(tab1, "Stats");


    //Tab2
    QPushButton* testButton = new QPushButton("In construction");
    QHBoxLayout* layoutTab2 = new QHBoxLayout;
    layoutTab2->addWidget(testButton);
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
}
