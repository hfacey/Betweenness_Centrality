#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <omp.h>
#include "BC.h"
#include "shortestPaths.h"
#include "readGraph.h"
#include "BinHeap.h"

using namespace std;

void serialBC(string inFile, string DorBFS, double& runtime)
{
  ifstream fin(inFile);
  double** weights;
  int** adj;
  int* lengths;
  string* vLabels;
  string** eLabels;

  int vert = readGraph(fin,adj,weights,lengths,vLabels,eLabels);
  fin.close();

  int* bc = new int[vert];
  for(int i = 0; i<vert;i++)
    { bc[i]=0; }
  int maxBC = 0;
  int maxBCidx = -1;

  auto t2 = chrono::system_clock::now();
  if(DorBFS=="d")
    for(int i = 0; i<vert;i++)
      { 
	double* dist;
	int* prev;
	dijkstra(adj,weights,lengths, vert, i, dist, prev);
	accumulateBetweenness(vert,i,prev,bc);
      }
  else if(DorBFS=="bfs")
    for(int i = 0; i<vert;i++)
      { 
	int* prev;
	BFS(adj,lengths, vert, i, prev);
	accumulateBetweenness(vert,i,prev,bc);
      }

  for(int i = 0; i<vert;i++)
    {
      if(bc[i]>maxBC)
	{
	  maxBC = bc[i];
	  maxBCidx = i;
	}
    }
  auto t1 = chrono::system_clock::now();
  auto dur = t1-t2;
  auto durMS = chrono::duration_cast<chrono::microseconds>(dur);
  runtime = durMS.count()/1000000.0;

  //cout<<"Time taken to perfom Betweenness Centrality: "<<elapsed<<" seconds"<<endl;
  //cout<<vLabels[maxBCidx]<<" was the vertex with the highest BC. It was a part of "<<((double)bc[maxBCidx]*100)/(vert*(vert-1))<<"% of the graph's shortest paths."<<endl;
  
}


struct MaxComp
{
  int val;
  int idx;
  MaxComp()
  {
    val = 0;
    idx = -1;
  }
};

MaxComp& myComp(MaxComp &x, MaxComp &y)
{
  return x.val > y.val ? x : y;
}


#pragma omp declare reduction(maximum : MaxComp : omp_out = myComp(omp_out, omp_in)) initializer (omp_priv = MaxComp())


void parallelBC(string inFile, string DorBFS, int numThreads, double &runtime)
{
  ifstream fin(inFile);
  double** weights;
  int** adj;
  int* lengths;
  string* vLabels;
  string** eLabels;
  
  int vert = readGraph(fin,adj,weights,lengths,vLabels,eLabels);
  fin.close();
  
  //bool valid = true;

  omp_set_num_threads(numThreads);
  
  int* bc = new int[vert];
  for(int i = 0; i<vert;i++)
    { bc[i]=0; }
  
  MaxComp maxBC;
  maxBC.val = 0;
  maxBC.idx = -1;
  
  omp_lock_t myLocks[vert];
  for(int i = 0; i<vert;i++)
    {
      omp_init_lock(&myLocks[i]);
    }
  
  double ostart= omp_get_wtime();
#pragma omp parallel
  {
    if(DorBFS=="d")
#pragma omp for
      for(int s = 0; s<vert;s++)
	{ 
	  double* dist;
	  int* prev;
	  dijkstra(adj,weights,lengths, vert, s, dist, prev);
	  accumulateBetweenness(vert,s,prev,bc, myLocks);
	}
    else if(DorBFS=="bfs")
#pragma omp for
      for(int s = 0; s<vert;s++)
	{ 
	  int* prev;
	  BFS(adj,lengths, vert, s, prev);
	  accumulateBetweenness(vert,s,prev,bc, myLocks);
	}
    else
      {
	cout<<"Error: please pass as a parameter 'd' to perform Dijkstra's (weighted) or 'bfs' to perform BFS(unweighted)"<<endl; 
	//valid = false;
      }
    //if(valid)
#pragma omp for reduction(maximum:maxBC)
    for(int i=0;i<vert;i++)
      {
	if(bc[i]>maxBC.val)
	  {
	    maxBC.val=bc[i];
	    maxBC.idx = i;
	  }
      }
  }
  double oend =omp_get_wtime();
  
  //if(valid)
  runtime = (oend-ostart);
  
  //cout<<"Time taken to perfom Betweenness Centrality: " << (oend-ostart) << " seconds"<<endl;
  //cout<<vLabels[maxBC.idx]<<" was the vertex with the highest BC. It was a part of "<<((double)bc[maxBC.idx]*100)/(vert*(vert-1))<<"% of the graph's shortest paths."<<endl;  
}
