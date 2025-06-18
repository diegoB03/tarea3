#include "./LList.cpp"
#include "./AQueue.cpp"
#include "./edge.cpp"
#include "../tda/tda_Graph.cpp"

#define VISITED -1
#define UNVISITED -2
#define INFINITY 999999

class Graphl : public Graph {
	private:
		List<Edge>** vertex;    // List headers
		int numVertex, numEdge; // Number of vertices, edges
		int *mark;              // Pointer to mark array
	public:
		Graphl(int numVert)	{ Init(numVert); }
		// Destructor
		~Graphl() { 
			delete [] mark; // Return dynamically allocated memory
			for (int i=0; i<numVertex; i++) 
				delete [] vertex[i];
			delete [] vertex;
		}
		void Init(int n) {
			int i;
			numVertex = n;
			numEdge = 0;
			mark = new int[n]; // Initialize mark array
			for (i=0; i<numVertex; i++) 
				mark[i] = UNVISITED;
			// Create and initialize adjacency lists
			vertex = (List<Edge>**) new List<Edge>*[numVertex];
			for (i=0; i<numVertex; i++)
				vertex[i] = new LList<Edge>();
		}
		
		int n() { return numVertex; } // Number of vertices
		int e() { return numEdge; }   // Number of edges
		
		// Return first neighbor of "v"
		int first(int v) { 
			if (vertex[v]->length() == 0)
				return numVertex; // No neighbor
			vertex[v]->moveToStart();
			Edge it = vertex[v]->getValue();
			return it.vertex();
		}
		// Get v’s next neighbor after w
		int next(int v, int w) {
			Edge it;
			if (isEdge(v, w)) {
				if ((vertex[v]->currPos()+1) < vertex[v]->length()) {
					vertex[v]->next();
					it = vertex[v]->getValue();
					return it.vertex();
				}
			}
			return n(); // No neighbor
		}
		// Set edge (i, j) to "weight"
		void setEdge(int i, int j, int weight) {
			Assert(weight>0, "May not set weight to 0");
			Edge currEdge(j, weight);
			if (isEdge(i, j)) { // Edge already exists in graph
				vertex[i]->remove();
				vertex[i]->insert(currEdge);
			}
			else { // Keep neighbors sorted by vertex index
				numEdge++;
				for (vertex[i]->moveToStart(); vertex[i]->currPos() < vertex[i]->length(); vertex[i]->next()) {
					Edge temp = vertex[i]->getValue();
					if (temp.vertex() > j) break;
				}
				vertex[i]->insert(currEdge);
			}
		}
		// Delete edge (i, j)
		void delEdge(int i, int j) { 
			if (isEdge(i,j)) {
				vertex[i]->remove();
				numEdge--;
			}
		}
		// Is (i,j) an edge?
		bool isEdge(int i, int j) { 
			Edge it;
			for (vertex[i]->moveToStart(); vertex[i]->currPos() < vertex[i]->length(); vertex[i]->next()) { // Check whole list
				Edge temp = vertex[i]->getValue();
				if (temp.vertex() == j) 
					return true;
			}
			return false;
		}
		
		// Return weight of (i, j)
		int weight(int i, int j) { 
			Edge curr;
			if (isEdge(i, j)) {
				curr = vertex[i]->getValue();
				return curr.weight();
			}
			else return 0;
		}
		
		int getMark(int v) { return mark[v]; }
		void setMark(int v, int val) { mark[v] = val; }
};

void PreVisit(Graph* g, int ve) {
	cout << ve << "-";
}

void PostVisit(Graph* g, int ve) {
	cout << ve << "-";
}

void DFS(Graph* G, int v) { // Depth first search
	//PreVisit(G, v); // Take appropriate action
	G->setMark(v, VISITED);
	for (int w=G->first(v); w<G->n(); w = G->next(v,w))
		if (G->getMark(w) == UNVISITED)
			DFS(G, w);
	//PostVisit(G, v); // Take appropriate action
}

void DFSCustomized(Graph* G, int v, int action) { // Depth first search
	if (action == 0)
		PreVisit(G, v); // Take appropriate action
	G->setMark(v, VISITED);
	for (int w=G->first(v); w<G->n(); w = G->next(v,w))
		if (G->getMark(w) == UNVISITED)
			DFSCustomized(G, w, action);
	if (action == 1)
		PostVisit(G, v); // Take appropriate action
}

void BFS(Graph* G, int start, Queue<int>* Q) {
	int v, w;
	Q->enqueue(start); // Initialize Q
	G->setMark(start, VISITED);
	while (Q->length() != 0) { // Process all vertices on Q
		v = Q->dequeue();
		//PreVisit(G, v); // Take appropriate action
		for (w = G->first(v); w < G->n(); w = G->next(v,w))
			cout << "v =" << v << " - w =" << w << "\n";
			if (G->getMark(w) == UNVISITED) {
				G->setMark(w, VISITED);
				Q->enqueue(w);
			}
	}
}

int minVertex(Graph* G, int* D) { // Find min cost vertex
	int i, v = -1;
	// Initialize v to some unvisited vertex
	for (i=0; i<G->n(); i++)
		if (G->getMark(i) == UNVISITED) { 
			v = i; break; 
		}
	for (i++; i<G->n(); i++) // Now find smallest D value
		if ((G->getMark(i) == UNVISITED) && (D[i] < D[v]))
			v = i;
	return v;
}

// Compute shortest path distances from "s".
// Return these distances in "D".
void Dijkstra(Graph* G, int* D, int s) {
	int i, v, w;

	for (int i=0; i<G->n(); i++) // Initialize
		D[i] = INFINITY;
	D[s] = 0;
	//for (i=0; i<G->n(); i++) { // Process the vertices
	for (i=s; i<G->n(); i++) { // Process the vertices
		v = minVertex(G, D);
		if (D[v] == INFINITY) 
			return; // Unreachable vertices
		G->setMark(v, VISITED);
		for (w=G->first(v); w<G->n(); w = G->next(v,w))
			if (D[w] > (D[v] + G->weight(v, w)))
				D[w] = D[v] + G->weight(v, w);
	}
}

void AddEdgetoMST(int arr, int vert) {
	cout << "V[v] = " << arr << " -- v = " << vert << "\n";
}

// Prim’s MST algorithm
void Prim(Graph* G, int* D, int s) { 
	int V[G->n()]; // Store closest vertex
	int i, w;
	for (int i=0; i<G->n(); i++) // Initialize
		D[i] = INFINITY;
	D[s] = 0;
	
	//for (i=0; i<G->n(); i++) { // Process the vertices
	for (i=s; i<G->n(); i++) { // Process the vertices
		int v = minVertex(G, D);
		G->setMark(v, VISITED);
		if (v != s)
			//AddEdgetoMST(V[v], v); // Add edge to MST
		if (D[v] == INFINITY) 
			return; // Unreachable vertices
		for (w=G->first(v); w<G->n(); w = G->next(v,w))
			if (D[w] > G->weight(v,w)) {
				D[w] = G->weight(v,w); // Update distance
				V[w] = v; // Where it came from
			}
	}
}