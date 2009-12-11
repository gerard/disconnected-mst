#include <values.h>
#include "mfSetClass.h"

using namespace std;

mfSet::mfSet(int talla) {
  mfs = new int[talla];
  mfs2 = new int[talla];
  mfsAristas = new int[talla];
  mfsNodes = new int[talla];
  mfsPC = new int[talla];
  mfsPes = new float[talla];
  nSubconjuntos=n=talla;
  for(int i=0; i<talla; i++) {
  	mfs2[i]=mfs[i]=-1;
	mfsAristas[i]=0;
	mfsNodes[i]=1;
  }
}

mfSet::~mfSet() {}

int mfSet::find(int x) {                // Torna el representant de x
  int i=0;
  while(mfs[x]>=0) { 
    mfsPC[i]=x;
	i++;
	x=mfs[x];
  }
  for(i--; i>=0; i--) mfs[mfsPC[i]]=x;
  return x;
}

int mfSet::find2(int x) {				// El mateix, tan sols que per a una
  int i=0;								// component, no pel graf general
  while(mfs2[x]>=0) {
    mfsPC[i]=x;
	i++;
	x=mfs2[x];
  }
  for(i--; i>=0; i--) mfs2[mfsPC[i]]=x;
  return x;
}

void mfSet::merge(int x, int y, float pes) { // Enlaza el nodo y al nodo x.
  int i=find(x);
  int j=find(y);

  if(i==j) {
    mfsAristas[j]++;	// En aquest cas, nomes cal sumar una aresta
    return;
  }
  
  nSubconjuntos--;
  // En aquest cas tenim les arestes del dos conjunts més la nova
  if(mfs[i]<mfs[j]) {
    mfsNodes[i]=mfsNodes[j]+mfsNodes[i]; // Se suman el número de nodos
    mfsAristas[i]=mfsAristas[j]+mfsAristas[i]+1;
	mfsPes[i]=mfsPes[j]+mfsPes[i]+pes;
    mfs[j]=i;	           // Ara la rama x, esta penjada a y
    return;
  }
  mfsNodes[j]=mfsNodes[j]+mfsNodes[i]; // Se suman el número de nodos
  mfsAristas[j]=mfsAristas[j]+mfsAristas[i]+1;
  mfsPes[j]=mfsPes[j]+mfsPes[i]+pes;
  mfs[i]=j;
  if(mfs[i]==mfs[j]) mfs[j]--;
}

/*
 * La funció torna "false" en el cas de que estiga formant-se un cicle,
 * en cas contarari, torna true. Es la condicio del if més intern del 
 * algorisme de Kruskal que aplicarem en la classe Graf
 */
bool mfSet::merge2(int x, int y) {
  int i, j;
  i=find2(x);
  j=find2(y);
	
  if(i==j) return false;
  
  if(mfs2[i]<mfs2[j]) {
	mfs2[j]=i;
	return true;
  }
  mfs2[i]=j;
  if(mfs2[i]==mfs2[j]) mfs2[j]--;
  return true;
}

int mfSet::Subconjuntos() {         // Torna el nombre de subconjunts o
  return nSubconjuntos;				// o representants
}

int mfSet::nArestes(int i) {
  return mfsAristas[i];
}

int mfSet::nNodes(int i) {
  return mfsNodes[i];
}

/*
 * Aquest métode, torna el nombre de nodes, arestes de cada component,
 * així com els representants de les mateixes. També proporcionem la funció
 * inversa, per a optimitzar la funció representants de la classe Graf
 */
void mfSet::obteRepresen(int *vRep, int *vRepInv, int *nNod, int *nAr) { 
  int cont=0;
  float min=MAXFLOAT;
  
  for(int i=0; i<n; i++) {
    if(mfs[i]<0) {
	  vRep[cont]=i;
	  vRepInv[i]=cont;
	  nNod[cont]=mfsNodes[i];
	  nAr[cont]=mfsAristas[i];
	  if(mfsPes[i]<min) {
	    min=mfsPes[i];
		cota=cont;
      }
	  cont++;
	}
  }
}

// Torna un dels valors obtesos en el anterior metode
int mfSet::obteCota() {
  return cota;
}
