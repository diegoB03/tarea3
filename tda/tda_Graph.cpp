// Graph abstract class. This ADT assumes that the number
// of vertices is fixed when the graph is created.
class Graph {
	private:
		void operator =(const Graph&) {} // Protect assignment
		Graph(const Graph&) {}           // Protect copy constructor
	public:
		Graph() {}         // Default constructor
		virtual ~Graph() {} // Base destructor
		
		// Initialize a graph of n vertices
		virtual void Init(int n) =0;
		// Return: the number of vertices and edges
		virtual int n() =0;
		virtual int e() =0;
		
		// Return v’s first neighbor
		virtual int first(int v) =0;
		// Return v’s next neighbor
		virtual int next(int v, int w) =0;
		// 
		// i, j: The verticeswgt: Edge weight
		virtual void setEdge(int v1, int v2) =0;
		// Delete an edge
		// i, j: The vertices
		virtual void delEdge(int v1, int v2) =0;
		// Determine if an edge is in the graph
		// i, j: The vertices
		// Return: true if edge i,j has non-zero weight
		virtual bool isEdge(int i, int j) =0;
		

		// Get and Set the mark value for a vertex
		// v: The vertex
		// val: The value to set
		virtual int getMark(int v) =0;
		virtual void setMark(int v, int val) =0;
};