#include "../implementacion/Graphl_2.cpp"
#include <iostream>

#define peso 999
using namespace std;

void esArco(Graphl *g, int i, int j) {
	if (g->isEdge(i, j)) 
		cout << "Es un arco(" << i << "," << j << ")" << "\n";
	else
		cout << "NO es un arco(" << i << "," << j << ")" << "\n";
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
	int vertices = 6;
	
	/* Creación de grafo */
	Graphl *grf = new Graphl(vertices);
	
	/* Clase de hoy */
	grf->setEdge(0, 2);
	grf->setEdge(2, 0);
	grf->setEdge(0, 4);
	grf->setEdge(4, 0);

	grf->setEdge(1, 2);
	grf->setEdge(2, 1);
	grf->setEdge(1, 5);	
	grf->setEdge(5, 1);
	grf->setEdge(5, 2);
	grf->setEdge(5, 3);
	grf->setEdge(5, 4);
	
	grf->setEdge(2, 3);
	grf->setEdge(3, 2);
	grf->setEdge(2, 5);
	
	grf->setEdge(3, 5);
	grf->setEdge(4, 5);	
	
	/* Consultas al grafo */
	cout << "Numero de vertices: " << grf->n() << "\n";
	cout << "Numero de arcos: " << grf->e() << "\n";
	cout << "\n";
	recorrerGrafo(grf);
	cout << "\n";
	
	// Recorrido DFS
	for (int i = 0; i < grf->n(); i++) 
        grf->setMark(i, UNVISITED);
	DFS(grf, 1);

	// Recorrido DFS arreglado
	cout << "Recorrido DFS recursivo ..." << "\n";
	for (int i = 0; i < grf->n(); i++) 
        grf->setMark(i, UNVISITED);
	DFSCustomized(grf, 0, 1); cout << "\n";

	// Recorrido DFS si recursividad
	cout << "Recorrido DFS sin recursividad..." << endl;
	for (int i = 0; i < grf->n(); i++)
		grf->setMark(i, UNVISITED);
	DFSNonRecursive(grf,0); cout << "\n";
	
	// Recorrido DFS
	cout << "Recorrido BFS usando colas..." << "\n";
	for (int i = 0; i < grf->n(); i++) 
        grf->setMark(i, UNVISITED);
	AQueue<int>* cola = new AQueue<int>(defaultSize);
	// Recorrido BFS
	BFS(grf, 0, cola);
	cout << "\nHasta luego ..." << "\n";
}