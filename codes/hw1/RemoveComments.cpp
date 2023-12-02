/*
 * File: RemoveComments.cpp
 * ------------------------
 * Prints out a file after removing comments.
 */
// header file for local test
#include <iostream>
#include <iomanip>
//#include "CSC3002OJActive/assignment1/RemoveComments.h" //for OJ
#include "RemoveComments.h" //for local test
using namespace std;


/*
 * Function: removeComments
 * Usage: removeComments(is, os);
 * ------------------------------
 * Copies characters from the input stream is to the output stream os,
 * removing any comments it finds.  This program eliminates both the
 * /* and // comment forms but does not check to see if those characters
 * are embedded within strings.
 */

void removeComments(istream & is, ostream & os) 
{
   //TODO
   string fileline;
   bool inBlock = false;
   
   while (getline(is, fileline))
   {
       string writeIn;
       for (int i=0; i < fileline.length(); i++)
       {
           if (!inBlock && i+1 < fileline.length() && fileline[i]=='/' && fileline[i+1]=='*')
           {
               inBlock = true;
               i++;
           }
           else if (inBlock && i+1 < fileline.length() && fileline[i]=='*' && fileline[i+1]=='/')
           {
               inBlock = false;
               i++;
           }
           else if (!inBlock && i+1 < fileline.length() && fileline[i]=='/' && fileline[i+1]=='/')
           {
               break;
           }
           else if (!inBlock)
           {
               writeIn += fileline[i];
           }
       }
       cout << writeIn << endl;
   }
}


void TestRemoveComments(){
    removeComments(cin, cout);
}

// DO NOT modify the main() function
/*
 * sample output format:
 * input:  test file // this is a comment
           test file /* this is also a comment*/
/* output: test file
           test file
 */
int main(int argc, char* argv[]) {
    TestRemoveComments();
    return 0;
}

