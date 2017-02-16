// MaFenetre.cpp

#include "MaFenetre.h"
#include "PokerTextFile.h"
#include <string>
#include <QDebug>
#include "Player.h"


MaFenetre::MaFenetre() : QWidget(), m_activePlayer(0)
{
    m_fileName = "";
    setFixedSize(230, 120);

    m_boutonDialogue = new QPushButton("Ouvrir la boîte de dialogue", this);
    m_boutonDialogue->move(40, 50);

    m_activePlayer = new Player("Bobsleigh", 1500);

    QObject::connect(m_boutonDialogue, SIGNAL(clicked()), this, SLOT(ouvrirDialogue()));
}

MaFenetre::~MaFenetre()
{
    delete m_activePlayer;
}


void MaFenetre::ouvrirDialogue()
{
    m_fileName = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Texte (*.txt)");
    pokerTextFile.load(m_fileName.toStdString(), m_activePlayer);
}

