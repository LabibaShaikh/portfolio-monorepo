.default: all

PROGRAMS=hospital

all: $(PROGRAMS)

clean:
	rm -rf $(PROGRAMS) *.o *.dSYM

hospital: Hospital.o Patient.o PatientRegister.o WaitingList.o HospitalUtils.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $<
