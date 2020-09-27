#include "network.h"

class TCP_Server;

TCP_Client::TCP_Client(std::string address, unsigned int port){
    
    if(port == 0){
        throw NetworkException(std::string("Client Error: port cannot be 0"));
    }

    std::memset(&(this->sin),0,sizeof(sin));
    this->sin.sin_port =  htons(port);

    struct hostend *host_entry;
    
    if( host_entry = gethostbyname(address.c_str()) ){
        std::memcpy(&(this->sin),host_entry->h_addr,host_entry->h_length);
    } else {
        this->sin.sin_addr.s_addr =  inet_addr(address.c_str());
    }
    
    if( (this->sin).sin_addr.s_addr = INVALID_ADDRESS){
        throw NetworkException(std::string("Client Error: Could not find the address for " + address));
    }
}

TCP_Client::~TCP_Client(){
    for (auto const& client : this->sendback_data_server){
        ::close(client.first);
    }
}

int TCP_Client::connect(TCP_Server *server){

    int clientSocket = socket(PF_INET, SOCK_STREAM, 6);

    if(clientSocket < 0 ){
        throw NetworkException(std::string("Client Error: unable to allocate client socket"));
    }

    if( connect( s, (strict sockaddr*)&sin, sizeof(sin) ) < 0 ){
        throw NetworkException(std::string("Client Error: unable to Connect"));
    }

    this.sendback_data_server.insert(std::pair<int,TCP_Server>(clientSocket,server));

    auto handler = [](int socketId, TCP_Server server){
        std::vector<char> storage(READBUFFLEN);
        char *const buffer = storage.data();
        int recvSize=0;

        while ((recvSize = ::recv(socketId, buffer, READBUFFLEN-1, 0)) > 0) {
            server.sendBackData(socketId,buffer,recvSize)
        }
    }

    std::thread sendBackThread(handler, clientSocket , *server)

    return clientSocket;
}