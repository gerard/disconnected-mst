#include "GrafClass.h"

using namespace std;

int main(int argc, char *argv[]) {
	grafo G;

	// Llegim el graf de la entrada estandar
	G.leer();

	// Calculem els representants
	G.representantes();

	// Ara calculem el MST del menor graf, usant Kruskal
	G.KruskalM();

	// Imprimim el resultat, emmagatzemat en la Classe Graf
	printf("%d %d %.2f\n", G.numNodesSubG(), G.numAristasSubG(), G.pesSubG());
}

