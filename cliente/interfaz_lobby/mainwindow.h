#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QListWidget>
#include <QDialog>
#include <string>
#include <list>
#include "../lobby.h"

class VentanaEsperando : public QMainWindow {
    Q_OBJECT

public:
    explicit VentanaEsperando(QWidget *parent = nullptr);
    ~VentanaEsperando();

private:
    QLabel* statusLabel;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(Lobby* lobby, QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void crear_partida_clicked();
    void cargar_partida_clicked();
    void mostrarListaPartidas(); 

signals:
    void crear_partida(int jugadores);
    void cargar_partida();
    void unirse_partida(int id_partida);

public slots:
    void actualizarListaPartidas(const std::list<int>& partidas);

private:
    Lobby* lobby; 
    QPushButton* crear_partida_Button;
    QPushButton* cargar_partida_Button;
    QListWidget* partidasListWidget; 
    QLabel* statusLabel;
    QComboBox* jugadoresComboBox;
};

#endif // MAINWINDOW_H
