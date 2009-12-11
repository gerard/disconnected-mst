#ifndef _HEAP_
#define _HEAP_
#include "ArestaClass.h"

class minHeap {
  int maxNelem;
  int nElem;
  arista **elHeap;
  void heapify(int i);
 public:
  minHeap(arista **h, int numElem);
  ~minHeap();
  int numElem();
  void buildMinHeap();
  arista *extractMinHeap();
};
#endif
