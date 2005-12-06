/*
 * API du centre de calcul.
 */

%module calcul

%{
#include "navigation/navigation.hpp"
%}

void initArbo(char* filename);
void specialiser(char* filename, int node, char* outname);
void sauter(char* filename, int node, char* outname);
