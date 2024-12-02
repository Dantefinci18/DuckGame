#include <QApplication>
#include "map_editor.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);  
    MapEditor editor;    
    editor.show();               
    return app.exec();  
}
