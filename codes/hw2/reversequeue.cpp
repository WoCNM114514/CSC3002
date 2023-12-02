/* P1:
 * File: reversequeue.cpp
 * ----------------------
 * This file tests the ReverseQueue function.
 */

#include <iostream>
//#include "CSC3002OJActive/assignment2/reversequeue.h" // For OJ test
#include "reversequeue.h" // For local test
#include <stack>
#include <queue>
using namespace std;

/* TODO PART:
 * Function: reverseQueue
 * Usage: reverseQueue(queue);
 * ---------------------------
 * Reverses the order of the elements in a queue.  This
 * implementation does so by using a stack to hold the
 * values as they are being reversed.
 */

void reverseQueue(queue<string> & queue) {
   // TODO
   stack<string> stack; // create a stack to temporarily store elements

   // push all elements from queue to stack
   while (!queue.empty())
   {
        stack.push(queue.front());     // stack follows LIFO, so push the first to the bottom of stack
        queue.pop();
   }

   // pop elements from stack and push back to queue
   while (!stack.empty())
   {
        queue.push(stack.top());       // by LIFO from queue, the bottom of stack will be the last to back in queue
        stack.pop();
   }
}

/* TODO PART:
 * Function: listQueue
 * Usage: listQueue(queue);
 * ------------------------
 * Lists the contents of the queue on the standard output stream.
 */

void listQueue(queue<string> & queue) {
   // TODO
   int size = queue.size();
   cout << "The queue contains: ";
   while (!queue.empty())
   {    
        for (int i = 0; i <= size; i++)
        {
            cout << queue.front()  << " ";
            queue.push(queue.front());
            queue.pop();
        }
   }
   cout << endl;
}

/* DO NOT modify this main() part*/

int main() {
    string str;
    queue<string> line;

    while(cin>>str){
        line.push(str);
    }
    listQueue(line);
    reverseQueue(line);
    listQueue(line);
    return 0;
}
