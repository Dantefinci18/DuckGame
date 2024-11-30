#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QDialog>
#include <QVBoxLayout> 
#include <QMouseEvent>
#include <QPalette>
#include <QLineEdit>
#include <iostream>
#include <memory>
#include <vector>
#include "drawable.h"
#include "canva.h"
#include "../common/common_screen_utils.h"
class MapEditor : public QMainWindow {
    Q_OBJECT
public:
    explicit MapEditor(QWidget *parent = nullptr);

public slots:
    void select_box_clicked();
    void select_spawn_place_clicked();
    void select_platform_clicked();
    void save_button_clicked();

private:
    QPushButton *select_box_button;
    QPushButton *select_spawn_place_button;
    QPushButton *select_platform_button;
    QPushButton *save_button;
    Canva* canva;
    std::unique_ptr<Drawable> selectedDrawable;
    std::vector<std::unique_ptr<Drawable>> drawn_objects;
    QPalette get_selected_palette();
    QPalette get_unselected_palette();
};
#endif
