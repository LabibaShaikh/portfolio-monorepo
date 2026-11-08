# Makefile for Memory Allocation Simulation

CXX = g++
CXXFLAGS = -Wall -Werror -lpthread

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include

# Object files for both
OBJ_FILES_COMMON = $(BUILD_DIR)/memory_manager.o
OBJ_FILES_FIRST_FIT = $(BUILD_DIR)/first_fit.o
OBJ_FILES_BEST_FIT = $(BUILD_DIR)/best_fit.o

# Executables
EXEC_FIRSTFIT = $(BIN_DIR)/firstfit
EXEC_BESTFIT = $(BIN_DIR)/bestfit

# Targets
all: setup $(EXEC_FIRSTFIT) $(EXEC_BESTFIT)

setup:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Build firstfit executable
$(EXEC_FIRSTFIT): $(OBJ_FILES_COMMON) $(OBJ_FILES_FIRST_FIT) $(BUILD_DIR)/main_firstfit.o
	$(CXX) $(OBJ_FILES_COMMON) $(OBJ_FILES_FIRST_FIT) $(BUILD_DIR)/main_firstfit.o -o $(EXEC_FIRSTFIT) $(CXXFLAGS)

# Build bestfit executable
$(EXEC_BESTFIT): $(OBJ_FILES_COMMON) $(OBJ_FILES_BEST_FIT) $(BUILD_DIR)/main_bestfit.o
	$(CXX) $(OBJ_FILES_COMMON) $(OBJ_FILES_BEST_FIT) $(BUILD_DIR)/main_bestfit.o -o $(EXEC_BESTFIT) $(CXXFLAGS)

# Compile object files
$(BUILD_DIR)/memory_manager.o: $(SRC_DIR)/memory_manager.cpp $(INCLUDE_DIR)/memory_manager.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/memory_manager.cpp -o $(BUILD_DIR)/memory_manager.o

$(BUILD_DIR)/first_fit.o: $(SRC_DIR)/first_fit.cpp $(INCLUDE_DIR)/memory_manager.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/first_fit.cpp -o $(BUILD_DIR)/first_fit.o

$(BUILD_DIR)/best_fit.o: $(SRC_DIR)/best_fit.cpp $(INCLUDE_DIR)/memory_manager.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/best_fit.cpp -o $(BUILD_DIR)/best_fit.o

# Compile the main files
$(BUILD_DIR)/main_firstfit.o: $(SRC_DIR)/main_firstfit.cpp $(INCLUDE_DIR)/memory_manager.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/main_firstfit.cpp -o $(BUILD_DIR)/main_firstfit.o

$(BUILD_DIR)/main_bestfit.o: $(SRC_DIR)/main_bestfit.cpp $(INCLUDE_DIR)/memory_manager.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/main_bestfit.cpp -o $(BUILD_DIR)/main_bestfit.o

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
