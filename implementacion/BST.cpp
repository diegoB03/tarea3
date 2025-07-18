#include "../tda/tda_Dictionary.cpp"
#include "./BSTNode.cpp"
#include "./AStack.cpp"
#include "./AQueue.cpp"

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key,E> {
	private:
		// Root of the BST
		BSTNode<Key,E>* root; 
		// Number of nodes in the BST
		int nodecount; 
		// Private "helper" functions
		void clearhelp(BSTNode<Key, E>*);
		BSTNode<Key,E>* inserthelp(BSTNode<Key, E>*, const Key&, const E&);
		BSTNode<Key,E>* deletemin(BSTNode<Key, E>*);
		BSTNode<Key,E>* getmin(BSTNode<Key, E>*);
		BSTNode<Key,E>* removehelp(BSTNode<Key, E>*, const Key&);
		E findhelp(BSTNode<Key, E>*, const Key&) const;
		void printhelp(BSTNode<Key, E>*, int) const;
	public:
		// Constructor
		BST() { root = NULL; nodecount = 0; } 
		// Destructor
		~BST() { clearhelp(root); } 
		
		BSTNode<Key,E>* getRoot() { return root; }
		
		// Reinitialize tree
		void clear() { clearhelp(root); root = NULL; nodecount = 0; }
		// Insert a record into the tree.
		// k Key value of the record.
		// e The record to insert.
		void insert(const Key& k, const E& e) {
			root = inserthelp(root, k, e);
			nodecount++;
		}
		// Remove a record from the tree.
		// k Key value of record to remove.
		// Return: The record removed, or NULL if there is none.
		E remove(const Key& k) {
			E temp = findhelp(root, k); // First find it
			if (temp != 0) {
				root = removehelp(root, k);
				nodecount--;
			}
			return temp;
		}
		// Remove and return the root node from the dictionary.
		// Return: The record removed, null if tree is empty.
		E removeAny() { // Delete min value
			if (root != NULL) {
				E temp = root->element();
				root = removehelp(root, root->key());
				nodecount--;
				return temp;
			}
			else return 0;
		}
		// Return Record with key value k, NULL if none exist.
		// k: The key value to find. */
		// Return some record matching "k".
		// Return true if such exists, false otherwise. If
		// multiple records match "k", return an arbitrary one.
		E find(const Key& k) const { return findhelp(root, k); }
		// Return the number of records in the dictionary.
		int size() { return nodecount; }
		// Print the contents of the BST
		void print() const { 
			if (root == NULL) std::cout << "The BST is empty.\n";
			else printhelp(root, 0);
		}
};

template <typename Key, typename E>
void preOrder(BSTNode<Key, E>* root) {
	if (root == NULL) return; // Empty subtree, do nothing
	std::cout << root->key() << "\n"; // Perform desired action
	preOrder(root->left());
	preOrder(root->right());
}

template <typename Key, typename E>
void postOrder(BSTNode<Key, E>* root) {
	if (root == NULL) return; // Empty subtree, do nothing
	postOrder(root->left());
	postOrder(root->right());
	std::cout << root->key() << "\n"; // Perform desired action
}

template <typename Key, typename E>
void inOrder(BSTNode<Key, E>* root) {
	if (root == NULL) return; // Empty subtree, do nothing
	inOrder(root->left());
	std::cout << root->key() << "\n"; // Perform desired action
	inOrder(root->right());
}

template <typename Key, typename E>
void porNiveles(BSTNode<Key, E>* root, int level) {
	if (root == NULL) return; // Empty tree
	porNiveles(root->left(), level+1); // Do left subtree
	for (int i=0; i<level; i++) // Indent to level
		std::cout << " ";
	std::cout << root->key() << " - level: " << level << "\n"; // Print node value
	porNiveles(root->right(), level+1); // Do right subtree
}
	
template <typename Key, typename E>
E BST<Key, E>::findhelp(BSTNode<Key, E>* root, const Key& k) const {
	if (root == NULL) return 0; // Empty tree
	if (k < root->key())
		return findhelp(root->left(), k); // Check left
	else if (k > root->key())
		return findhelp(root->right(), k); // Check right
	else 
		return root->element(); // Found it
}

template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp(BSTNode<Key, E>* root, const Key& k, const E& it) {
	if (root == NULL) // Empty tree: create node
		return new BSTNode<Key, E>(k, it, NULL, NULL);
	if (k < root->key())
		root->setLeft(inserthelp(root->left(), k, it));
	else root->setRight(inserthelp(root->right(), k, it));
	return root; // Return tree with node inserted
}

template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::deletemin(BSTNode<Key, E>* rt) {
	if (rt->left() == NULL) // Found min
		return rt->right();
	else { // Continue left
		rt->setLeft(deletemin(rt->left()));
	return rt;
	}
}

template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::getmin(BSTNode<Key, E>* rt) {
	if (rt->left() == NULL)
		return rt;
	else return getmin(rt->left());
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E> 
BSTNode<Key, E>* BST<Key, E>::removehelp(BSTNode<Key, E>* rt, const Key& k) {
	if (rt == NULL) return NULL; // k is not in tree
	else if (k < rt->key())
		rt->setLeft(removehelp(rt->left(), k));
	else if (k > rt->key())
		rt->setRight(removehelp(rt->right(), k));
	else { // Found: remove it
		BSTNode<Key, E>* temp = rt;
		if (rt->left() == NULL) { // Only a right child
			rt = rt->right(); // so point to right
			delete temp;
		}
		else if (rt->right() == NULL) { // Only a left child
			rt = rt->left(); // so point to left
			delete temp;
		}
		else { // Both children are non-empty
			BSTNode<Key, E>* temp = getmin(rt->right());
			rt->setElement(temp->element());
			rt->setKey(temp->key());
			rt->setRight(deletemin(rt->right()));
			delete temp;
		}
	}
	return rt;
}

template <typename Key, typename E>
void BST<Key, E>::clearhelp(BSTNode<Key, E>* root) {
	if (root == NULL) return;
	clearhelp(root->left());
	clearhelp(root->right());
	delete root;
}

template <typename Key, typename E>
void BST<Key, E>::printhelp(BSTNode<Key, E>* root, int level) const {
	if (root == NULL) return; // Empty tree
	printhelp(root->left(), level+1); // Do left subtree
	for (int i=0; i<level; i++) // Indent to level
		std::cout << " ";
	std::cout << root->key() << "\n"; // Print node value
	printhelp(root->right(), level+1); // Do right subtree
}