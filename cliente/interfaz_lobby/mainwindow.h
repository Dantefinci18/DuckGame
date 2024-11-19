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

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(Lobby* lobby, QWidget *parent = nullptr);
    void mostrar_ventana_espera(bool mostrar);

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
    QDialog *ventanaEspera;  
};

#endif // MAINWINDOW_H
