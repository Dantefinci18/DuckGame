#include "mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QListWidget>
#include <QPixmap>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QEventLoop> 
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
    partidasListWidget(new QListWidget(this)),
    statusLabel(new QLabel("Esperando conexión...", this)),
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
    jugadoresComboBox->addItem("Seleccione la cantidad de jugadores para la partida");
    
    for (int i = 2; i <= 10; ++i) {
        jugadoresComboBox->addItem(QString::number(i));
    }

    layout->addWidget(jugadoresComboBox);
    layout->addWidget(crear_partida_Button);
    layout->addSpacing(20);
    layout->addWidget(cargar_partida_Button);
    layout->addWidget(statusLabel);
    
    connect(crear_partida_Button, &QPushButton::clicked, this, &MainWindow::crear_partida_clicked);
    connect(cargar_partida_Button, &QPushButton::clicked, this, &MainWindow::cargar_partida_clicked);
}

void MainWindow::crear_partida_clicked() {
    int index = jugadoresComboBox->currentIndex();
    if (index == 0) {
        return;
    }
    int numeroJugadores = jugadoresComboBox->currentIndex() + 1;

    statusLabel->setText("Partida creada: " +  QString::number(numeroJugadores) + " jugadores.");
    emit crear_partida(numeroJugadores);
}

void MainWindow::cargar_partida_clicked(){
    statusLabel->setText("Cargando partida seleccionada...");
    emit cargar_partida();
}

void MainWindow::actualizarListaPartidas(const std::list<int>& partidas) {
    partidasListWidget->clear(); 
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

        connect(unirseButton, &QPushButton::clicked, this, [this, nombrePartida, dialogoPartidas]() {
            int numeroPartida = nombrePartida.toInt();
            dialogoPartidas->accept();         
            emit unirse_partida(numeroPartida); 
            
        });

        layout->addWidget(partidaWidget);  
    }

    QDialogButtonBox* botonera = new QDialogButtonBox(QDialogButtonBox::Close, dialogoPartidas);
    layout->addWidget(botonera);

    connect(botonera, &QDialogButtonBox::rejected, dialogoPartidas, &QDialog::accept);

    dialogoPartidas->exec(); 
}

void MainWindow::mostrarVentanaEsperando(int id_partida) {
    dialogoEsperando = new QDialog(this);
    dialogoEsperando->setWindowTitle("Esperando Jugadores");

    QLabel* label = new QLabel(QString("Esperando jugadores para comenzar partida\nID PARTIDA: %1").arg(id_partida), dialogoEsperando);
    QVBoxLayout* layout = new QVBoxLayout(dialogoEsperando);
    layout->addWidget(label);
    dialogoEsperando->setLayout(layout);

    dialogoEsperando->show(); 
}




void MainWindow::cerrarVentanaEsperando() {
    if (dialogoEsperando != nullptr) {
        dialogoEsperando->close();  
        dialogoEsperando = nullptr; 
    }
}

