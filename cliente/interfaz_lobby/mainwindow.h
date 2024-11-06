#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "../lobby.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(Lobby* lobby, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void crear_partida(); 

private slots:
    void crear_partida_clicked();

private:
    Lobby* lobby;
    QPushButton *crear_partida_Button;
    QLabel *statusLabel;
};

#endif // MAINWINDOW_H