/*
 * API du centre de calcul.
 */

%module calcul
 
%{
#include "navigation/navigation.hpp"
%}
 
void initArbo(string filename);
void specialiser(string filename);
void sauter(string filename);