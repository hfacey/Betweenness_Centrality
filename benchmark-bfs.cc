#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "BC.h"

//
//
//Program to benchmark the Betweenness Centrality of a graph with unweighted
//edges. Modified Breadth Firth Search (BFS) algorithm is used to find 
//all shortest paths.
//
//
using namespace std;

int main (int argc, char **argv)
{
  ofstream fout(argv[1]);

  int sizes[] = {200,800,1600,3200,6400,80000,200000};

  fout<<"Benchmark for Betweenness Centrality with unweighted edges"<<endl;
  for(int i=0;i<7;i++)
    {
      double serialTimeSum = 0;
      string graphFile = to_string(sizes[i])+".txt";
      for(int r=i;r<7;r++)
	{
	  double serialTime = -1;
	  serialBC(graphFile,"bfs",serialTime);
	  serialTimeSum+=serialTime;
	}
      fout<<"Graph size: "<<sizes[i]<<"\tSerial time: "<<(serialTimeSum/(7-i))<<endl;
      fout<<"NumThreads\tSpeedup"<<endl;
      for(int j = 4;j<29;j +=4)
	{
	  double runtimeSum = 0;
	  for(int r=i;r<7;r++)
	    {
	      double runtime = -1;
	      parallelBC(graphFile,"bfs",j,runtime);
	      runtimeSum+=runtime;
	    }
	  fout<<j<<"\t"<<((serialTimeSum/(7-i))/(runtimeSum/(7-i)))<<endl;
	}
      cout<<"completed size: "<<sizes[i]<<endl;
    }

}  
