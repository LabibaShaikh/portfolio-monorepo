# Default target
.PHONY: all clean

# Top-level target
all: mmcopier src/mscopier

# Clean target
clean:
	rm -rf mmcopier src/mscopier *.o *.dSYM

# Main executable target for mmcopier
mmcopier: $(wildcard src/mmcopier.cpp) $(wildcard src/*.h)
	g++ -Wall -Werror -std=c++14 -g -O -o mmcopier src/mmcopier.cpp
	chmod +x mmcopier  # Set executable permission

# Main executable target for mscopier (inside src directory)
src/mscopier: $(wildcard src/mscopier.cpp) $(wildcard src/*.h)
	g++ -Wall -Werror -std=c++14 -g -O -o src/mscopier src/mscopier.cpp -lpthread
	chmod +x src/mscopier  # Set executable permission
