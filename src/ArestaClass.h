#ifndef _ARISTA_
#define _ARISTA_

class arista{
  int u, v;                  		// u i v son els nodes de l'aresta
  float w;                          // w es el pes de l'aresta
public:
  arista (int a, int b, float c);    // Definim el constructor
  arista ();
  ~arista();
  bool operator == (arista& a);
  bool operator < (arista& a);
  bool operator <= (arista& a);
  void operator = (arista& a);
  int nodoU ();        				// Torna un node de l'aresta
  int nodoV ();            			// Torna l'altre node de l'aresta
  float peso ();                	// Torna el pes de l'aresta
  void inserir (int a, int b, float c);
};

#endif














