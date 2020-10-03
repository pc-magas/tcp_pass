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

#define MAXPENDING 5
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
        int connect();
        void close();
    private:
        struct sockaddr_in sin;
        struct hostent *host_entry;
};

/**
* Syncronizes data between 2 sockets
*/
void transferSocket(int source, int dest);

/**
* Tranfers data Between server and client socket
*/
class Socket_Transfer{
    public:
        void setConnectionPair(int server_socket, int client_socket);
};

class TCP_Server {
    public:
        TCP_Server(std::string address, unsigned int port, TCP_Client client, Socket_Transfer transfer);
        ~TCP_Server();
        void listen();
    private:
        //Socket file Descriptor
        int servSock;
        struct sockaddr_in ServAddr;
        TCP_Client client;
        Socket_Transfer handler;
        
};


#endif