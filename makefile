SRC_DIR := src
HEADER_DIR := headers

all: sp_lab

sp_lab: $(SRC_DIR)/main.o $(SRC_DIR)/elements.o $(SRC_DIR)/strategy.o $(SRC_DIR)/visitor.o
	g++ -o $@ $^

$(SRC_DIR)/main.o: $(SRC_DIR)/main.cpp $(HEADER_DIR)/elements.hpp $(HEADER_DIR)/strategy.hpp $(HEADER_DIR)/visitor.hpp
	g++ -c $< -o $@

$(SRC_DIR)/elements.o: $(SRC_DIR)/elements.cpp $(HEADER_DIR)/elements.hpp
	g++ -c $< -o $@

$(SRC_DIR)/strategy.o: $(SRC_DIR)/strategy.cpp $(HEADER_DIR)/strategy.hpp
	g++ -c $< -o $@

$(SRC_DIR)/visitor.o: $(SRC_DIR)/visitor.cpp $(HEADER_DIR)/visitor.hpp
	g++ -c $< -o $@
