#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include "PokerTextFile.h"
#include "Player.h"
#include "qcustomplot.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    MainWindow();
    ~MainWindow();

    public slots:
    void loadButtonClicked();
    void cardRankEntered();

    private:
    QPushButton *m_loadButton;
    QString m_fileName;
    PokerTextFile m_pokerTextFile;
    Player* m_activePlayer;
    QCustomPlot* m_sessionPlot;

    QLabel* m_lbTournamentNb;
    QLabel* m_lbNbOfHands;
    QLabel* m_lbNetGain;
    QLabel* m_lbAvgGain;
    QLineEdit* m_cardRankInput;

    //Card rank stats section
    QLabel* m_lbWinRate;

    void displaySessionPlot();
};

#endif // MAINWINDOW_H
