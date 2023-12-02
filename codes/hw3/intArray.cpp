/* P2:
 * File: intArray.cpp
 * ------------------
 * This file inplements the intarray.h interface.
 */
#include <iostream>
// #include "CSC3002OJActive/assignment3/intArray.h"  // For OJ test
#include "intArray.h"  // For local test

using namespace std;
/*
 * Implementation notes: IntArray constructor and destructor
 * ---------------------------------------------------------
 * The constructor allocates an array to hold the values and initializes
 * each element to 0; the constructor must also store the effective size
 * in the variable nElements.  The destructor must take responsibility
 * for freeing the dynamic array.
 */

int ret = 0;
IntArray::IntArray(int n) {
   // TODO
   // allocate dynamic memory for the array
   array = new int[n];
   // initialize each element to 0
   for (int i = 0; i < n; i++)
   {  
      *(array + i) = 0;
   }
   // store the number of elements
   nElements = n;
}

IntArray::~IntArray() {
   // TODO
   // deallocate the dynamically allocated array
   delete [] array;
}

/*
 * Implementation notes: size, get, and set
 * ----------------------------------------
 * Given the data structure, each of these methods is straightforward.
 */

int IntArray::size() {
   // TODO
   return nElements;
}

int IntArray::get(int index) {
   // TODO
   if (index < nElements && index >= 0)
   {
      return array[index];
   }
   else
   {
      cout << "ERROR: Index range out of bounds!" << endl;
      return -1;
   }
}

void IntArray::put(int index, int value) {
   // TODO
   if (index < nElements && index >= 0)
   {
      array[index] = value;
   }
   else
   {
      cout << "ERROR: Index range out of bounds!" << endl;
   }
}

/*
 * Implementation notes: operator
 * ---------------------------------
 * The selction operator is identical to get except for the fact that it
 * returns its result by reference.
 */

// overloaded version of operator[]
int & IntArray::operator[](int index) {
   // TODO
   // check if valid 
   if (index < nElements && index >= 0)
   {
      return array[index];
   }
   else
   {
      cout << "ERROR: Index range out of bounds!" << endl;
      return ret;
   }
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * These methods make it possible to pass a IntArray by value or
 * assign one IntArray to another.
 */

// constructor
IntArray::IntArray(const IntArray & src) {
   // TODO
   // create a new object 
   // 从无到有靠复制创建一个新对象
   if (this != &src)
   {  // 如果在此处delete []会直接干掉刚生成的对象
      deepCopy(src);
   }
}

// overloader
IntArray & IntArray::operator=(const IntArray & src) {
   // TODO  
   // assign value of src to current object
   // 重载函数, 把值赋予已经存在(创建)的对象, 可以靠重载来实现改变源的同时也改变靠复制源而创造的对象
   if (this != &src)
   {
      delete[] array;
      deepCopy(src);
   }
   return *this;
}

/*
 * Implementation notes: deepCopy
 * ------------------------------
 * Copies the data from the src parameter into the current object.
 * All dynamic memory is reallocated to create a "deep copy" in
 * which the current object and the source object are independent.
 */

void IntArray::deepCopy(const IntArray & src) {
  // TODO
  // allocate new memory for the array in the current object
  array = new int[src.nElements];
  // copy elements from source object
  for (int i = 0; i < src.nElements; i++)
  {      
      array[i] = src.array[i];
  }
  // update number of elements in current object
  nElements = src.nElements;
}

/* DO NOT modify this part*/
int main() {
   int id;
   int size_num;
   cin>>id;
   cin>>size_num;

   if(id==1){
      IntArray array(size_num);
      cout << "array.size(): " << integerToString(array.size()) << '\n' << endl;
      for (int i = 0; i < size_num; i++) {
         cout << "array.get(): " << integerToString(array.get(i)) << endl;
         cout << "array.put(" << i << ", " << i << ");" << endl;
         array.put(i, i);
         cout << "array.get(): " << integerToString(array.get(i))<< '\n' << endl;
      }
      array.get(-1);
      array.put(size_num+1, size_num+1);
   }
   if(id == 2){
      IntArray array(size_num);
      cout << "array.size(): " << integerToString(array.size()) << '\n' << endl;
      for (int i = 0; i < size_num; i++) {
         cout << "array.get(): " << integerToString(array.get(i)) << endl;
         cout << "array[" << i << "] = " << i << ";" << endl;
         array[i] = i;
         cout << "array.get(): " << integerToString(array.get(i))<< '\n' << endl;
      }
   }
   if(id == 3){
      IntArray v1(size_num);
      cout << "v1.size(): " << integerToString(v1.size()) << '\n' << endl;
      for (int i = 0; i < size_num; i++) {
         cout << "v1.get(): " << integerToString(v1.get(i)) << endl;
         cout << "v1[" << i << "] = " << i << ";" << endl;
         v1[i] = i;
         cout << "v1.get(): " << integerToString(v1.get(i))<< '\n' << endl;
      }
      IntArray v2;
      v2 = v1;
      cout << "v2.size(): " << integerToString(v2.size()) << '\n' << endl;
      for (int i = 0; i < v2.size(); i++) {
         cout << "v2.get(): " << integerToString(v2.get(i)) << endl;
      }
      IntArray v3;
      v3 = IntArray(v1);
      cout << '\n' << "v3.size(): " << integerToString(v3.size()) << '\n' << endl;
      for (int i = 0; i < v3.size(); i++) {
         cout << "v3.get(): " << integerToString(v3.get(i)) << endl;
      }
   }
   return 0;
}

