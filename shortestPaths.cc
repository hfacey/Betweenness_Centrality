#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <omp.h>
#include "shortestPaths.h"
#include "BinHeap.h"

using namespace std;

void dijkstra(const int* const * adj, const double* const * weights, const int* lengths, int numVertices, int source, double*& dist, int*& prev)
{
  dist = new double[numVertices];
  prev = new int[numVertices];

  for(int i=0;i<numVertices;i++)
    {
      dist[i]=numeric_limits<double>::infinity();
      prev[i]=-1;
    }

  BinaryHeap heap(dist, numVertices);
  heap.decreasePriority(source,0);
  int n = heap.getMin();
  heap.popMin();

  dist[n] = 0;
  for(int i = 1;i<numVertices;i++)
    {
      for(int j=0;j<lengths[n];j++)
	{
	  if(dist[n]+weights[n][j]<heap.getPriority(adj[n][j]))
	    {
	      heap.decreasePriority(adj[n][j],dist[n]+weights[n][j]);
	      prev[adj[n][j]] = n;
	    }
	}
      n = heap.getMin();
      dist[n] = heap.getPriority(n);
      heap.popMin();
    }
}

void BFS(const int* const * adj, const int* len, int numVertices, int source, int*& prev)
{
  int d = 0;
  int* depth = new int[numVertices];
  prev = new int[numVertices];
  for(int i = 0; i<numVertices;i++)
    { depth[i]=-1; prev[i]=-1; }

  vector<int> B;
  B.push_back(source);
  
  depth[source] = 0;
  while(B.size()>0)
    {
      vector<int> F;
      d++;
      for(unsigned i = 0; i<B.size();i++)
	{
	  for(int j=0; j<len[B[i]];j++)
	    {
	      if(depth[adj[B[i]][j]]==-1) //not travelled to as yet
		{
		  depth[adj[B[i]][j]] = d;
		  F.push_back(adj[B[i]][j]);
		  prev[adj[B[i]][j]] = B[i];
		}
	    }
	}
      B = F;
    }
}


void accumulateBetweenness(int numVertices, int source, const int* prev, int*& bc)
{
  for(int i = 0; i<numVertices;i++)
    {
      int step = i;
      //ned to ensure there's really a path to accumulate
      int fail = false, found=false;
      int n = 0, v=i;
      while(!found && !fail)
	{
	  if(v==source)
	    { found = true; }
	  else if(n>=numVertices||v==-1)
	    { fail = true; }
	  else
	    { 
	      v = prev[v]; n++;
	      //if(source==62)
	      //{cout<<"now at v: "<<v<<endl;}
	    }
	}
      if(fail)
	{//cout<<"source: "<<source<<" dest: "<<i<<endl;

	  continue;}


      while(step != source)
	{
	  bc[step]++;
	  step = prev[step];
	}
    }
}

//possible methods: 
//1. lock BC array when adding to prevent race
//2. have separate BC arrays and sum them in a reduction after
//3. one BC array and do sum reduction on it. probably still with locks
//4. recognize that the few race conditions that will actualize, 
//will not affect the end result. Prove 
//Edit: Reductions on arrays take a bit of work. so #1 or 4.
//Further edit: locks are about data. I could coomprimise between 1 and 4:
//creata an array of locks for each data element. Most times, 
//multiple processes won't be trying to write to the same element, so why
//restrict everyone...

void accumulateBetweenness(int numVertices, int source, const int* prev, int*& bc, omp_lock_t* myLocks)
{
  for(int i = 0; i<numVertices;i++)
    {
      int step = i;
      //ned to ensure there's really a path to accumulate
      int fail = false, found=false;
      int n = 0, v=i;
      while(!found && !fail)
	{
	  if(v==source)
	    { found = true; }
	  else if(n>=numVertices||v==-1)
	    { fail = true; }
	  else
	    { v = prev[v]; n++;}
	}
      if(fail)
	{//cout<<"source: "<<source<<" dest: "<<i<<endl;

	  continue;}

      while(step != source)
	{
	  omp_set_lock(&myLocks[step]);
	  bc[step]++;
	  omp_unset_lock(&myLocks[step]);
	  step = prev[step];
	}
    }
}



