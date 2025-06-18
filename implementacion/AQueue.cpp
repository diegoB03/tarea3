#include "../tda/tda_Queue.cpp"
#include "../tda/Assert.hpp"
#include "../tda/defines.hpp"

// Array-based queue implementation
template <typename E> class AQueue: public Queue<E> {
	private:
		int maxSize; // Maximum size of queue
		int front; // Index of front element
		int rear; // Index of rear element
		E *listArray; // Array holding queue elements
	public:
		// Constructor
		AQueue(int size =defaultSize) { 
			// Make list array one position larger for empty slot
			maxSize = size+1;
			rear = 0; front = 1;
			listArray = new E[maxSize];
		}
		// Destructor
		~AQueue() { delete [] listArray; }
		// Reinitialize
		void clear() { rear = 0; front = 1; } 
		// Put "it" in queue
		void enqueue(const E& it) { 
			Assert(((rear+2) % maxSize) != front, "Queue is full");
			rear = (rear+1) % maxSize; // Circular increment
			listArray[rear] = it;
		}
		// Take element out
		E dequeue() { 
			Assert(length() != 0, "Queue is empty");
			E it = listArray[front];
			front = (front+1) % maxSize; // Circular increment
			return it;
		}
		// Get front value
		const E& frontValue() const { 
			Assert(length() != 0, "Queue is empty");
			return listArray[front];
		}
		// Return length
		virtual int length() const 
		{ return ((rear+maxSize) - front + 1) % maxSize; }
};