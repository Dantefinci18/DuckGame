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
#include <QApplication>
#include <QThread>
#include "../cliente_protocolo.h"
#include "../../common/common_socket.h"
#include "../../server/Collidable.h"
#include "../../server/Platform.h"
#include "../../server/server_leaderboard.h" 

class VentanaCargarPartida : public QMainWindow{
    Q_OBJECT

    private:
        QPushButton *restablecerPartidasButton;
        QPushButton *volverButton;
        QScrollArea *scrollArea;
        QWidget *scrollContent;
        QVBoxLayout *scrollLayout;

    private slots:
        void restablecer_partidas_clicked();
        void volver_clicked();
    
    signals:
        void restablecer_partidas();
        void volver();
        void unirse(int id, std::string partida);

    public:
        explicit VentanaCargarPartida(QWidget *parent = nullptr);
        void agregar_partida(int id,std::string nombre_partida);
};

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
};


class ClienteLobby : public QObject{
    Q_OBJECT

    private:
        QApplication *app;
        MainWindow mainWindow;
        VentanaCargarPartida ventanaCargarPartida;
        VentanaNuevaPartida ventanaNuevaPartida;
        VentanaEsperando ventanaEsperando;
        ClienteProtocolo protocolo;
        std::vector<Collidable*> collidables;
        Leaderboard leaderboard; 
        QThread *receiver;
        int id = 0;
        float x_inicial = 0;
        float y_inicial = 0;
        ColorDuck color = ColorDuck::MAX_COLOR;

        void recibir_eventos();

    public:
        explicit ClienteLobby(int argc, char* argv[], Socket&& skt);
        int run();
        ~ClienteLobby();

};

#endif // MAINWINDOW_H
