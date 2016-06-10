INC=./inc
SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin
LIB=-luv -lbluetooth -std=c++11
CC=g++


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ -c $< -I$(INC) $(LIB)

_OBJ=cmfw_wfd.o tmp_control.o opel_cmfw.o
OBJ=$(patsubst %, $(OBJ_DIR)/%, $(_OBJ))

all : test

$(OBJ_DIR)/cmfw_bt.o: $(SRC_DIR)/cmfw_bt.cpp
	$(CC) -o $@ -c $< -I$(INC) -luv -lbluetooth

test: $(SRC_DIR)/test.cpp $(OBJ_DIR)/cmfw_bt.o $(OBJ) 
	$(CC) -o $(BIN_DIR)/$@ $^ -I$(INC) $(LIB)

clean :
	rm -f $(OBJ_DIR)/* $(BIN_DIR)/test

