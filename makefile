CPP=g++
BUILD_PATH=./build
CCFLAGS:=-pthread -Wall -std=c++11
LINK_LIBS:= -lsocket

build_network:
	${CPP} ${CCFLAGS} ${LINK_LIBS} -c ./src/network/network.cpp -o ${BUILD_PATH}/network.o