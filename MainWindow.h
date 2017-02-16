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

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    MainWindow();
    ~MainWindow();

    public slots:
    void loadButtonClicked();

    private:
    QPushButton *m_loadButton;
    QString m_fileName;
    PokerTextFile pokerTextFile;
    Player* m_activePlayer;
};

#endif // MAINWINDOW_H
