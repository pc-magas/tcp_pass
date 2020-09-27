CPP=g++
BUILD_PATH=./build
CCFLAGS:=-pthread -Wall -std=c++11
LINK_LIBS:= -lsocket

.PHONY: default

default: run

build_network:
	${CPP} ${CCFLAGS} ${LINK_LIBS} ./src/network/tcp_server.cpp ./src/network/tcp_client.cpp ./src/network/socket_transfer.cpp -o ${BUILD_PATH}/network.o

build: build_network
	${CPP} ${CCFLAGS} -o ${BUILD_PATH}/tcp_proxy ${BUILD_PATH}/network.o ./src/main.cpp

run: build
	${BUILD_PATH}/tcp_proxy