#include "../implementacion/Graphl_2.cpp"
#include <iostream>

using namespace std;

void EntradasySalidas(Graphl *grf){
    int vertices = grf->n();
    int* salidas = new int[vertices](); 
    int* entradas = new int[vertices]();  
    
    for(int vertice = 0; vertice < vertices; vertice++){
        for(int vecino = grf->first(vertice); vecino < vertices; vecino = grf->next(vertice, vecino)){
            salidas[vertice]++;
            entradas[vecino]++;
        }
        cout << endl;
        cout << "Vertice " << vertice << ":" << endl;
        cout << "Entradas: " << entradas[vertice] << endl;
        cout << "Salidas: " << salidas[vertice] << endl; 
    }
    
    delete[] entradas;
    delete[] salidas;
}


int main(){
	int vertices = 6;
	
	/* Creación de grafo */
	Graphl *grf = new Graphl(vertices);
    grf->setEdge(0, 2, 0);
    grf->setEdge(0, 4, 0);

    grf->setEdge(1, 2, 0);
    grf->setEdge(1, 5, 0);
    
    grf->setEdge(2, 3, 0);
    grf->setEdge(2, 5, 0);

    grf->setEdge(3, 5, 0);

    grf->setEdge(4, 5, 0);
    EntradasySalidas(grf);

}