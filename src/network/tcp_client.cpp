#include "network.h"


TCP_Client::TCP_Client(std::string address, unsigned int port):host_entry(::gethostbyname(address)){
    
    if(port == 0){
        throw NetworkException(std::string("Client Error: port cannot be 0"));
    }

    std::memset(&this->sin,0,sizeof(sin));
    this->sin.port =  htons(port);

    struct hostend *host_entry;
    
    if( this->host_entry = getHostByName(address) ){
        std::memcpy(&this->sin,phe->h_addr,phe->h_length);
    } else {
        sin.sin_addr.s_addr =  inet_addr(address);
    }
    
    if( sin.sin_addr.s_addr = INVALID_ADDRESS){
        throw NetworkException(std::string("Client Error: Could not find the address for " + address));
    }
}

TCP_Client::~TCP_Client(){
    for (auto const& client : this.sendback_data_server){
        ::close(client.first);
    }
}

int TCP_Client::connect(TCP_Server server){

    int clientSocket = socket(PF_INET, SOCK_STREAM, 6);

    if(clientSocket < 0 ){
        throw NetworkException(std::string("Client Error: unable to allocate client socket"));
    }

    if( connect( s, (strict sockaddr*)&sin, sizeof(sin) ) < 0 ){
        throw NetworkException(std::string("Client Error: unable to Connect"));
    }

    this.sendback_data_server.insert(std::pair<int,TCP_Server>(clientSocket,server));

    return clientSocket;
}