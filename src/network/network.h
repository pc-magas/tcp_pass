#ifndef TCPSERVER
#define TCPSERVER

#ifndef INVALID_ADDRESS
#define INVALID_ADDRESS  0xffffffff
#endif

class TCP_Client;

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <unistd.h>

#include <cstring>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/tcp.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAXPENDING 100
#define READBUFFLEN 1024

class Exception {
    public:
    Exception(std::string message):message(message){}
    std::string getMessage();
    private:
    std::string message;
};

class NetworkException:public Exception {
    public:
    NetworkException(std::string message) : Exception(message) {}
};

class TCP_Client {
    public:
        TCP_Client(std::string address, unsigned int port);
        ~TCP_Client();
        int send(const char* receivedBuffer, int recvSize, int client_socket);
        int connect(TCP_Server *server);
        void close();
    private:
        struct sockaddr_in sin;
        std::map<int,TCP_Server> sendback_data_server;
};


class TCP_Server {
    public:
        TCP_Server(std::string address, unsigned int port, TCP_Client client);
        ~TCP_Server();
    private:
        //Socket file Descriptor
        int servSock;
        struct sockaddr_in ServAddr;
        TCP_Client client;
        std::map<int,int> socket_map;
        void listen();
        void sendBackData(int clientSock, const char* data, int size);
};



#endif