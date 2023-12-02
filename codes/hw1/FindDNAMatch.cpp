/* Q2: 
 * File: FindDNAMatch.cpp
 * ----------------------
 * This file solves the DNA matching exercise from the text.
 */
// header file for OJ system
// #include <iostream>
// #include <string>

// using namespace std;

#include <iostream>
#include <string>
//#include "CSC3002OJActive/assignment1/FindDNAMatch.h" //for OJ
#include "FindDNAMatch.h" //for local test
using namespace std;


/*
 * Function: findDNAMatch
 * Usage: int pos = findDNAMatch(s1, s2);
 *        int pos = findDNAMatch(s1, s2, start);
 * ---------------------------------------------
 * Returns the first index position at which strand s1 would bind to
 * the strand s2, or -1 if no such position exists.  If the start
 * parameter is supplied, the search begins at that index position.
 */

int findDNAMatch(string s1, string s2, int start) {
   // TODO
   string s1ForStrand = matchingStrand(s1);
   int lengthDiff = s2.length() - s1.length();
   if (s2.length()>=s1.length() && start<=lengthDiff) {
      for (int i=start; i<=lengthDiff; i++) {
         for (int j=0; j<s1.length(); j++) {
            if (s1ForStrand[j] != s2[i+j]) {
               break;
            }
            if (j==s1.length()-1) {
               return i;
            }
         }
      }
   }
   return -1;
}

/*
 * Function: matchingStrand
 * Usage: string match = matchingStrand(strand);
 * ---------------------------------------------
 * Returns a string in which each base has been replaced by its
 * counterpart base (C <-> G and A <-> T).  Any other characters
 * are replaced by an X.
 */

string matchingStrand(string strand) {
   // TODO
   string strandMatch = strand;
   for (int i=0; i<strand.length(); i++) {
      if (strandMatch[i] == 'A') {
         strandMatch[i] = 'T';
      }
      else if (strandMatch[i] == 'T') {
         strandMatch[i] = 'A';
      }
      else if (strandMatch[i] == 'G') {
         strandMatch[i] = 'C';
      }
      else if (strandMatch[i] == 'C') {
         strandMatch[i] = 'G';
      }
      else {
         strandMatch[i] = 'X';
      }
   }
   return strandMatch;
}

/*
 * Function: findAllMatches
 * Usage: findAllMatches(s1, s2);
 * ------------------------------
 * Finds all positions at which s1 can bind to s2.
 */

void findAllMatches(string s1, string s2) {
   // TODO
   bool ifMatch = false;
   int lengthDiff = s2.length() - s1.length();
   if (lengthDiff<0) {
      cout << s1 << " " << "has no matches in" << " " << s2 << endl; 
   }
   else {
      for (int i=0; i<=lengthDiff; i++) {
         int indexPos = findDNAMatch(s1, s2, i);
         if (indexPos != -1) {
            cout << s1 << " " << "matches" << " " << s2 << " " << "at position" << " " << indexPos << endl;
            ifMatch = true;
            i = indexPos;
         }
         else if (!ifMatch && i==lengthDiff) {
            cout << s1 << " " << "has no matches in" << " " << s2 << endl; 
         }
      }
   }
}
// DO NOT modify the main() function
/*
 * sample output:
 * input:  TTGCC TAACGGTACGTC
 * output: TTGCC matches TAACGGTACGTC at position 1
*/
int main(int argc, char* argv[]) {
    string s1, s2;
    cin >> s1 >> s2; 
    findAllMatches(s1, s2);
    return 0;
}
