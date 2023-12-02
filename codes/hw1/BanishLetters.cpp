/*
 * File: BanishLetters.cpp
 * -----------------------
 * This program removes all instances of a set of letters from
 * an input file.
 */

#include <iostream>
#include <istream>
//#include "CSC3002OJActive/assignment1/lib.h"
using namespace std;
#include "D:\csc3002\assignment1_231008\lib.h"

int banishLetters() {
    // TODO
    string inputfile;
    string outputfile;
    string letterToBanish;

    // get the letters to banish(1st line) and ignore them while outputting
    cin >> letterToBanish;
    cin.ignore();

    while (getline(cin, inputfile))
    {
        outputfile = "";
        for (int i = 0; i < inputfile.length(); i++)
        {
            char c = inputfile[i];
            if ((letterToBanish.find(char(toupper(c))) > inputfile.length()) && (letterToBanish.find(char(tolower(c))) > inputfile.length()))
            {
                // put the unbanished letter to the outputfile
                outputfile += c;
            }
        }

        cout << outputfile << endl;
    }

    return 0;
}


/* DO NOT modify this main() part */
/*
 sample output:
 input: S
        this is a testing 1
        this is a testing 2
 output:
        thi i a teting 1
        thi i a teting 2
*/
int main(int argc, char* argv[]) {
    banishLetters();
    return 0;
}
