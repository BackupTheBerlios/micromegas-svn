MODULES = order/setofint.o \
          order/setofintTest.o \
	  order/table.o \
	  order/tableTest.o \
	  order/element.o \
	  order/elementTest.o \
	  order/setofelements.o \
	  order/setofelementsTest.o \
	  order/order.o \
	  order/orderTest.o \
	  ruletree/node.o \
	  ruletree/setofnodes.o \
	  ruletree/ruletree.o \
	  navigation/navigation.o

#	order/element.o \
#	order/table.o \
#	order/setOfElements.o \
#	order/orderTest.o \
#	order/order.o \
#order/setOfElementsTest.o
#order/elementTest.o
#order/tableTest.o
#order/itemsetTest.o

CXX=g++
FLAGS = -Wall -lcppunit -ldl -g -O2 -lxml2

all : clean mods test_exe

mods:
	make -C order CXX=$(CXX)
	make -C ruletree CXX=$(CXX)
	make -C navigation CXX=$(CXX)

clean:
	make -C order clean
	make -C ruletree clean
	make -C navigation clean
	rm -f test_exe

test_exe: $(MODULES)
	$(CXX) $(FLAGS) $^ main.cpp -o test_exe
