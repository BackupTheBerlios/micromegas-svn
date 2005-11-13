#include <iostream>
#include <unistd.h>
#include "navigation/navigation.hpp"

int main(int argc, char **argv) {
	int option_char,node;
	bool init=false,spe=false,jmp=false,nd=false,out=false;
	string input,output;
	
	while ((option_char = getopt(argc, argv, "i:s:j:n:o:")) != EOF) {
		switch(option_char) {
			case 'i' :
				if (spe || jmp) {
					cout << "You can only have one of -s -j or -i" << endl;
					return 1;
				}
				init = true;
				input = optarg;
				break;
			case 's' :
				if (init || jmp) {
					cout << "You can only have one of -s -j or -i" << endl;
					return 1;
				}
				spe = true;
				input = optarg;
				break;
			case 'j' :
				if (init || spe) {
					cout << "You can only have one of -s -j or -i" << endl;
					return 1;
				}
				jmp = true;
				input = optarg;
				break;
			case 'n' :
				node = atoi(optarg);
				nd = true;
				break;
			case 'o' :
				output = optarg;
				out = true;
				break;
		}
	}
	if (init)
		initArbo(input);
	else if (spe && nd && out)
		specialiser(input,node,output);
}
