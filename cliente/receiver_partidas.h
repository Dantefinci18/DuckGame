#ifndef RECEIVER_PARTIDAS_H
#define RECEIVER_PARTIDAS_H

#include "../common/common_thread.h"
#include "cliente_protocolo.h"
#include "interfaz_lobby/mainwindow.h"

class ReceiverPartidas : public Thread {
    private:
        ClienteProtocolo& protocolo;
        MainWindow mainWindow;
        
    public:
        explicit ReceiverPartidas(ClienteProtocolo& protocolo, MainWindow& mainWindow);
        void run() override;

};

#endif