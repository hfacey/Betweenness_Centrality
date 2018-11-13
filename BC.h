#ifndef BC_H
#define BC_H

#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

void serialBC(string inFile, string DorBFS, double &runtime);

void parallelBC(string inFile, string DorBFS, int numThreads, double &runtime);

#endif
