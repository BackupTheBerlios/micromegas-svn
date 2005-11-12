XML = -I/usr/include/libxml2

all: clean node.o setofnodes.o ruletree.o ruletreeTest.o

%.o: %.cpp
	$(CXX) -Wall $(XML) -g -c $<

node.o: ../../src/ruletree/node.cpp
	$(CXX) -Wall $(XML) $^ -g -c -o node.o

setofnodes.o: ../../src/ruletree/setofnodes.cpp
	$(CXX) -Wall $(XML) $^ -g -c -o setofnodes.o

ruletree.o: ../../src/ruletree/ruletree.cpp
	$(CXX) -Wall $(XML) $^ -g -c -o ruletree.o

clean:
	rm -f *.o
