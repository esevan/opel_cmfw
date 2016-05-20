INC=./inc
SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin
LIB=-luv
CC=g++


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ -c $< -I$(INC) $(LIB)

_OBJ=cmfw_wfd.o tmp_control.o
OBJ=$(patsubst %, $(OBJ_DIR)/%, $(_OBJ))



test: $(SRC_DIR)/test.cpp $(OBJ)
	$(CC) -o $(BIN_DIR)/$@ $^ -I$(INC) $(LIB)

all : test
clean :
	rm -f $(OBJ)

