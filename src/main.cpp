#include <iostream>
#include "network/network.h"

int main(int argc, char **argv){
    TCP_Client client((std::string)"192.168.20.3",22);
    Socket_Transfer transfer;
    TCP_Server server((std::string)"localhost",9052,client,transfer);

    server.listen();
}   