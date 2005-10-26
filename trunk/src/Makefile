all:
	swig -python -c++ calcul.i
	g++ -o _calcul.so -shared calcul_wrap.cxx -I/usr/include/python2.3 -I/usr/include/libxml2 -I. -L. -Lorder -Lruletree -Lnavigation -Iorder -Iruletree -Inavigation
	
clean:
	rm -f calcul.py _calcul.so calcul_wrap.cxx