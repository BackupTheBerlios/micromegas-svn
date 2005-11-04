FILES = order/setofint.cpp order/element.cpp order/table.cpp order/setofelements.cpp order/order.cpp ruletree/node.cpp ruletree/ruletree.cpp ruletree/setofnodes.cpp navigation/navigation.cpp main.cpp

XML = -I/usr/include/libxml2

all: $(FILES)
	g++ -Wall -g -O2 $(XML) -lxml2 $(FILES) -o arf

swig:
	swig -python -c++ calcul.i
	g++ -o _calcul.so -shared calcul_wrap.cxx -I/usr/include/python2.3 -I/usr/include/libxml2 -I. -L. -Lorder -Lruletree -Lnavigation -Iorder -Iruletree -Inavigation
	
clean:
	rm -f calcul.py _calcul.so calcul_wrap.cxx