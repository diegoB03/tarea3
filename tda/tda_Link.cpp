// Singly linked list node
template <typename E> class Link {
	public:
		E element; 	// Value for this node
		Link *next; // Pointer to next node in list
		// Constructors
		Link(const E& elemval, Link* nextval = nullptr)	{ element = elemval; next = nextval; }
		Link(Link* nextval = nullptr) { next = nextval; }
};