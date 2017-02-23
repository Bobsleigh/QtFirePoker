#include "GUI/MainWindow.h"
#include "Parsing/StatsCounter.h"


MainWindow::MainWindow() : m_activePlayer(0), m_loadButton(0), m_sessionPlot(0), m_lbTournamentNb(0), m_lbNbOfHands(0), m_lbNetGain(0), m_lbAvgGain(0), m_cardRankInput(0), m_lbWinRate(0), m_lbShowdown(0), m_lbFoldPreFlop(0), m_lbFoldFlop(0), m_lbFoldTurn(0), m_lbFoldRiver(0)
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


    m_cardRankInput = new QLineEdit();
    m_cardRankInput->setMaxLength(3);

    QHBoxLayout* layoutTab2 = new QHBoxLayout;

    //Left part
    QLabel* lbInputBox = new QLabel("Hole Cards Ranking:");
    QLabel* lbInputInfo = new QLabel("Type a hole cards rank in the box above to display related stats. A hole cards rank must be in the standard format of [HigherCard][LowerCard][OffsuitOrSuited]. Use 'o' or 's' for the suit character. Ten, Jack, Queen King and Ace must be written as a letter. Pokets must exclude the suit character. Valid examples: A2s, T4o, AA, QJs, 97o, 22");
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
    m_lbWinRate = new QLabel("% win:");
    m_lbFoldPreFlop = new QLabel("% fold preflop:");
    m_lbFoldFlop = new QLabel("% fold flop:");
    m_lbFoldTurn = new QLabel("% fold turn:");
    m_lbFoldRiver = new QLabel("% fold river:");
    m_lbShowdown = new QLabel("% to showdown:");

    QGridLayout* layoutStatsLabels = new QGridLayout;
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
    QObject::connect(m_cardRankInput, SIGNAL(returnPressed()), this, SLOT(cardRankEntered()));
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

void MainWindow::cardRankEntered()
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
        StatsCounter stats = m_pokerTextFile.nbOfHoleCardsPerRank(firstCardRank, secondCardRank, suited);

        m_lbWinRate->setText("% win: " + QString::number(stats.wins()));
        m_lbFoldPreFlop->setText("% fold preflop: " + QString::number(stats.foldPreflop()));
        m_lbFoldFlop->setText("% fold flop: " + QString::number(stats.foldFlop()));
        m_lbFoldTurn->setText("% fold turn: " + QString::number(stats.foldTurn()));
        m_lbFoldRiver->setText("% fold river: " + QString::number(stats.foldRiver()));
        m_lbShowdown->setText("% to showdown: " + QString::number(stats.showdowns()));
    }
}


