#include <iostream>
#include "BinHeap.h"

using namespace std;

BinaryHeap::BinaryHeap(const double* priorities, int numItems)
{
   this->numItems = numItems;
   heap = new int[numItems];
   this->priorities = new double[numItems];
   pos = new int[numItems];

   for(int i = 0; i < numItems; i++)
   {
      heap[i] = i;
      pos[i] = i;
      this->priorities[i] = priorities[i];
   }

   for(int i = numItems/2; i >= 0; i--)
   {
      heapify(i);
   }
}

BinaryHeap::~BinaryHeap()
{
   delete[] heap;
   delete[] priorities;
   delete[] pos;
}

int BinaryHeap::getMin() const
{
   return heap[0];
}

void BinaryHeap::swap(int pos1, int pos2)
{
   int tmp = heap[pos1];
   heap[pos1] = heap[pos2];
   heap[pos2] = tmp;
   
   pos[heap[pos1]] = pos1;
   pos[heap[pos2]] = pos2;
}

void BinaryHeap::heapify(int pos)
{
   int left = 2*pos + 1;
   int right = 2*pos + 2;
   int smaller;
   if(right < numItems and priorities[heap[pos]] > priorities[heap[right]])
   {
      smaller = right;
   }
   else
   {
      smaller = pos;
   }

   if(left < numItems and priorities[heap[smaller]] > priorities[heap[left]])
   {
      smaller = left;
   }

   if(smaller != pos)
   {
      swap(pos, smaller);      
      heapify(smaller);
   }
}

void BinaryHeap::popMin()
{
   pos[heap[0]] = -1;
       
   heap[0] = heap[numItems - 1];
   pos[heap[0]] = 0;
       
   numItems--;

   heapify(0);
}

bool BinaryHeap::contains(int item) const
{
   return pos[item] >= 0;
}

double BinaryHeap::getPriority(int item) const
{
   return priorities[item];
}

void BinaryHeap::decreasePriority(int item, double newPriority)
{
   if(newPriority < priorities[item])
   {
      priorities[item] = newPriority;

      int i = pos[item];
      int parent = (i - 1)/2;
      while(i > 0 && priorities[heap[parent]] > priorities[heap[i]])
      {
	 swap(i, parent);
	 
	 i = parent;
	 parent = (i - 1)/2;
      }   
   }
}

int BinaryHeap::getSize() const
{
   return numItems;
}

int BinaryHeap::getItem(int pos) const
{
   return heap[pos];
}

int BinaryHeap::getPos(int item) const
{
   return pos[item];
}
