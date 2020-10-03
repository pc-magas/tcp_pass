#include <iostream>
#include "network/network.h"

int main(int argc, char **argv){
    TCP_Client client((std::string)"localhost",22);
    Socket_Transfer transfer;
    TCP_Server server((std::string)"localhost",9022,client,transfer);

    server.listen();
}   