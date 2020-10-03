#include "network.h"

TCP_Client::TCP_Client(std::string address, unsigned int port):host_entry(gethostbyname(address.c_str())){
    
    if(port == 0){
        throw NetworkException(std::string("Client Error: port cannot be 0"));
    }

    std::memset(&(this->sin),0,sizeof(sin));
    this->sin.sin_port =  htons(port);
    
    if(host_entry){
        std::memcpy(&(this->sin),host_entry->h_addr,host_entry->h_length);
    } else {
        this->sin.sin_addr.s_addr =  inet_addr(address.c_str());
    }
    
    if( ((this->sin).sin_addr.s_addr) == INVALID_ADDRESS){
        throw NetworkException(std::string("Client Error: Could not find the address for " + address));
    }
}

TCP_Client::~TCP_Client(){
}

int TCP_Client::connect(){

    int clientSocket = socket(PF_INET, SOCK_STREAM, 6);

    if(clientSocket < 0 ){
        throw NetworkException(std::string("Client Error: unable to allocate client socket"));
    }

    if( ( ::connect( clientSocket, (struct sockaddr*)&sin, sizeof(sin) ) ) < 0 ){
        throw NetworkException(std::string("Client Error: unable to Connect"));
    }

    return clientSocket;
}

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


TCP_Server::TCP_Server(std::string address, unsigned int port, TCP_Client client, Socket_Transfer transfer):servSock(::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)),client(client),handler(transfer){
    
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
    int serverSocket;                    /* Socket descriptor for client */

    for (;;) {
    
       if ((serverSocket = accept(this->servSock, (struct sockaddr *) &RecvServAddr, &recvServLen)) < 0) {
           std::clog<<"Failed to fetch"<<std::endl;
           continue;
       }
       std::clog << "Handling connection from: " << inet_ntoa(RecvServAddr.sin_addr) << std::endl;

       int clientSocket = this->client.connect();
       this->handler.setConnectionPair(serverSocket, clientSocket);
    }
}

TCP_Server::~TCP_Server(){
 ::close(this->servSock);
}


