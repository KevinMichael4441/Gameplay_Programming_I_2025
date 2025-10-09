# Compiler
CXX			:= g++

# CPP standard
CXXFLAGS 	:= -std=c++11 -Wall -Wextra -Werror -g -I.

MSG_START	:= "Build Started"
MSG_END		:= "Build Complete"
MSG_CLEAN	:= "Cleaning up"

BUILD_DIR	:= ./bin
SRC_DIR		:= ./src


ifeq ($(OS),Windows_NT)
    os  := Windows
	TARGET		:= ${BUILD_DIR}/game.exe
else
	os := $(shell uname -s)
	TARGET		:= ${BUILD_DIR}/game.bin
endif

SRC			:= ${SRC_DIR}/main.cpp ${SRC_DIR}/Player.cpp ${SRC_DIR}/NPC.cpp ${SRC_DIR}/GameObject.cpp

all			:= build

build:
	@echo ${MSG_START}

	#remove directory if it exits and then create directory
	rm -rf ${BUILD_DIR} || true

	#create bin directory
	mkdir ${BUILD_DIR}

	${CXX} ${CXXFLAGS} -o ${TARGET} ${SRC}
	@echo ${MSG_END}
	./${TARGET}

.PHONY: clean

clean:
	@echo ${MSG_CLEAN}
	rm -rf ${BUILD_DIR} || true