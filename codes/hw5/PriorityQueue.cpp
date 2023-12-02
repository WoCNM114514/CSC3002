/*
 * File: PriorityQueue.cpp
 * ---------------------------
 * This file contains a unit test of the PriorityQueue class.
 */

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
// #include "CSC3002OJActive/assignment5/lib.h" // for OJ test
// #include "CSC3002OJActive/assignment5/priorityqueue.h" // for OJ test

#include "lib.h" // for local test
#include "priorityqueue.h" // for local test

using namespace std;

template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue() {
   clear();
}

/*
 * Implementation notes: ~PriorityQueue destructor
 * -----------------------------------------------
 * All of the dynamic memory is allocated in the Vector class, so no work
 * is required at this level.
 */

template <typename ValueType>
PriorityQueue<ValueType>::~PriorityQueue() {
   /* Empty */
}

template <typename ValueType>
int PriorityQueue<ValueType>::size() const {
   return count;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::isEmpty() const {
   return count == 0;
}

template <typename ValueType>
void PriorityQueue<ValueType>::clear() {
   heap.clear();
   count = 0;
}

int backIndex; // create an index to keep track of the last element

template <typename ValueType>
void PriorityQueue<ValueType>::enqueue(ValueType value, double priority) {
   // TODO
   if (count == heap.size()) heap.push_back(HeapEntry());
   int index = count++;
   heap[index].value = value;
   heap[index].priority = priority;
   heap[index].sequence = enqueueCount++;
   if (index == 0 || takesPriority(backIndex, index)) backIndex = index;
   while (index > 0) {
      // compute the parent node and swap if necessary
       int parent = (index - 1) / 2;
       if (takesPriority(parent, index)) break;
       swapHeapEntries(parent, index);
       index = parent;
   }
}

/*
 * Implementation notes: dequeue, peek, peekPriority
 * -------------------------------------------------
 * These methods must check for an empty queue and report an error if there
 * is no first element.
 */

template <typename ValueType>
ValueType PriorityQueue<ValueType>::dequeue() {
   // TODO
   if (count == 0) error("this is a empty queue");
   count--;
   bool Back = (backIndex == count);
   ValueType value = heap[0].value;
   swapHeapEntries(0, count);
   int index = 0;
   while (true) {
      // compute the child nodes and swap if necessary
       int left = 2 * index + 1;
       int right = 2 * index + 2;
       if (left >= count) break;
       int child = left;
       if (right < count && takesPriority(right, left)) child = right;
       if (takesPriority(index, child)) break;
       swapHeapEntries(index, child);
       index = child;
   }
   if (Back) backIndex = index;
   return value;
}

template <typename ValueType>
ValueType PriorityQueue<ValueType>::peek() const {
   //TODO
   if (isEmpty()) error("the queue is empty");
   // fetch the value of the first element
   return heap[0].value;
}

template <typename ValueType>
double PriorityQueue<ValueType>::peekPriority() const {
   // TODO
   if (isEmpty()) error("the queue is empty");
   // fetch the priority of the first element
   return heap[0].priority;
}

template <typename ValueType>
void enqueueHeap(ValueType & value, double priority) {
   //TODO
}

template <typename ValueType>
ValueType dequeueHeap(){
   //TODO
}

template <typename ValueType>
bool PriorityQueue<ValueType>::takesPriority(int i1, int i2) {
   /* Return true if i1 takes the priority */

   //TODO
   if (heap[i1].priority < heap[i2].priority) return true;
   if (heap[i1].priority > heap[i2].priority) return false;
   return (heap[i1].sequence < heap[i2].sequence);
}

template <typename ValueType>
void PriorityQueue<ValueType>::swapHeapEntries(int i1, int i2) {
   /* Swap elements in the two positions */

   //TODO
   // swap two elements throw a tempel variable
   HeapEntry temp;
   temp = heap[i1];
   heap[i1] = heap[i2];
   heap[i2] = temp;
}

template <typename ValueType>
std::string PriorityQueue<ValueType>::toString() {
   /* convert the PriorityQueue into a printable String */

   //TODO
   ostringstream os;
   os << *this;
   return os.str();
}

template <typename ValueType>
std::ostream & operator<<(std::ostream & os,
                          const PriorityQueue<ValueType> & pq) {
   /* give the output of all the elements in queue(not dequeue)
      i.e.: cout << pq gives the output of all the content in current queue without change pq */

   //TODO
   os << "{";
   PriorityQueue<ValueType> copy = pq;
   int len = pq.size();
   for (int i = 0; i < len; i++) {
       if (i > 0) os << ", ";
       os << copy.peekPriority() << ":";
       writeGenericValue(os, copy.dequeue(), true);
   }
   return os << "}";
}

int main() {
   PriorityQueue<string> pq;
   string value;
   double priority;

   string in_pair;
   while(getline(cin,in_pair)){
      int sp = in_pair.find(' ');
      value = in_pair.substr(0, sp);
      priority = stod(in_pair.substr(sp+1, in_pair.size()));
      pq.enqueue(value, priority);
   }
   cout<<"pq.size() = "<<pq.size()<<endl;
   cout<<"pq.toString() : "<<pq.toString()<<endl;
   int init_len = pq.size();
   for (int i = 0; i<init_len; i++) {
      cout<<"i="<<i<<": pq.peek() = "<<pq.peek()<<endl;
      cout<<"i="<<i<<": pq.dequeue() = "<<pq.dequeue()<<endl;
   }
   cout<<"pq.isEmpty(): "<<boolalpha<<pq.isEmpty()<<endl;
   return 0;
}
