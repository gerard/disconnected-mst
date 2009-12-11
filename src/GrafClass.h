#include <stdio.h>

#include "HeapClass.h"
#include "ArestaClass.h"
#include "mfSetClass.h"

class grafo {
  int nArestes, nNodes, nRep;
  float min_pes;
  
  // Este vector, conte els representants del graf
  int *vRep, *nNod;
  
  arista **lasAristas;  // Vector d'emmagatzematge
  mfSet *mfs;			// Estructura per manejar els conjunts
  minHeap **heaps;     	// Heaps per a cada component
 
public:
  grafo();
  ~grafo();
  void leer();
  // Torna els representants amb el seu nombre de Nodes
  void representantes();
  // Kruskal per a tots els representants
  void KruskalM();
  int numAristasSubG(); // Torna el número d'arestes del menor subgraf
  int numNodesSubG();
  float pesSubG();
};

