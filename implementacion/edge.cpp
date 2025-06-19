// Edge class for Adjacency List graph representation
class Edge {
private:
    int vert, wt;
public:
    Edge() { vert = -1; wt = 1; }
    Edge(int v, int w = 1) { vert = v; wt = w; }

    int vertex() const { return vert; }
    int weight() const { return wt; }
};
