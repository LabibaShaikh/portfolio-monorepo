# Default target
.default: all

# Top-level target
all: bin/ftt

# Clean target
clean:
	rm -rf bin/*.o bin/*.dSYM bin/ftt

# Main executable target
bin/ftt: $(wildcard src/*.cpp) $(wildcard src/*.h)
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^
	chmod +rw $@  # Set permissions (e.g., 755 for read, write, execute by user; read, execute by group and others)

# Generic rule for object files
bin/%.o: src/%.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $< -o $@

# Ensure bin directory exists
$(shell mkdir -p bin)
