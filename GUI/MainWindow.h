#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include "Parsing/PokerTextFile.h"
#include "Parsing/Player.h"
#include "GUI/qcustomplot.h"
#include "TabGraph.h"
#include "TabHoleCardsRank.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    MainWindow();
    ~MainWindow();

    public slots:
    void loadButtonClicked();

    private:
    QPushButton* m_loadButton;
    QString m_fileName;
    PokerTextFile m_pokerTextFile;
    Player* m_activePlayer;

    TabGraph* m_tab1;
    TabHoleCardsRank* m_tab2;

    //Card rank stats section
    QLineEdit* m_cardRankInput;
    QLabel* m_lbTotal;
    QLabel* m_lbWinRate;
    QLabel* m_lbShowdown;
    QLabel* m_lbFoldPreFlop;
    QLabel* m_lbFoldFlop;
    QLabel* m_lbFoldTurn;
    QLabel* m_lbFoldRiver;

    void displaySessionPlot();

};

#endif // MAINWINDOW_H
