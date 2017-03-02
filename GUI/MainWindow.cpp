#include "GUI/MainWindow.h"
#include "Parsing/StatsCounter.h"
#include "TabGraph.h"


MainWindow::MainWindow() : m_tab1(0), m_tab2(0), m_loadButton(0), m_activePlayer(0), m_cardRankInput(0), m_lbTotal(0), m_lbWinRate(0), m_lbShowdown(0), m_lbFoldPreFlop(0), m_lbFoldFlop(0), m_lbFoldTurn(0), m_lbFoldRiver(0)
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

    m_tab1 = new TabGraph;
    m_tab2 = new TabHoleCardsRank(&m_pokerTextFile);

    tabWidget->addTab(m_tab1, "Graph");
    tabWidget->addTab(m_tab2, "Stats");

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
    }
}

void MainWindow::displaySessionPlot()
{
    m_tab1->updateGraph(m_pokerTextFile.getFileHands());
}
