XML = -I/usr/include/libxml2

all: clean navigation.o

navigation.o: ../../src/navigation/navigation.cpp
	$(CXX) -Wall $(XML) $^ -g -c -o navigation.o

clean:
	rm -f *.o
