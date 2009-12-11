class hashTable{
  struct hashNode {char *key; int value; struct hashNode *next;};
  hashNode **Table;  // Vector de punteros a listas de nodos. Cada posisi�n del
     // vector representa una cubeta. El entero 'value' de cada nodo se utiliza
                          // realizar una funci�n de "mapeo" f:cadena -> entero
  int sizeTable;
  int sizeVector;
  int numElem;
  hashNode *hNodes;
  char *cadenes;
  char *punt;
  unsigned int hashFunction(const char *cadena);
public:
  hashTable (int s);
  ~hashTable();
  int keyToIndex (char *newKey);       // Funci�n f:cadena -> entero
  char *indexToKey (int i);                 // Funci�n f^{-1}: entero -> cadena
  void statistics ();
  int nElem ();
};

