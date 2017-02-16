#include "MainWindow.h"


MainWindow::MainWindow() : m_activePlayer(0)
{

    m_fileName = "";
    m_activePlayer = new Player("Bobsleigh", 1500);

    setFixedSize(230, 120);

    m_loadButton = new QPushButton("Load PokerStars file", this);
    m_loadButton->move(40, 50);

    QGridLayout* centralLayout = new QGridLayout;
    centralLayout->addWidget(m_loadButton);

    QWidget* centralZone = new QWidget;
    centralZone->setLayout(centralLayout);
    setCentralWidget(centralZone);

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
    pokerTextFile.load(m_fileName.toStdString(), m_activePlayer);
}
