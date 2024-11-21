#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QDialog>
#include <QVBoxLayout> 
#include "../lobby.h"
#include <string>  


class VentanaEsperando : public QMainWindow {
    Q_OBJECT

public:
    explicit VentanaEsperando(QWidget *parent = nullptr);
    virtual ~VentanaEsperando() override;

private:
    QLabel *statusLabel;
};


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(Lobby* lobby, QWidget *parent = nullptr);

signals:
    void crear_partida(const std::string& mapaSeleccionado);
    void cargar_partida(); 

private slots:
    void crear_partida_clicked();
    void cargar_partida_clicked();

private:
    Lobby* lobby;
    QPushButton *crear_partida_Button;
    QPushButton *cargar_partida_Button;
    QLabel *statusLabel;
    QComboBox *mapaComboBox; 
};

#endif // MAINWINDOW_H
