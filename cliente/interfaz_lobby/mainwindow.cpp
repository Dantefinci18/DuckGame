#include "mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QListWidget>
#include <QPixmap>
#include <QDialog>
#include <QDialogButtonBox>
#include <string>  

// Ventana de espera (opcional)
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
    partidasListWidget(new QListWidget(this)),  // Lista de partidas
    statusLabel(new QLabel("Esperando conexión...", this)),
    mapaComboBox(new QComboBox(this)),
    jugadoresComboBox(new QComboBox(this))
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
    
    mapaComboBox->addItem("Mapa 1");
    mapaComboBox->addItem("Mapa 2");

    for (int i = 2; i <= 10; ++i) {
        jugadoresComboBox->addItem(QString::number(i));
    }

    // Agregar widgets al layout
    layout->addWidget(mapaComboBox);
    layout->addWidget(jugadoresComboBox);
    layout->addWidget(crear_partida_Button);
    layout->addSpacing(20); // Espaciado entre lista y botón
    layout->addWidget(cargar_partida_Button);
    layout->addWidget(statusLabel);
    
    // Conectar señales y slots
    connect(crear_partida_Button, &QPushButton::clicked, this, &MainWindow::crear_partida_clicked);
    connect(cargar_partida_Button, &QPushButton::clicked, this, &MainWindow::cargar_partida_clicked);
}

void MainWindow::crear_partida_clicked() {
    QString mapaSeleccionadoQString = mapaComboBox->currentText();
    std::string mapaSeleccionado = mapaSeleccionadoQString.toStdString();
    int numeroJugadores = jugadoresComboBox->currentIndex() + 2;

    statusLabel->setText("Partida creada: " + mapaSeleccionadoQString + " con " + QString::number(numeroJugadores) + " jugadores.");
    emit crear_partida(mapaSeleccionado, numeroJugadores);
}

void MainWindow::cargar_partida_clicked(){
    statusLabel->setText("Cargando partida seleccionada...");
    QString partidaSeleccionada = partidasListWidget->currentItem()
                                   ? partidasListWidget->currentItem()->text()
                                   : "Ninguna partida seleccionada";
    
    // Aquí puedes conectar con lógica futura para manejar las partidas
    emit cargar_partida();
}

void MainWindow::actualizarListaPartidas(const std::list<int>& partidas) {
    partidasListWidget->clear();  // Limpiar la lista existente
    for (const auto& partida : partidas) {
        partidasListWidget->addItem(QString::number(partida));  
    }
    mostrarListaPartidas();
}

void MainWindow::mostrarListaPartidas() {
    QDialog* dialogoPartidas = new QDialog(this);
    dialogoPartidas->setWindowTitle("Lista de Partidas");
    dialogoPartidas->setFixedSize(300, 400);

    QVBoxLayout* layout = new QVBoxLayout(dialogoPartidas);

    for (int i = 0; i < partidasListWidget->count(); ++i) {
        QWidget* partidaWidget = new QWidget(dialogoPartidas);
        QHBoxLayout* partidaLayout = new QHBoxLayout(partidaWidget);

        QString nombrePartida = partidasListWidget->item(i)->text();
        QLabel* partidaLabel = new QLabel(nombrePartida, partidaWidget);
        partidaLayout->addWidget(partidaLabel);

        QPushButton* unirseButton = new QPushButton("Unirse", partidaWidget);
        partidaLayout->addWidget(unirseButton);

        connect(unirseButton, &QPushButton::clicked, this, [this, nombrePartida]() {
        });

        layout->addWidget(partidaWidget);  
    }

    QDialogButtonBox* botonera = new QDialogButtonBox(QDialogButtonBox::Close, dialogoPartidas);
    layout->addWidget(botonera);

    connect(botonera, &QDialogButtonBox::rejected, dialogoPartidas, &QDialog::accept);

    dialogoPartidas->exec(); 
}

