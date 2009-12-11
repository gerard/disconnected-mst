#ifndef _MFSET_
#define _MFSET_

using namespace std;

class mfSet {
  int *mfs;                         // Vector per a guardar el mfset principal
  int *mfs2;						// Vector per a guardar el mfset de comp.
  int *mfsAristas;					// Nombre de arestas de les components
  int *mfsNodes;					// Nombre de nodes de les components
  float *mfsPes;					// Pes total de la component
  int *mfsPC;						// Vector para Path Compress
  int n;                            // Nombre de elements del mfSet (talla)
  int nSubconjuntos;          		// Nombre de subconjunts (representants)
  int cota;
 public:
  mfSet(int talla);                                  		// Constructor
  ~mfSet();                                           		// Destructor
  int find(int x);                					// Representant de x
  int find2(int x);
  void merge(int x, int y, float pes);
  bool merge2(int x, int y);
  int Subconjuntos();        	 					// Torna nSubconjuntos
  int nArestes(int i);
  int nNodes(int i);
  void obteRepresen(int *vRep, int *vRepInv, int *nNod, int *nAr);
  int obteCota();
};
#endif
