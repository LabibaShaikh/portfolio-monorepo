.default: all

PROGRAMS=date

all: $(PROGRAMS)

clean:
	rm -rf $(PROGRAMS) *.o *.dSYM

date: main.o Date.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
