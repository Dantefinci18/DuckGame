#include "mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPixmap>
#include <string>  

VentanaEsperando::VentanaEsperando(QWidget *parent) :
    QMainWindow(parent),
    statusLabel(new QLabel("Esperando conexión...", this))
{
    setFixedSize(200, 100);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setGeometry(0, 50, 300, 50);
}

VentanaEsperando::~VentanaEsperando() {}

MainWindow::MainWindow(Lobby* lobby, QWidget *parent) :
    QMainWindow(parent),
    lobby(lobby),
    crear_partida_Button(new QPushButton("Crear partida", this)),
    cargar_partida_Button(new QPushButton("Cargar partida", this)),
    statusLabel(new QLabel("Esperando conexión...", this)),
    mapaComboBox(new QComboBox(this)),
    jugadoresComboBox(new QComboBox(this)) // Inicialización del combo de jugadores
{
    setWindowTitle("Lobby");
    setFixedSize(800, 600);

    QLabel *background = new QLabel(this);
    background->setPixmap(QPixmap(":/images/images/background_duckgame.jpg").scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    background->setGeometry(0, 0, 800, 600);  
    background->lower(); 

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    // Agregar opciones al combo de mapas
    mapaComboBox->addItem("Mapa 1");
    mapaComboBox->addItem("Mapa 2");

    // Agregar opciones al combo de número de jugadores (1 a 10)
    for (int i = 1; i <= 10; ++i) {
        jugadoresComboBox->addItem(QString::number(i)); // Agrega los números de 1 a 10
    }

    // Agregar widgets al layout
    layout->addWidget(mapaComboBox);
    layout->addWidget(jugadoresComboBox); // Se añade el combo de jugadores
    layout->addWidget(crear_partida_Button);
    layout->addWidget(cargar_partida_Button);
    layout->addWidget(statusLabel);
    
    // Conectar señales y slots
    connect(crear_partida_Button, &QPushButton::clicked, this, &MainWindow::crear_partida_clicked);
    connect(cargar_partida_Button, &QPushButton::clicked, this, &MainWindow::cargar_partida_clicked);
}

void MainWindow::crear_partida_clicked() {
    // Obtener el mapa seleccionado
    QString mapaSeleccionadoQString = mapaComboBox->currentText();
    std::string mapaSeleccionado = mapaSeleccionadoQString.toStdString();

    // Obtener el número de jugadores seleccionado
    int numeroJugadores = jugadoresComboBox->currentIndex() + 1; // Los índices empiezan en 0, pero el número de jugadores va de 1 a 10

    // Actualizar la etiqueta de estado
    statusLabel->setText("Partida creada: " + mapaSeleccionadoQString + " con " + QString::number(numeroJugadores) + " jugadores.");

    // Emitir la señal para crear la partida
    emit crear_partida(mapaSeleccionado, numeroJugadores);
}

void MainWindow::cargar_partida_clicked(){
    emit cargar_partida();
}
