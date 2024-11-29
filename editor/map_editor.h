#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QDialog>
#include <QVBoxLayout> 
#include <QMouseEvent>
#include <iostream>
class MapEditor : public QMainWindow {
    Q_OBJECT
public:
    explicit MapEditor(QWidget *parent = nullptr);

public slots:
    void select_box_clicked();

private:
    QPushButton *select_platform_button;
    QPushButton *select_box_button;
    QPushButton *select_spawn_place_button;
    QPushButton *delete_button;
};
#endif
