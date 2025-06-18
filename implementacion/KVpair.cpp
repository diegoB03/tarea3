template <typename Key, typename E>
class KVpair {
	private:
		Key k;
		E e;
	public:
		// Constructors
		KVpair() {}
		KVpair(Key kval, E eval) { k = kval; e = eval; }
		// Copy constructor
		KVpair(const KVpair& o) { k = o.k; e = o.e; } 
		// Assignment operator
		void operator =(const KVpair& o) { k = o.k; e = o.e; } 
		// Data member access functions
		Key key() { return k; }
		void setKey(Key ink) { k = ink; }
		E value() { return e; }
};