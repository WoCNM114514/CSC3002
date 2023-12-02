/* P1:
 * File: WildcardMatch.cpp
 * -----------------------
 * This program tests the wildcardMatch method, which
 * matches a filename against a pattern containing the wildcard
 * characters * and ?.
 */

#include <iostream>
#include <string>
// #include "CSC3002OJActive/assignment4/WildcardMatch.h" //for OJ test
#include "WildcardMatch.h" // for local test
using namespace std;

/*
 * Method: wildcardMatch
 * Usage: if (wildcardMatch(filename, pattern)) . . .
 * --------------------------------------------------
 * This method checks to see whether filename matches the pattern,
 * which consists of three types of characters:
 *
 * 1. The character ?, which matches any single character
 * 2. The character *, which matches any string of characters
 * 3. Any other character, which matches only that character
 */

/* DO NOT modify the main() part */
/**
 * Checks if a given filename matches a given pattern.
 *
 * @param filename The name of the file to check.
 * @param pattern The pattern to match against the filename.
 * @return True if the filename matches the pattern, false otherwise.
 */
bool wildcardMatch(string filename, string pattern) 
{
    int filePos = 0, patPos = 0; // Initialize file and pattern positions
    int fileLen = filename.length(), patLen = pattern.length(); // Get the lengths of the filename and pattern
    int lastFilePos = -1, lastPatPos = -1; // Initialize the last matched file and pattern positions

    while (filePos < fileLen) { // While there are still characters in the filename
        if (patPos < patLen && (pattern[patPos] == '?' || filename[filePos] == pattern[patPos])) 
        { // If the pattern character is a wildcard or matches the current filename character
            filePos++; // Move to the next character in the filename
            patPos++; // Move to the next character in the pattern
        } else if (patPos < patLen && pattern[patPos] == '*') 
        { // If the pattern character is a wildcard
            lastFilePos = filePos; // Remember the current file position
            lastPatPos = patPos; // Remember the current pattern position
            patPos++; // Move to the next character in the pattern
        } else if (lastPatPos != -1) 
        { // If there was a previous wildcard in the pattern
            filePos = ++lastFilePos; // Move the file position to the last matched file position
            patPos = lastPatPos + 1; // Move the pattern position to the next character after the wildcard
        } else 
        {
            return false; // The pattern cannot be matched, return false
        }
    }

    while (patPos < patLen && pattern[patPos] == '*') 
    { // If there are still wildcards in the pattern, move to the next character
        patPos++;
    }

    return patPos == patLen; // If all characters in the pattern have been matched, return true
}

int main() {
   string in_pair, filename, pattern;
   bool matchResult;
   while(getline(cin,in_pair)){
      int sp = in_pair.find(' ');
      filename = in_pair.substr(0, sp);
      pattern = in_pair.substr(sp+1, in_pair.size());
      matchResult = wildcardMatch(filename, pattern);
      cout << boolalpha  << matchResult << endl;
    }
   return 0;
}

