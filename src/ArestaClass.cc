#include "ArestaClass.h"

/*
Implementació básica de la Classe Aresta
*/

arista::arista (int a, int b, float c) {
  u = a;  v = b;  w = c;
}

arista::arista () {}

arista::~arista() {}

bool arista::operator == (arista& a) {
  return w==a.w;
}

bool arista::operator < (arista& a) {
  return w<a.w;
}

bool arista::operator <= (arista& a) {
  return w<=a.w;
}

void arista::operator = (arista& a) {
  u=a.u;  v=a.v;  w=a.w;
}

int arista::nodoU () {
  return u;
}

int arista::nodoV () {
  return v;
}

float arista::peso () {
  return w;
}

void arista::inserir(int a, int b, float c) {
  u=a;	v=b;  w=c;
}
