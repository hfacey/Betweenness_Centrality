#ifndef BINARYHEAP_H
#define BINARYHEAP_H

class BinaryHeap
{
  protected:
   int* heap;
   double* priorities;
   int* pos;
   int numItems;

   void heapify(int pos);
   void swap(int pos1, int pos2);

  public:
   BinaryHeap(const double* priorities, int numItems);
   virtual ~BinaryHeap();

   virtual int getMin() const;
   virtual void popMin();

   virtual bool contains(int item) const;

   virtual double getPriority(int item) const;
   virtual void decreasePriority(int item, double newPriority);

   virtual int getSize() const;
   virtual int getItem(int pos) const;
   virtual int getPos(int item) const;
};

#endif
