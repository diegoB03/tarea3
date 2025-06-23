#include <iostream>
#include <fstream>
#include <sstream>
#include "implementacion/Graphl_2.cpp"

using namespace std;
using std::string;
using std::stoi;

struct infografo {
    string linea;
    int arcosNum, nodosNum, conducNum;
    int arcos[90][2];       // Lista de arcos
    int conductores[5];    // Lista de conductores
};

infografo info;
Graphl* grafo;


/*****
 * void datosGrafo
 *****
 * Lee los datos desde data1.txt y los carga en una estructura infografo
 *****
 * Input: ninguno
 *****
 * Returns: estructura infografo con todos los datos cargados
*****/
infografo datosGrafo() {
    fstream archivo("data1.txt", ios::in);
    infografo info;
    string linea;
    int lineaActual = 0;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        exit(1);
    }

    while (getline(archivo, linea)) {
        istringstream ss(linea);
        if (lineaActual == 0) {
            // Primera línea: nodos, arcos, conductores
            ss >> info.nodosNum >> info.arcosNum >> info.conducNum;
        } else if (lineaActual <= info.arcosNum) {
            // Leer arcos
            ss >> info.arcos[lineaActual - 1][0] >> info.arcos[lineaActual - 1][1];
        } else {
            // Última línea: conductores
            for (int i = 0; i < info.conducNum; i++) {
                ss >> info.conductores[i];
            }
        }
        lineaActual++;
    }

    archivo.close();
    return info;
}


/*****
 * Graphl* crearArcos
 *****
 * Construye un grafo a partir de los datos leídos
 *****
 * Input: estructura infografo con nodos y arcos
 * Returns: puntero a Graphl ya inicializado
*****/
Graphl* crearArcos(infografo& info) {
    Graphl* g = new Graphl(info.nodosNum + 1);  // +1 por si usan nodos 1-based
    for (int i = 0; i < info.arcosNum; i++) {
        g->setEdge(info.arcos[i][0], info.arcos[i][1]);
    }
    return g;
}


void BFS_Camino(Graph* G, int start, int destino, int padres[], int& distanciaFinal) {
    distanciaFinal = -1;  // Valor por defecto si no hay camino

    if (start == destino) {
        for (int i = 0; i < G->n(); i++) padres[i] = -1;
        padres[start] = -1;
        distanciaFinal = 0;
        return;
    }

    AQueue<int>* Q = new AQueue<int>(100);
    int visitado[100] = {0};
    for (int i = 0; i < G->n(); i++) padres[i] = -1;

    Q->enqueue(start);
    G->setMark(start, VISITED);
    visitado[start] = 1;

    while (Q->length() != 0) {
        int v = Q->dequeue();

        for (int w = G->first(v); w < G->n(); w = G->next(v, w)) {
            if (!visitado[w]) {
                G->setMark(w, VISITED);
                padres[w] = v;
                visitado[w] = 1;
                Q->enqueue(w);

                if (w == destino) {
                    // Ya encontramos el destino, salimos
                    goto calcular_distancia;
                }
            }
        }
    }

calcular_distancia:
    if (padres[destino] == -1) {
        distanciaFinal = -1;
        delete Q;
        return;
    }

    distanciaFinal = 0;
    for (int p = destino; p != -1; p = padres[p]) distanciaFinal++;

    distanciaFinal--;  // Excluye nodo de inicio
    delete Q;
}


void imprimirRuta(int destino, int padres[]) {
    if (destino == -1) return;
    imprimirRuta(padres[destino], padres);
    cout << destino << " ";
}


/*****
 * void solicitar_uber
 *****
 * Recibe un viaje (origen, destino) y encuentra el conductor más cercano,
 * el camino más corto y el costo total.
 *****
 * Input:
 * int origen      : Nodo del pasajero
 * int destino     : Nodo de destino
 *****
 * Uses:
 * infografo info  : debe estar declarado global o accesible
 * Graphl* grafo   : también debe estar accesible
 *****
 * Output:
 * Muestra la ruta y el costo, y actualiza la posición del conductor
*****/

