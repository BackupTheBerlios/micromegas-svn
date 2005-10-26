/*
 * API du centre de calcul.
 */

%module calcul
 
%{
#include "navigation/navigation.hpp"
%}
 
void initArbo(char * filename);
void specialiser(char * filename);
void sauter(char * filename);