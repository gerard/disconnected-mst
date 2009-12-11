#include <cstring>
#include "Hash.h"

using namespace std;

inline
unsigned int hashTable::hashFunction(const char *name) {   
  unsigned int hash0 = 0x12a3fe2d, hash1 = 0x37abe8f9;
  while (*name!='\0') {
    unsigned int hash = hash1 + (hash0 ^ (*name++ * 7152373));

    if (hash & 0x80000000) hash -= 0x7fffffff;
      hash1 = hash0;
      hash0 = hash;
  }
  return (hash0 << 1) & 0x3fffff;
}

hashTable::hashTable (int s) {
  const int NODES=100000; 				// Dada del enunciat
  const int CHARS=2560000;				// Máxim nombre de caràcters

  Table = new hashNode *[s]; // Cada posició d'aquest vector està asociat
        // a una cubeta. Cada cubeta es reprensenta como una llista enllaçada.
  cadenes = new char[CHARS];
  punt = cadenes;
  hNodes = new hashNode[NODES];
  sizeVector = s;
  sizeTable = s;
  numElem = 0;
  for (int i=0; i<sizeTable; i++) Table[i] = 0;
}

hashTable::~hashTable() {}

int hashTable::keyToIndex (char *newKey) {
  unsigned int p = hashFunction(newKey);
  hashNode *aux=Table[p];
  
  while (aux!=0 && strcmp(aux->key, newKey)) aux=aux->next;
  if (aux!=0)  return aux->value;
  // Si trobem la cadena, tornem l'enter associat.
  else {
    // Intentem evitar fer una reserva per cada iteració
	aux = &(hNodes[numElem]);
	aux->key = punt;
    
	// Açó es básicament un strcpy
	int i=0;
	for(; newKey[i]!='\0'; i++) aux->key[i]=newKey[i];
	aux->key[i]='\0';
	punt=punt+i+1;
    
	aux->value = numElem;
    aux->next = Table[p];
    Table[p] = aux;
    numElem++;
    return aux->value;
  }
}

// Nombre de elements de la taula Hash (Nodes en el nostre cas)
int hashTable::nElem() {
  return numElem;
}