void solicitar_uber(int origen, int destino) {
    int mejorConductor = -1;
    int mejorDistancia = 999;
    int padresConductor[100];

    // Buscar el conductor más cercano al pasajero
    for (int i = 0; i < info.conducNum; i++) {
        int tempPadres[100];
        int distTemp;

        // Importante: ya no necesitas setMark aquí porque BFS_Camino lo hace internamente
        BFS_Camino(grafo, info.conductores[i], origen, tempPadres, distTemp);

        // Depuración
        cout << "🔎 Conductor " << info.conductores[i]
             << " → pasajero " << origen
             << " | distancia = " << distTemp << endl;

        // Elegir al mejor conductor (mínima distancia válida)
        if (distTemp >= 0 && distTemp < mejorDistancia) {
            mejorConductor = info.conductores[i];
            mejorDistancia = distTemp;
            for (int j = 0; j < 100; j++) padresConductor[j] = tempPadres[j];
        }
    }

    if (mejorConductor == -1) {
        cout << "🚫 Ningún conductor pudo llegar al pasajero.\n";
        return;
    }

    // Mostrar ruta del conductor al pasajero
    cout << "✅ Conductor asignado: " << mejorConductor
         << " (distancia = " << mejorDistancia << ")\n";
    cout << "🛣️  Ruta conductor → pasajero: ";
    imprimirRuta(origen, padresConductor);
    cout << endl;

    // Calcular viaje del pasajero al destino
    int padresViaje[100], distViaje;
    BFS_Camino(grafo, origen, destino, padresViaje, distViaje);

    if (distViaje < 0) {
        cout << "🚧 No se puede llegar al destino desde el pasajero.\n";
        return;
    }

    // Mostrar ruta completa y costo
    int costo = 300 * mejorDistancia + 500 * distViaje;
    cout << "🛣️  Ruta pasajero → destino: ";
    imprimirRuta(destino, padresViaje);
    cout << endl;

    cout << "💰 Costo total: " << costo << "\n";

    // Actualizar posición del conductor
    for (int i = 0; i < info.conducNum; i++) {
        if (info.conductores[i] == mejorConductor) {
            info.conductores[i] = destino;
            break;
        }
    }
}


//DEPURACION GRAFO BORRAR DESPUES
void imprimirGrafo(Graphl* grafo, int maxNodo) {
    cout << "\n--- DEPURACIÓN: Arcos del grafo ---\n";
    for (int i = 1; i <= maxNodo; i++) {
        bool tieneVecinos = false;
        for (int j = grafo->first(i); j < grafo->n(); j = grafo->next(i, j)) {
            cout << i << " → " << j << "\n";
            tieneVecinos = true;
        }
        if (!tieneVecinos) {
            cout << i << " → (sin vecinos)\n";
        }
    }
    cout << "------------------------------------\n";
}


int main() {

    int inicio, fin;
    info = datosGrafo();
    grafo = crearArcos(info);

//    imprimirGrafo(grafo, info.nodosNum);

//    cout << "Conductores ubicados en:\n";
//    for (int i = 0; i < info.conducNum; i++) {
//        cout << "Nodo " << info.conductores[i] << endl;
//    }

    // Verificación visual: imprimir arcos
//    cout << "Lista de arcos cargados:\n";
//    for (int i = 1; i <= info.nodosNum; i++) {
//        for (int j = grafo->first(i); j < grafo->n(); j = grafo->next(i, j)) {
//            cout << i << " → " << j << "\n";
//        }
//    }

    int padresTest[100], distTest;
    for (int j = 0; j < grafo->n(); j++) grafo->setMark(j, UNVISITED);
    BFS_Camino(grafo, 2, 30, padresTest, distTest);

    cout << "\nPrueba BFS directo desde 2 a 30:\n";
    cout << "Distancia: " << distTest << "\n";
    cout << "Ruta: ";
    imprimirRuta(30, padresTest);
    cout << "\n";


    while (true){
        cout << "Ingrese viaje (origen destino): ";
        cin >> inicio >> fin;
        if (inicio == -1 && fin == -1) break;
        solicitar_uber(inicio, fin);
    }

    delete grafo;
    return 0;
}
