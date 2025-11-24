CXX		:= g++
MSG_START	:="Build Started"
MSG_END		:= "Buld Ended"
MSG_CLEAN	:= "Cleaning Up!"
BUILD_DIR	:= ./bin
SRC_DIR		:= ./src
TARGET		:= ${BUILD_DIR}/sampleapp.bin
SRC		:= ${SRC_DIR}/main.cpp ${SRC_DIR}/sample_function.cpp

all:	build

CXXFLAGS	:= -Wall
DEBUG		:= 1


ifeq ($(DEBUG), 1)
	CXXFLAGS += -g
else
	CXXFLAGS += -02
endif

build:
	@echo ${MSG_START}
	${CXX} -o ${TARGET} ${SRC} -I.
	@echo ${MSG_END}
	./${TARGET}

clean:
	@echo ${MSG_CLEAN}
	rm ${TARGET}
