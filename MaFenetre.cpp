// MaFenetre.cpp

#include "MaFenetre.h"
#include "PokerTextFile.h"
#include <string>
#include <QDebug>
#include <QException>

MaFenetre::MaFenetre() : QWidget()
{
    m_fileName = "";
    setFixedSize(230, 120);

    m_boutonDialogue = new QPushButton("Ouvrir la boîte de dialogue", this);
    m_boutonDialogue->move(40, 50);

    QObject::connect(m_boutonDialogue, SIGNAL(clicked()), this, SLOT(ouvrirDialogue()));
}

void MaFenetre::ouvrirDialogue()
{
    //m_fileName = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Texte (*.txt)");
    try
    {
        qDebug() << std::stoul("salut90");
    }
    catch(QException const& e)
    {
        qDebug() << e;
    }
    //pokerTextFile.load(m_fileName.toStdString(), "Bobsleigh");
}
