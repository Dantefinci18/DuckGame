#include "map_editor.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPixmap>
#include <string>  

MapEditor::MapEditor(QWidget *parent) :
    QMainWindow(parent),
    select_box_button(new QPushButton("Box", this))
{
    setWindowTitle("Lobby");
    setFixedSize(1000, 600);
    
    QLabel *background = new QLabel(this);
    background->setPixmap(QPixmap(":/images_editor/images_editor/forest.png").scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    background->setGeometry(0, 0, 800, 600);  

    select_box_button->setGeometry(50, 850, 100, 30);
    background->lower(); 

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    layout->addWidget(select_box_button);
    connect(select_box_button, &QPushButton::clicked, this, &MapEditor::select_box_clicked);
}

void MapEditor::select_box_clicked() {
    std::cout << "here" << std::endl;
}