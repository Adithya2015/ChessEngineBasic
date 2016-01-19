#ifndef HELPER_FUNCS_H
#define HELPER_FUNCS_H
#include "definitions.h"
#include "sstream"
#include "enumerations.h"

int getrank(int); /// 63 format
int getfile(int); /// 63 format
int colors(const vint&,int);
std::string tostring(int x);
std::string toalgebsquare(int x);
bool incheck(int,movetype, vint&);
bool incheck(int, vint&);

#endif // HELPER_FUNCS_H
