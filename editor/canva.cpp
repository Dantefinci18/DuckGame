// canva.cpp
#include "canva.h"

namespace fs = std::filesystem;
Canva::Canva(QWidget *parent, QVBoxLayout *layout)
    : QWidget(parent), layout(layout), drawable(DrawableType::None) {
        setAttribute(Qt::WA_TransparentForMouseEvents, false);
        setStyleSheet("background-color: transparent;");
    }

void Canva::set_drawable(DrawableType drawable) {
    this->drawable = drawable;
}

void Canva::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        bool okWidth;
        int platformWidth = this->platformWidth->text().toInt(&okWidth);
        
        bool okHeight;
        int platformHeight = this->platformHeight->text().toInt(&okHeight);  // Convert input to int
        if (drawable == DrawableType::PlatformType && (!okWidth || !okHeight)) {
            return;
        } 
        std::shared_ptr<Drawable> drawObject = DrawableUtils::get_drawable(event->pos().x(), event->pos().y(), platformWidth, platformHeight, drawable);
        if (drawObject) {
            QLabel *obj = new QLabel(this);
            objects[drawObject] = obj;
            obj->setPixmap(QPixmap(drawObject->image.c_str()).scaled(drawObject->w, drawObject->h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            obj->setGeometry(drawObject->x, drawObject->y - drawObject->h, drawObject->w, drawObject->h);
            obj->show();
        }
    }
    else if (event->button() == Qt::RightButton) {
        delete_object_at(event->pos().x(), event->pos().y());
    }
}

void Canva::set_platform_width(QLineEdit* width) {
    this->platformWidth = width;
}

void Canva::set_platform_height(QLineEdit* height) {
    this->platformHeight = height;
}

void Canva::save() {
     // Construct YAML node
    YAML::Node root;
    for (auto& object : objects) {
        root["collidables"].push_back(object.first->to_yaml());
    }

    std::string dir_path = "../server/mapas";
    fs::create_directories(dir_path);

    int map_number = 1;
    std::string filename;
    do {
        filename = dir_path + "/mapa_" + std::to_string(map_number++) + ".yaml";
    } while (fs::exists(filename));

    std::ofstream fout(filename);
    fout << root;
}

void Canva::delete_object_at(int x, int y) {
    for (auto it = objects.begin(); it != objects.end(); ) {
        if (it->first->is_within(x, y)) {
            QLabel* label = it->second;
            if (label) {
                label->deleteLater();  // Use deleteLater() to avoid immediate deletion issues
            }
            it = objects.erase(it);  // Erase returns the next iterator
            
            return;  // Assuming you only want to delete one object
        } else {
            ++it;  // Move to the next element
        }
    }
}