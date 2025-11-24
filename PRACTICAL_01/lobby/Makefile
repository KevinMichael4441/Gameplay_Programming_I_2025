CXX := g++
TARGET := lobby
SRC := ./src/lobby.cpp ./src/lobby_welcome.cpp
INC := -I./include

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(INC) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
