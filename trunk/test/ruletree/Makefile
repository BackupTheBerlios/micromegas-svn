XML = -I/usr/include/libxml2

all: clean node.o setofnodes.o ruletree.o

node.o: ../../src/ruletree/node.cpp
	g++ -Wall $(XML) $^ -g -c -o node.o
	
setofnodes.o: ../../src/ruletree/setofnodes.cpp
	g++ -Wall $(XML) $^ -g -c -o setofnodes.o

ruletree.o: ../../src/ruletree/ruletree.cpp
	g++ -Wall $(XML) $^ -g -c -o ruletree.o

clean:
	rm -f *.o