#include "mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPixmap>
#include <string>  

MainWindow::MainWindow(Lobby* lobby, QWidget *parent) :
    QMainWindow(parent),
    lobby(lobby),
    crear_partida_Button(new QPushButton("Crear partida", this)),
    statusLabel(new QLabel("Esperando conexión...", this)),
    mapaComboBox(new QComboBox(this))
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
    layout->addWidget(mapaComboBox);
    
    layout->addWidget(crear_partida_Button);
    layout->addWidget(statusLabel);

    connect(crear_partida_Button, &QPushButton::clicked, this, &MainWindow::crear_partida_clicked);
}

MainWindow::~MainWindow() {}

void MainWindow::crear_partida_clicked() {
    QString mapaSeleccionadoQString = mapaComboBox->currentText();
    std::string mapaSeleccionado = mapaSeleccionadoQString.toStdString();
    
    statusLabel->setText("Partida creada: " + mapaSeleccionadoQString);
    
    emit crear_partida(mapaSeleccionado);
}
