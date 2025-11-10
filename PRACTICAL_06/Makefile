CC 			:= gcc
CFLAGS		:= -std=c99 -Wall -Wextra -Werror -g -I.

MSG_START	:= "Build Started"
MSG_END		:= "Build Complete"
MSG_CLEAN	:= "Cleaning up"

BUILD_DIR	:= ./bin
SRC_DIR		:= ./src

ifeq ($(OS),Windows_NT)
    os  := Windows
	TARGET		:= ${BUILD_DIR}/missiledefence.exe
else
	os := $(shell uname -s)
	TARGET		:= ${BUILD_DIR}/missiledefence.bin
endif

SRC			:= ${SRC_DIR}/main.c

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