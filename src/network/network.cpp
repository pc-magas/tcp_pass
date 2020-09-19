#include "network.h"


TCP_Server::TCP_Server(string address, int port, TCP_Client client)::servSock(::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)),client(client){
    
    if (this->servSock < 0) {
        throw NetworkException(std::string("SOCKET Error: could not create basic socket"));
    }

    std::memset(&this->ServAddr,0,sizeof(this->ServAddr));

    ServAddr.sin_family = AF_INET;
    ServAddr.sin_addr.s_addr = inet_addr(address.c_str());
    ServAddr.sin_port = htons(port);

    
    if (bind(this->servSock, (struct sockaddr *) &this->ServAddr, sizeof(this->ServAddr)) < 0) {
        throw NetworkException(std::string("SOCKET Error: Failed to bind a socket"));
    }

    if (::listen(this->servSock, MAXPENDING) < 0) {
        throw NetworkException(std::string("SOCKET Error: Failed to Listen"));
    }
}

void TCPServer::listen(){

    struct sockaddr_in RecvServAddr;     /* Address that performed a connection to the server */
    socklen_t recvServLen = (socklen_t)sizeof(ClntAddr);
    int recvServSock;                    /* Socket descriptor for client */

    for (;;) {
    
       if ((recvServSock = accept(servSock, (struct sockaddr *) &ClntAddr, &clntLen)) < 0) {
           std::clog<<"Failed to fetch"<<std::endl;
           continue;
       }
       std::clog << "Handling connection from: " << inet_ntoa(RecvServAddr.sin_addr) << std::endl;

       int client_socket = client->connect(this->sendBackData);
       this->socket_map->insert(pair<int,int>(client_socket,recvServSock));

       auto handler = [](int recvServSock, TCP_Client client){
           std::vector<char> storage(buffLen);
           char *const buffer = storage.data();
           int recvSize=0;
        
           while ((recvSize = ::recv(socketid, buffer, this->buffLen-1, 0)) > 0) {
                client->send(receivedBuffer,recvSize,client_socket);
           }
       }

       std::thread handleConnectionThread(handler, recvServSock, client_socket);
       handleConnectionThread.detach();
    }
}

void TCPServer::sendBackData(int clientSock, const char* data, int size){
    int servSock = this->socket_map-[clientSock];

    
}

TCPServer::~TCPServer(){
 ::close(this->servSock);
 this->client->close();
}