#include "../tda/tda_Stack.cpp"
#include "../tda/tda_Link.cpp"
#include "../tda/Assert.hpp"
#include "../tda/defines.hpp"

// Linked stack implementation
template <typename E> class LStack: public Stack<E> {
	private:
		Link<E>* top; // Pointer to first element
		int size; // Number of elements
	public:
		// Constructor
		LStack(int sz =defaultSize) { top = NULL; size = 0; }
		// Destructor
		~LStack() { clear(); } 
		// Reinitialize
		void clear() { 
			while (top != NULL) { // Delete link nodes
				Link<E>* temp = top;
				top = top->next;
				delete temp;
			}
			size = 0;
		}
		// Put "it" on stack
		void push(const E& it) { 
			top = new Link<E>(it, top);
			size++;
		}
		// Remove "it" from stack
		E pop() { 
			Assert(top != NULL, "Stack is empty");
			E it = top->element;
			Link<E>* ltemp = top->next;
			delete top;
			top = ltemp;
			size--;
			return it;
		}
		// Return top value
		const E& topValue() const { 
			Assert(top != 0, "Stack is empty");
			return top->element;
		}
		int length() const { return size; } // Return length
};