#include <cstdlib>
#include "GrafClass.h"

#include "Hash.h"

/*
Per definir el nombre de arestes, anem a basarnos en la informació que tenim,
es a dir, la memoria disponible en el servidor on s'executen els programes.
128 * 1024 ^ 2 = ARIST * 16 (bytes de l'estructura)

Si bé els nodes ocupen memoria, per al pitjor cas, en que nodes = sqrt(arestes)
el seu pes es despreciable
*/
#define ARIST 8388608

using namespace std;

hashTable *T;

/*
 * La classe Graf disposa de 4 Estructures: Una taula Hash, un vector
 * de punters a arestes, un MFSet especial, i un minHeap
 */
grafo::grafo() { //Creador del Graf
  nArestes=0;
  nNodes=0;
  lasAristas=0;
  mfs=0;
  heaps=0;
  nRep=0;
}
  
grafo::~grafo() {}

void grafo::leer() {
  const int TALLA=256;
  const int CUBETAS=4194304;
  // Aquest parámetre es un compromís entre la velocitat i l'ús de memoria
  // Primer reservem DISPER punter a aresta i si ens fan falta més els
  // crearem
  // 500000 desaprofita un máxim de:
  // 16 * 500000 / 1024^2 = 7Mb de memoria
  const int DISPER=500000;
  
  float w;
  char node1[TALLA], node2[TALLA], cadena[TALLA];

  T = new hashTable(CUBETAS);

  lasAristas = new arista*[ARIST];
  arista **tmp = new arista*[ARIST/DISPER];
  int stat=0;
  int i=0;
  char c;

  int n1, n2;
  // La lectura la farem al menor nivell possible, per a optimitzarla
  while((c=getchar())!=EOF) {
	switch(stat) {
	  case 0:					// Lectura del primer node
	  if(c!='|') {
	    if(i==0 && nArestes%DISPER==0) 
		  tmp[nArestes/DISPER]=new arista[DISPER];
	    cadena[i]=c;
		i++;
	  } else {
	    stat=1;
		cadena[i]='\0';
		i=0;
		n1=T->keyToIndex(cadena);
	  }
	  break;
	  case 1:					// Lectura del segon node
	  if(c!='|') {
	    cadena[i]=c;
	    i++;
	  } else {
	    stat=2;
		cadena[i]='\0';
		i=0;
		n2=T->keyToIndex(cadena);
	  }
	  break;
      case 2:					// Lectura del pes
	  if(c!='\n') {
	    cadena[i]=c;
	    i++;
	  } else {
		stat=0;
		cadena[i]='\0';
		i=0;
		w=(float)strtod(cadena, NULL);
		tmp[nArestes/DISPER][nArestes%DISPER].inserir(n1, n2, w);
		lasAristas[nArestes]= &tmp[nArestes/DISPER][nArestes%DISPER];
		nArestes++;
		}
	  break;
	}
  }
  nNodes=T->nElem();
}

/*
Este métode calcula els representants del graf, aixi com crea el conjunt de
heaps que s'usaran per a Kruskal, entre altres dades, com la primera component
que estudiarem
*/
void grafo::representantes() {
  int *nAr, *tmp, *vRepInv;
 
  mfs = new mfSet(nNodes);
  
  // Hi ha que fer un merge de tots els nodes, per trobar els representants
  // També li passem el pes, per a que calcule la component amb menor pes
  // total, que será la primera que calcularem i ens proporicionará una cota
  // rápidament
  for(int i=0; i<nArestes; i++) 
    mfs->merge(lasAristas[i]->nodoU(), lasAristas[i]->nodoV(), lasAristas[i]->peso());
  nRep=mfs->Subconjuntos();

  // Tindrem n representants i per tant, usarem n heaps;
  arista ***arestesORD=new arista**[nRep];		// Arestes a posar en el Heap
  heaps=new minHeap*[nRep]; // Vector de Heaps
  vRep=new int[nRep];		// Representants de les components
  vRepInv=new int[nNodes];	// Funcio inversa
  nNod=new int[nRep];		// Nombre de nodes de les Components
  nAr=new int[nRep];		// Nombre de arestes de les Components
  tmp=new int[nRep];		// Variable temporal
  
  mfs->obteRepresen(vRep, vRepInv, nNod, nAr);

  // Aquí reservem la memoria necessaria per als heaps, amb el nombre
  // d'arestes que tindrà cada heap. Tambe inicialitzem tmp[]
  for(int i=0; i<nRep; i++) {
    tmp[i]=0;
    arestesORD[i]=new arista*[nAr[i]];
  }
  
  // Aquí ja recorrem lesArestes i les coloquem en els heaps
  int rep, j;
  for(int i=0; i<nArestes; i++) {
    // Extraguem el representant de l'aresta que analitzem
    rep = mfs->find(lasAristas[i]->nodoU());

	// L'emmagatzemem on calga, necessitem l'index de vRep
	arestesORD[vRepInv[rep]][tmp[vRepInv[rep]]]=lasAristas[i];
	tmp[vRepInv[rep]]++;
  }  
  
  // Ara només cal crear tots els heaps
  for(int i=0; i<nRep; i++) {
    heaps[i] = new minHeap(arestesORD[i], nAr[i]);
	heaps[i]->buildMinHeap();
  }
}

/*
 * En l'algorisme, aplicarem primer Kruskal sobre la component que te un
 * pes total inferior a la resta. Amb açó pretenem que el primer pes de
 * tall siga suficientment bó com per a tallar quan abans millor
 */
void grafo::KruskalM() {
  
  // Aresta d'estudi
  static arista *AMST;

  // Variables per resultats parcials i comptadors
  static int arestesMST=0;
  static float pesMST;
 
  // Establim una cota per a reduir les iteracions
  int cota=mfs->obteCota();
  while(arestesMST < nNod[cota] - 1) {
    AMST=heaps[cota]->extractMinHeap();
	if(mfs->merge2(AMST->nodoU(), AMST->nodoV())) {
	  min_pes=min_pes+AMST->peso();
	  arestesMST++;
	}
  }
  int min_i=cota;
  
  // Inici del bucle principal, s'analitzen tots els heaps
  for(int i=0; i<nRep ; i++) {
    if(i==cota) continue; // Esta component ja està estudiada
    arestesMST = 0;
	pesMST = 0;
  
    // Si excedim la cota superior abortem
    while(arestesMST < nNod[i] - 1 && pesMST<min_pes) {
	  AMST=heaps[i]->extractMinHeap();
	  // Si l'aresta forma cicle, passem d'ella
	  if( mfs->merge2(AMST->nodoU(), AMST->nodoV()) ) {
	    pesMST=pesMST+AMST->peso();
	    arestesMST++;
	  }
    }
  
    // Retorn del pes i actualització de nArestes
    if(pesMST<min_pes) {
	  min_i=i;
	  min_pes=pesMST;
    }
  }
  // Encara que gastem la variable i per facilitar la iteració, el
  // representant de la component estudiada es vRep[i]
  nArestes=mfs->nArestes(vRep[min_i]);
  nNodes=mfs->nNodes(vRep[min_i]);
}

/*
 * Aquestes funcions tornen els valors que ens demana el problema (estan
 * emmagatzemats en la classe)
 */
 
int grafo::numAristasSubG() {
  return nArestes;
}

int grafo::numNodesSubG() {
  return nNodes;
}

float grafo::pesSubG() {
  return min_pes;
}
