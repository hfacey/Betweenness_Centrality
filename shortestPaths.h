#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H
#include <omp.h>

void dijkstra(const int* const * adj, const double* const * weights, const int* lengths, int numVertices, int source, double*& dist, int*& prev);

void BFS(const int* const * adj, const int* len, int numVertices, int source, int*& prev);


void accumulateBetweenness(int numVertices, int source, const int* prev, int*& bc);

void accumulateBetweenness(int numVertices, int source, const int* prev, int*& bc, omp_lock_t* myLocks);

#endif
