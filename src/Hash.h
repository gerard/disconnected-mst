class hashTable{
  struct hashNode {char *key; int value; struct hashNode *next;};
  hashNode **Table;  // Vector de punteros a listas de nodos. Cada posisión del
     // vector representa una cubeta. El entero 'value' de cada nodo se utiliza
                          // realizar una función de "mapeo" f:cadena -> entero
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
  int keyToIndex (char *newKey);       // Función f:cadena -> entero
  char *indexToKey (int i);                 // Función f^{-1}: entero -> cadena
  void statistics ();
  int nElem ();
};

