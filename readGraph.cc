#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
using namespace std;

int readGraph(ifstream& fin, int**& edgeList, double*& weights,
	      int& numEdges, string*& vLabels, string*& eLabels)
{
  int vert;
  fin >> vert;
  fin >> numEdges;
  weights = new double[numEdges];
  edgeList = new int*[numEdges];
  eLabels = new string[numEdges];
  vLabels = new string[vert];

  for(int i = 0; i<vert;i++)
    {fin >> vLabels[i];}

  for(int i = 0; i<numEdges;i++)
    {edgeList[i] = new int[2];}

  for(int i = 0; i<numEdges;i++)
    {
      fin >> edgeList[i][0];
      fin >> edgeList[i][1];
      fin >> weights[i];
      fin >> eLabels[i];
    }

  return vert;  
}

int readGraph(ifstream& fin, int**& adj, double**& weights,
	      int*& lengths, string*& vLabels, string**& eLabels)
{
  int vert,edge, sourceV;//, dest, prevS,count;
  //double weigh;
  fin >> vert;
  fin >> edge;
  string labelStr;
  adj = new int*[vert];
  weights = new double*[vert];
  eLabels = new string*[vert];
  vLabels = new string[vert];
  lengths = new int[vert];
  for(int i = 0; i<vert;i++)
    {
      fin >> labelStr;
      vLabels[i] = labelStr;
    }
  
  fin >> sourceV;

for(int i = 0; i < vert; i++)
   {
      vector<int> tmpAdj;
      vector<double> tmpWeights;
      vector<string> tmpLabels;
   
      lengths[i] = 0;
      while(!fin.eof() && sourceV == i)
      {
	 int destV;
	 fin >> destV;
	 tmpAdj.push_back(destV);
	 double w;
	 fin >> w;
	 tmpWeights.push_back(w);
	 string label;
	 fin >> label;
	 tmpLabels.push_back(label);
	 lengths[i]++;
	 fin >> sourceV;
      }

      adj[i] = new int[lengths[i]];
      weights[i] = new double[lengths[i]];
      eLabels[i] = new string[lengths[i]];
      for(int j = 0; j < lengths[i]; j++)
      {
	 adj[i][j] = tmpAdj[j];
	 weights[i][j] = tmpWeights[j];
	 eLabels[i][j] = tmpLabels[j];
      }
   }
  return vert;
}


int readGraph(ifstream & fin, double**& matrix,
	      string*& vLabels, string**& eLabels)
{
  int vert,edge,source,dest;
  fin >> vert;
  fin >> edge;
  string labelStr;
  double weight;
  matrix = new double*[vert];
  eLabels = new string*[edge];
  vLabels = new string[vert];
  for(int i = 0; i<vert;i++)
    {
      fin >> labelStr;
      vLabels[i] = labelStr;
      
      string* tempS = new string[vert];
      double* tempD = new double[vert];
      for(int j=0;j<vert;j++)
	{
	  if(i==j)
	    {tempD[j] = 0;}
	  else
	    {tempD[j] = numeric_limits<double>::infinity();}
	}
      matrix[i] = tempD;
      eLabels[i] = tempS;
    }

  
  for(int i = 0; i<edge;i++)
    {
      fin >> source;
      fin >> dest;
      fin >> weight;
      fin >> labelStr;
      matrix[source][dest] = weight;
      eLabels[source][dest] = labelStr;
    }
  return vert;
}

