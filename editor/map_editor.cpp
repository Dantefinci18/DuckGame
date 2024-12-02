#include "map_editor.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include <QComboBox>
#include <QPixmap>

#include <string>  

MapEditor::MapEditor(QWidget *parent) :
    QMainWindow(parent),
    select_box_button(new QPushButton("Box", this)),
    select_spawn_place_button(new QPushButton("Spawn place", this)),
    select_platform_button(new QPushButton("Platform", this)),
    save_button(new QPushButton("Save map", this))
{
    setWindowTitle("Lobby");
    setFixedSize(ANCHO_VENTANA + 200, 600);
    
    // Set up the background
    QLabel *background = new QLabel(this);
    background->setPixmap(QPixmap(":/images_editor/images_editor/forest.png").scaled(ANCHO_VENTANA, ALTO_VENTANA, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    background->setGeometry(0, 0, ANCHO_VENTANA, ALTO_VENTANA);  
    background->lower();  // Send background behind other widgets

    //Platform input
    QLineEdit *widthInput = new QLineEdit(this);
    QLineEdit *heightInput = new QLineEdit(this);
    QLabel *widthHeightLabel = new QLabel("Platform width and height:", this);
    QLabel *deleteLabel = new QLabel("Right click to delete", this);
    // Set up the button
    select_box_button->setGeometry(850, 50, 100, 30);
    select_spawn_place_button->setGeometry(850, 100, 100, 30);
    select_platform_button->setGeometry(850, 150, 100, 30);
    
    widthInput->setGeometry(810, 250, 85, 30);
    heightInput->setGeometry(900, 250, 85, 30);
    save_button->setGeometry(810, 400, 180, 30);
    widthHeightLabel->setGeometry(800, 200, 200, 30);
    deleteLabel->setGeometry(800, 550, 200, 30);
    QVBoxLayout *layout = new QVBoxLayout;
    
    layout->addWidget(select_box_button);
    layout->addWidget(select_spawn_place_button);
    layout->addWidget(select_platform_button);
    layout->addWidget(widthInput);
    layout->addWidget(heightInput);
    layout->addWidget(widthHeightLabel);

    canva = new Canva(this, layout);
    canva->setGeometry(0, 0, ANCHO_VENTANA, ALTO_VENTANA);  
    canva->set_platform_width(widthInput);
    canva->set_platform_height(heightInput);

    layout->addWidget(canva);
    // Connect button signal
    connect(select_box_button, &QPushButton::clicked, this, &MapEditor::select_box_clicked);
    connect(select_spawn_place_button, &QPushButton::clicked, this, &MapEditor::select_spawn_place_clicked);
    connect(select_platform_button, &QPushButton::clicked, this, &MapEditor::select_platform_clicked);
    connect(save_button, &QPushButton::clicked, this, &MapEditor::save_button_clicked);
}

void MapEditor::select_box_clicked() {
    select_box_button->setPalette(get_selected_palette());
    select_spawn_place_button->setPalette(get_unselected_palette());
    select_platform_button->setPalette(get_unselected_palette());
    canva->set_drawable(DrawableType::BoxType);
}

void MapEditor::select_spawn_place_clicked() {
    select_box_button->setPalette(get_unselected_palette());
    select_spawn_place_button->setPalette(get_selected_palette());
    select_platform_button->setPalette(get_unselected_palette());
    canva->set_drawable(DrawableType::SpawnPlaceType);
}

void MapEditor::select_platform_clicked() {
    select_box_button->setPalette(get_unselected_palette());
    select_spawn_place_button->setPalette(get_unselected_palette());
    select_platform_button->setPalette(get_selected_palette());
    canva->set_drawable(DrawableType::PlatformType);
}

void MapEditor::save_button_clicked() {
    canva->save();
}

QPalette MapEditor::get_selected_palette() {
    QPalette selected=palette();   
    selected.setBrush(QPalette::Button,Qt::green);  
    selected.setBrush(QPalette::ButtonText, Qt::black);
    return selected;
}

QPalette MapEditor::get_unselected_palette() {
    QPalette unselected=palette();   
    unselected.setBrush(QPalette::Button,Qt::white);  
    unselected.setBrush(QPalette::ButtonText, Qt::black);
    return unselected;
}