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

class Lobby;  // Declaración adelantada de la clase Lobby

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
    void mostrarListaPartidas();  // Método para mostrar la lista de partidas en un QDialog

signals:
    void crear_partida(const std::string& mapa, int jugadores);
    void cargar_partida();

public slots:
    void actualizarListaPartidas(const std::list<int>& partidas);

private:
    Lobby* lobby;  // Puntero a la clase Lobby
    QPushButton* crear_partida_Button;
    QPushButton* cargar_partida_Button;
    QListWidget* partidasListWidget;  // Lista de partidas
    QLabel* statusLabel;
    QComboBox* mapaComboBox;
    QComboBox* jugadoresComboBox;
};

#endif // MAINWINDOW_H
