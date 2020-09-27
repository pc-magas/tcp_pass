#include "network.h"

void Socket_Transfer::setConnectionPair(int server_socket, int client_socket){
    std::thread serverToClient(transferSocket,server_socket,client_socket);
    std::thread clientToServer(transferSocket,server_socket,client_socket);
}


void transferSocket(int source, int dest){
    char buffer[READBUFFLEN];
    while(true){
        std::memset(&buffer,0,READBUFFLEN);
        size_t read_size = recv(source, buffer, READBUFFLEN, 0);

        // @todo check whether causes unexpected termimation
        if(read_size <= 0){
            close(source);
            close(dest);
            return;
        }

        send(dest,buffer,read_size,0);
    }
}