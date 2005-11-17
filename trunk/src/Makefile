# make : compiles both the server and the standalone exe
# make exe : compiles only the standalone exe
# make server : compiles the "server"


# Compiler configuration
CXX=g++
CXXFLAGS=-O2 -Wall -g

# Includes an libraries
INC_XML=-I/usr/include/libxml2
INC_PYTH=-I/usr/include/python2.3
LIB_XML=-lxml2

# Common source files and object file
SRC=$(wildcard ruletree/*.cpp order/*.cpp navigation/*.cpp)
OBJ=$(SRC:.cpp=.o)

# Output files
EXE_NAME=arf
LIB_NAME=_calcul.so



# Default : making the server library and the standalone exe
all: server exe


# Making the standalone exe
exe: $(OBJ) main.o
	$(CXX) $(CXXFLAGS) -o $(EXE_NAME) $^ $(INC_XML) $(LIB_XML)


# Making the server library (and related files)
server: $(OBJ) calcul_wrap.o
	$(CXX) $(CXXFLAGS) -o $(LIB_NAME) -shared $^ $(INC_XML) $(LIB_XML)


# Python <-> C++ wrapper
calcul_wrap.o: calcul_wrap.cxx
	$(CXX) $(CXXFALGS) -c -o $@ $< $(INC_PYTH) $(INC_XML)
calcul_wrap.cxx: calcul.i
	swig -python -c++ $<


# Building object files from source code
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INC_XML)




# Cleaning all temporary files but not the final exe or lib
clean:
	rm -rf $(OBJ) calcul_wrap.* main.o

# Cleaning all including final files
mrproper: clean
	rm -f $(EXE_NAME) $(LIB_NAME) calcul.py calcul.pyc
