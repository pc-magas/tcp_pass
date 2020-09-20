#include "network.h"

TCP_Server::TCP_Server(std::string address, unsigned int port, TCP_Client client):servSock(::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)),client(client){
    
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

void TCP_Server::listen(){

    struct sockaddr_in RecvServAddr;     /* Address that performed a connection to the server */
    socklen_t recvServLen = (socklen_t)sizeof(RecvServAddr);
    int recvServSock;                    /* Socket descriptor for client */

    for (;;) {
    
       if ((recvServSock = accept(this->servSock, (struct sockaddr *) &RecvServAddr, &recvServLen)) < 0) {
           std::clog<<"Failed to fetch"<<std::endl;
           continue;
       }
       std::clog << "Handling connection from: " << inet_ntoa(RecvServAddr.sin_addr) << std::endl;

       int client_socket = this->client.connect(this);
       this->socket_map.insert(std::pair<int,int>(client_socket,recvServSock));

       auto handler = [](int recvServSock, TCP_Client client, int client_socket){
           std::vector<char> storage(BUFFLEN);
           char *const buffer = storage.data();
           int recvSize=0;
        
           while ((recvSize = ::recv(recvServSock, buffer, BUFFLEN-1, 0)) > 0) {
                client.send(buffer,recvSize,client_socket);
           }

           return;
       };

       std::thread handleConnectionThread(handler, recvServSock, client, client_socket);
       handleConnectionThread.detach();
    }
}

void TCP_Server::sendBackData(int clientSock, const char* data, int size){

    std::map<int,int>::iterator i =  this->socket_map.find(clientSock);
    int servSock;

    if( i == this->socket_map.end()){
        return;
    }
    
    servSock = i.second;
    send(servSock,data,size,0);
}

TCP_Server::~TCP_Server(){
 ::close(this->servSock);
}


