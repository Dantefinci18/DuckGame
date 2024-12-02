// canva.h
#ifndef CANVA_H
#define CANVA_H

#include <QWidget>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QLineEdit>
#include "drawable.h"
#include <iostream>
#include "drawable_utils.h"
#include "../common/common_screen_utils.h"
#include <unordered_map>
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include <fstream>
#include <memory>
class Canva : public QWidget {
    Q_OBJECT

public:
    explicit Canva(QWidget *parent = nullptr, QVBoxLayout *layout = nullptr);

    void set_drawable(DrawableType drawable);
    void set_platform_width(QLineEdit* width);
    void set_platform_height(QLineEdit* height);
    void save();
protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QVBoxLayout* layout;
    QLineEdit* platformWidth;
    QLineEdit* platformHeight;
    DrawableType drawable;
    std::unordered_map<std::shared_ptr<Drawable>, QLabel*> objects;
    void delete_object_at(int x, int y);
    
};

#endif // CANVA_H