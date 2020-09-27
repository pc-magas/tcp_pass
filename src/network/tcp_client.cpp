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
    // for (auto const& client : this->sendback_data_server){
    //     ::close(client.first);
    // }
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