#include "receiver_partidas.h"

ReceiverPartidas::ReceiverPartidas(ClienteProtocolo& protocolo, MainWindow& mainWindow): 
    protocolo(protocolo),mainWindow(mainWindow){}

ReceiverPartidas::run(){
    while(_keep_running){
        Evento evento = protocolo.recibir_evento();

        if(evento == Evento::EventoActualizarPartidas){
            mainWindow.agregar_partida();
        
        }else{
            _keep_running = false;
        }
    }
}

