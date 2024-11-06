#include "mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>

MainWindow::MainWindow(Lobby* lobby, QWidget *parent) :
    QMainWindow(parent),
    lobby(lobby),
    crear_partida_Button(new QPushButton("Crear partida", this)),
    statusLabel(new QLabel("Esperando conexión...", this))
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
    layout->addWidget(crear_partida_Button);
    layout->addWidget(statusLabel);

    connect(crear_partida_Button, &QPushButton::clicked, this, &MainWindow::crear_partida_clicked);
}

MainWindow::~MainWindow() {
}

void MainWindow::crear_partida_clicked() {
    statusLabel->setText("Partida creada");
    emit crear_partida();  
}
