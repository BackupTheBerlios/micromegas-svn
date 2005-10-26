XML = -I/usr/include/libxml2

all: clean setofint.o setofintTest.o table.o tableTest.o element.o elementTest.o setofelements.o setofelementsTest.o order.o orderTest.o

%.o: %.cpp
	g++ -Wall $(XML) -g -c $<

setofint.o: ../../src/order/setofint.cpp
	g++ -Wall $^ -g -c -o setofint.o

table.o: ../../src/order/table.cpp
	g++ -Wall $(XML) $^ -g -c -o table.o
	
element.o: ../../src/order/element.cpp
	g++ -Wall $^ -g -c -o element.o

setofelements.o: ../../src/order/setofelements.cpp
	g++ -Wall $(XML) $^ -g -c -o setofelements.o

order.o: ../../src/order/order.cpp
	g++ -Wall $(XML) $^ -g -c -o order.o

clean:
	rm -f *.o