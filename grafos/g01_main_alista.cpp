#include "implementacion/Graphl_1.cpp"
#include <iostream>

#define peso 999
using namespace std;

void esArco(Graphl *g, int i, int j) {
	if (g->isEdge(i, j)) 
		cout << "Es un arco(" << i << "," << j << ")" << "\n";
	else
		cout << "NO es un arco(" << i << "," << j << ")" << "\n";
}

void pesoArco(Graphl *g, int i, int j) {
		cout << "Peso del arco(" << i << "," << j << ") es: " << g->weight(i, j) << "\n";
}

void miVecino(Graphl *g, int i, int j) {
		cout << "Vecino del arco(" << i << "," << j << ") es: " << g->next(i, j) << "\n";
}

void recorrerGrafo(Graphl *g) {
    int v;
    for (v = 0; v < g->n(); v++) 
        g->setMark(v, UNVISITED);
    for (v = 0; v < g->n(); v++)
        if (g->getMark(v) == UNVISITED) {
			cout << "Vertice: " << v << "\n";
			g->setMark(v, VISITED);
		}
}

int main() {
	cout << "Hola mundo ..." << "\n";
	int vertices = 5;
	
	/* Creación de grafo */
	Graphl *grf = new Graphl(vertices);
	
	/* Clase de hoy */
	grf->setEdge(0, 1, 10);
	grf->setEdge(0, 2, 3);
	
	grf->setEdge(1, 2, 5);
	grf->setEdge(1, 3, 6);	
	
	grf->setEdge(2, 4, 15);
	
	grf->setEdge(3, 4, 11);
	
	/* Consultas al grafo */
	cout << "Numero de vertices: " << grf->n() << "\n";
	cout << "Numero de arcos: " << grf->e() << "\n";
	cout << "\n";

	esArco(grf, 1, 2);
	esArco(grf, 1, 0);
	miVecino(grf, 1, 2);
	recorrerGrafo(grf);
	
}