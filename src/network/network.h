#ifndef TCPSERVER
#define TCPSERVER

#include <memory>
#include <string>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>


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


class TCP_Server {
    public:
        TCP_Server(string address, int port, TCP_Client client);
        ~TCP_Server(){};
    private:
        private:
        int port;
        //Socket file Descriptor
        int servSock;
        struct sockaddr_in ServAddr;
        TCP_Client client;
        map<int,int> socket_map;
        bool sendBackData(int clientSock, const char* data, int size);
}

class TCP_Client {
    public:
        TCP_Client(std::string address, int port)
        ~TCP_Client(){};
        int send(const char* receivedBuffer, int recvSize);
        auto onReceive();
        void close();
        auto setReceiveHandler();
}

#endif