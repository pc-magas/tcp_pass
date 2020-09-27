#include <iostream>
#include "network/network.h"

int main(){
    TCP_Client client('localhost',22);
    TCP_Server server('localhost',9022,client);

    server.listen();
}   