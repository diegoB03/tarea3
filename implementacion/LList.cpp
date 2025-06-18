#include "../tda/tda_List.cpp"
#include "../tda/tda_Link.cpp"
#include "../tda/Assert.hpp"
#include "../tda/defines.hpp"

// Linked list implementation
template <typename E> class LList: public List<E> {
	private:
		Link<E>* head; 	// Pointer to list header
		Link<E>* tail; 	// Pointer to last element
		Link<E>* curr; 	// Access to current element
		int listSize; 	// Size of list
		int pos;		// Position of current element
		void init() { 	// Intialization helper method
			curr = tail = head = new Link<E>;
			listSize = 0;
			pos = 0;
		}
		void removeall() { // Return link nodes to free store
			while(head != NULL) {
				curr = head;
				head = head->next;
				delete curr;
			}
			pos = 0;
		}
	public:
		LList(int size=defaultSize) { init(); } // Constructor
		~LList() { removeall(); } // Destructor
		void print() const; // Print list contents
		void clear() { removeall(); init(); } // Clear list
		// Insert "it" at current position
		void insert(const E& it) {
			curr->next = new Link<E>(it, curr->next);
			if (tail == curr) tail = curr->next; // New tail
			listSize++;
		}
		void append(const E& it) { // Append "it" to list
			tail = tail->next = new Link<E>(it, NULL);
			listSize++;
		}
		// Remove and return current element
		E remove() {
			Assert(curr->next != NULL, "No element");
			E it = curr->next->element; // Remember value
			Link<E>* ltemp = curr->next; // Remember link node
			if (tail == curr->next) tail = curr; // Reset tail
			curr->next = curr->next->next; // Remove from list
			delete ltemp; // Reclaim space
			listSize--; // Decrement the count
			return it;
		}
		void moveToStart() { curr = head; pos = 0;} // Place curr at list start
		void moveToEnd() { curr = tail; } // Place curr at list end
		// Move curr one step left; no change if already at front
		void prev() {
			if (curr == head) return; // No previous element
			Link<E>* temp = head;
			// March down list until we find the previous element
			while (temp->next!=curr) temp=temp->next;
			curr = temp;
			pos--;
		}
		// Move curr one step right; no change if already at end
		void next()	{ if (curr != tail) curr = curr->next; pos++;}
		int length() const { return listSize; } // Return length
		// Return the position of the current element
		int currPos() const {
			Link<E>* temp = head;
			int i;
			for (i=0; curr != temp; i++) temp = temp->next;
			return i;
		}
		// Move down list to "pos" position
		void moveToPos(int pos) {
			Assert ((pos>=0)&&(pos<=listSize), "Position out of range");
			curr = head;
			for(int i=0; i<pos; i++) curr = curr->next;
		}
		const E& getValue() const { // Return current element
			Assert(curr->next != NULL, "No value");
			return curr->next->element;
		}
};