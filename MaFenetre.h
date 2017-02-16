// MaFenetre.h

#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include "PokerTextFile.h"
#include "Player.h"



class MaFenetre : public QWidget
{
    Q_OBJECT

    public:
    MaFenetre();
    ~MaFenetre();


    public slots:
    void ouvrirDialogue();

    private:

    QPushButton *m_boutonDialogue;
    QString m_fileName;
    PokerTextFile pokerTextFile;
    Player* m_activePlayer;

};

#endif
