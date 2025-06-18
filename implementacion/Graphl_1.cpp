#include "./LList.cpp"
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

