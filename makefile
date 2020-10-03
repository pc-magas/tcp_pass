CPP=g++
BUILD_PATH=./build
CCFLAGS:=-pthread -Wall -std=c++11

.PHONY: default

default: run

build_server: 
	${CPP} ${CCFLAGS} -c ./src/network/tcp_server.cpp -o ${BUILD_PATH}/tcp_server.o

build: build_server
	${CPP} ${CCFLAGS} -o ${BUILD_PATH}/tcp_proxy ${BUILD_PATH}/tcp_server.o ./src/main.cpp

run: build
	${BUILD_PATH}/tcp_proxy