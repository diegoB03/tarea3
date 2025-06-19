#include "./LList.cpp"
#include "./AQueue.cpp"
#include "./AStack.cpp"
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

		
		int getMark(int v) { return mark[v]; }
		void setMark(int v, int val) { mark[v] = val; }
};

void doSomething(Graph* g, int ve) {
	cout << ve << "-";
}

void DFS(Graph* G, int v) { // Depth first search
	G->setMark(v, VISITED);
	for (int w=G->first(v); w<G->n(); w = G->next(v,w))
		if (G->getMark(w) == UNVISITED)
			DFS(G, w);
}

void DFSCustomized(Graph* G, int v, int action) { // Depth first search
	if (action == 1)
		doSomething(G, v); // Take appropriate action
	G->setMark(v, VISITED);

	for (int w=G->first(v); w<G->n(); w = G->next(v,w))
		if (G->getMark(w) == UNVISITED)
			DFSCustomized(G, w, action);
}

void DFSNonRecursive(Graph* G, int start) {
	// Non reursive Depth first search
	AStack<int>* S=new AStack<int>; // main stack
	AStack<int>* aux=new AStack<int>; // auxiliary stack
	S->push(start); // Initialize S
	G->setMark(start, VISITED);
	while (S->length() != 0) { // Process all vertices on S
		int v = S->pop();
		doSomething(G, v); // Take appropriate action
		for (int w = G->first(v); w < G->n(); w = G->next(v,w)){
			if (G->getMark(w) == UNVISITED) {
				G->setMark(w, VISITED);
				aux->push(w); // puts all non visited vertexes on auxiliary stack (biggest to smallest)
			}
		}
		while (aux->length() != 0) { // puts all non visited vertexes on main stack (smallest to biggest)
			int v = aux->pop();
			S->push(v);
		}
	}
}

void BFS(Graph* G, int start, Queue<int>* Q) {
	int v, w;
	Q->enqueue(start); // Initialize Q
	G->setMark(start, VISITED);
	while (Q->length() != 0) { // Process all vertices on Q
		v = Q->dequeue();
		doSomething(G, v); // Take appropriate action
		for (w = G->first(v); w < G->n(); w = G->next(v,w))
			//cout << "v =" << v << " - w =" << w << "\n";
			if (G->getMark(w) == UNVISITED) {
				G->setMark(w, VISITED);
				Q->enqueue(w);
			}
	}
}
