#include "mainwindow.h"
#include <QScrollArea>
#include <QPlainTextEdit>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPixmap>
#include <string> 
#include <QTextEdit> 

VentanaNuevaPartida::VentanaNuevaPartida(QWidget *parent):
    QMainWindow(parent),
    nombrePartidaInput(new QTextEdit()),
    crear_Button(new QPushButton("Crear", this)),
    volver_Button(new QPushButton("Volver", this)),
    mapaComboBox(new QComboBox(this)),
    cantidadDeJugadores_ComboBox(new QComboBox(this))    {

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QWidget *layoutContainer = new QWidget(centralWidget);
    layoutContainer->setGeometry(0, 0, 400, 220);
    QVBoxLayout *layout = new QVBoxLayout(layoutContainer);
    setWindowTitle("Crear Partida");
    setFixedSize(400, 300);

    QLabel *labelNombrePartida = new QLabel("Establecer nombre de partida:", this);
    layout->addWidget(labelNombrePartida);
    labelNombrePartida->setFixedSize(200, 50);
    layout->addWidget(nombrePartidaInput);

    mapaComboBox->addItem("Mapa 1");
    mapaComboBox->addItem("Mapa 2");
    QLabel *labelMapa = new QLabel("Elegir Mapa:", this);
    layout->addWidget(labelMapa);
    layout->addWidget(mapaComboBox);
    
    QLabel *labelCatntidadJugadores = new QLabel("Elegir cantidad de jugadores:", this);
    layout->addWidget(labelCatntidadJugadores);
    cantidadDeJugadores_ComboBox->addItem("2");
    cantidadDeJugadores_ComboBox->addItem("3");
    layout->addWidget(cantidadDeJugadores_ComboBox);
    
    crear_Button->setGeometry(290, 250, 100, 30);
    volver_Button->setGeometry(10, 250, 100, 30);
    crear_Button->setParent(centralWidget);
    volver_Button->setParent(centralWidget);

    connect(crear_Button, &QPushButton::clicked, this, &VentanaNuevaPartida::crear_clicked);
    connect(volver_Button, &QPushButton::clicked, this, &VentanaNuevaPartida::volver_clicked);
}

void VentanaNuevaPartida::crear_clicked() {
    std::string nombre = nombrePartidaInput->toPlainText().toStdString();
    
    QString mapaSeleccionadoQString = mapaComboBox->currentText();
    std::string mapaSeleccionado = mapaSeleccionadoQString.toStdString();
    
    unsigned int cantidad_de_jugadores = std::stoi(cantidadDeJugadores_ComboBox->currentText().toStdString());
    
    emit crear_partida(nombre,mapaSeleccionado,cantidad_de_jugadores);
}

void VentanaNuevaPartida::volver_clicked() {
    emit volver();
}

VentanaEsperando::VentanaEsperando(QWidget *parent) :
    QMainWindow(parent),
    statusLabel(new QLabel("Esperando conexión...", this))
{
    setFixedSize(200, 100);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setGeometry(0, 50, 300, 50);
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    crear_partida_Button(new QPushButton("Crear partida", this)),
    cargar_partida_Button(new QPushButton("Cargar partida", this)),
    scrollArea(new QScrollArea(this)),
    scrollContent(new QWidget(scrollArea)),
    scrollLayout(new QVBoxLayout(scrollContent))

{
    setWindowTitle("Lobby");
    setFixedSize(800, 600);

    QLabel *background = new QLabel(this);
    background->setPixmap(QPixmap(":/images/images/background_duckgame.jpg").scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    background->setGeometry(0, 0, 800, 600);  
    background->lower();

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    crear_partida_Button->setParent(centralWidget);
    crear_partida_Button->setGeometry(10, 90, 200, 30); 
    cargar_partida_Button->setGeometry(10, 130, 200, 30);
    
    scrollArea->setGeometry(10, 170, 400, 300);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setStyleSheet("background-color: rgba(0, 0, 0, 80%);");

    scrollContent->setLayout(scrollLayout);
    scrollContent->setStyleSheet("background: transparent;");
    scrollArea->setWidget(scrollContent);

    connect(crear_partida_Button, &QPushButton::clicked, this, &MainWindow::crear_partida_clicked);
    connect(cargar_partida_Button, &QPushButton::clicked, this, &MainWindow::cargar_partida_clicked);
}


void MainWindow::crear_partida_clicked() {
    emit crear_partida();
}

void MainWindow::cargar_partida_clicked(){
    emit cargar_partida();
}

void MainWindow::agregar_partida(std::string partida){
        QWidget *rowWidget = new QWidget();
        QHBoxLayout *rowLayout = new QHBoxLayout(rowWidget);

        QLabel *rowLabel = new QLabel(partida.data(), rowWidget);
        rowLabel->setStyleSheet("color: white; font-size: 14px;");

        QPushButton *joinButton = new QPushButton("Unirse", rowWidget);
         joinButton->setStyleSheet(
        "background-color: white;"
        "color: black;"
        "border: 2px solid black;"
        "padding: 5px 10px;"
        "border-radius: 5px;"
        "font-size: 12px;"
        "font-weight: bold;"
    );

        rowLayout->addWidget(rowLabel);
        rowLayout->addWidget(joinButton);
        rowLayout->addStretch();
        rowWidget->setLayout(rowLayout);

        scrollLayout->insertWidget(0,rowWidget);
}