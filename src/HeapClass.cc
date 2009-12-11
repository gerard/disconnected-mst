#include "HeapClass.h"

minHeap::minHeap(arista **h, int numElem) {
  elHeap = h-1;   		// el puntero elHeap apuntarà a una posició invalida
                                    // no obstant, no l'indexarem en cap cas
  maxNelem = nElem = numElem;
}

minHeap::~minHeap() {}

inline
void minHeap::heapify(int i) {  			// Versió iterativa de heapify
  int l, r, menor;

  while (i <= nElem/2) {
    l = 2*i;
    r = l+1;
    menor = l;
    
	if ((r <= nElem) && (*elHeap[r] < *elHeap[menor])) menor = r;
    if (*elHeap[menor] < *elHeap[i]) {
      arista *p = elHeap[menor];
      elHeap[menor] = elHeap[i];
      elHeap[i] = p;
      i = menor;
    }
    else return;
  }
}

void minHeap::buildMinHeap() {
  for (int i=nElem/2; i>0; i--)
    heapify(i);
}

arista * minHeap::extractMinHeap() {
  arista * p=elHeap[1];
  elHeap[1] = elHeap[nElem];
  
  nElem--;
  heapify(1);
  return p;
}
