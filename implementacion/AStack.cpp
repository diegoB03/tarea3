#include "../tda/tda_Stack.cpp"
#include "../tda/Assert.hpp"
#include "../tda/defines.hpp"

// Array-based stack implementation
template <typename E> class AStack: public Stack<E> {
	private:
		int maxSize; // Maximum size of stack
		int top; // Index for top element
		E *listArray; // Array holding stack elements
	public:
		// Constructor
		AStack(int size =defaultSize) { maxSize = size; top = 0; listArray = new E[size]; }
		// Destructor
		~AStack() { delete [] listArray; } 
		// Reinitialize
		void clear() { top = 0; } 
		// Put "it" on stack
		void push(const E& it) { 
			Assert(top != maxSize, "Stack is full");
			listArray[top++] = it;
		}
		// Pop top element
		E pop() { 
			Assert(top != 0, "Stack is empty");
			return listArray[--top];
		}
		// Return top element
		const E& topValue() const { 
			Assert(top != 0, "Stack is empty");
			return listArray[top-1];
		}
		// Return length
		int length() const { return top; } 
};