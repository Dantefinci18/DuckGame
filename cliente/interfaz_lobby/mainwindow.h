#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QScrollArea>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QDialog>
#include <QVBoxLayout> 
#include <QTextEdit>
#include <string>  

class VentanaNuevaPartida: public QMainWindow {
    Q_OBJECT
    private:
        QTextEdit *nombrePartidaInput;
        QPushButton *crear_Button;
        QPushButton *volver_Button;
        QComboBox *mapaComboBox;
        QComboBox *cantidadDeJugadores_ComboBox;
    
    private slots:
        void crear_clicked();
        void volver_clicked();

    signals:
        void crear_partida(
            const std::string& nombre, const std::string& mapaSeleccionado, const unsigned int cantidad_de_jugadores);
        
        void volver();

    public:
        explicit VentanaNuevaPartida(QWidget *parent = nullptr);
};

class VentanaEsperando : public QMainWindow {
    Q_OBJECT

public:
    explicit VentanaEsperando(QWidget *parent = nullptr);

private:
    QLabel *statusLabel;
};


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void agregar_partida(std::string partida);

signals:
    void crear_partida();
    void cargar_partida(); 

private slots:
    void crear_partida_clicked();
    void cargar_partida_clicked();

private:
    QPushButton *crear_partida_Button;
    QPushButton *cargar_partida_Button;
    QScrollArea *scrollArea;
    QWidget *scrollContent;
    QVBoxLayout *scrollLayout;


};

#endif // MAINWINDOW_H
