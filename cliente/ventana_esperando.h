
#ifndef VENTANA_ESPERANDO_H
#define VENTANA_ESPERANDO_H

#include <QMainWindow>
#include <QLabel>  

class VentanaEsperando : public QMainWindow {
    Q_OBJECT

public:
    explicit VentanaEsperando(QWidget *parent = nullptr);
    virtual ~VentanaEsperando() override;

private:
    QLabel *statusLabel;
};

#endif