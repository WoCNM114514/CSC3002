/* P3:
 * File: p3beffer.cpp
 * -------------------
 * This file implements EditorBuffer
 */
#include <cctype>
#include <iostream>
//#include "CSC3002OJActive/assignment4/buffer.h"
//#include "CSC3002OJActive/assignment4/SimpleTextEditor.h"
#include "buffer.h"
#include "SimpleTextEditor.h"
using namespace std;

/*
 * Implementation notes: EditorBuffer constructor
 * ----------------------------------------------
 * This function initializes an empty editor buffer, represented
 * as a doubly linked list.  In this implementation, the ends of
 * the linked list are joined to form a ring, with the dummy cell
 * at both the beginning and the end.  This representation makes
 * it possible to implement the moveCursorToEnd method in constant
 * time, and reduces the number of special cases in the code.
 */

EditorBuffer::EditorBuffer() {
   start = cursor = new Cell;
   start->next = start;
   start->prev = start;
}

/* TODO PART:
 * Implementation notes: EditorBuffer destructor
 * ---------------------------------------------
 * The destructor must delete every cell in the buffer.  Note
 * that the loop structure is not exactly the standard idiom for
 * processing every cell within a linked list, because it is not
 * legal to delete a cell and later look at its next field.
 */

// Destructor for the EditorBuffer class
EditorBuffer::~EditorBuffer() 
{
    // TODO: Delete every cell in the buffer
    Cell *temp = start->next;
    while (temp != start) 
    {
        Cell *next = temp->next;
        delete temp;
        temp = next;
    }
    delete temp;
}

/* TODO PART:
 * Implementation notes: cursor movement
 * -------------------------------------
 * In a doubly linked list, each of these operations runs in
 * constant time.
 */


void EditorBuffer::moveCursorForward() 
{
    // TODO
    if (cursor->next != start)
    {
        cursor = cursor->next;
    }
}


void EditorBuffer::moveCursorBackward() 
{
    // TODO
    if (cursor != start)
    {
        cursor = cursor->prev;
    }
}


void EditorBuffer::moveCursorToStart() 
{
    // TODO
    if (cursor != start->next)
    {
        cursor = start;
    }
}


void EditorBuffer::moveCursorToEnd() 
{
    // TODO
    if (cursor != start->prev)
    {
        cursor = start->prev;
    }
}

/* TODO PART:
 * Implementation notes: insertCharacter, deleteCharacter
 * ------------------------------------------------------
 * This code is much like that used for the traditional linked
 * list except that more pointers need to be updated.
 */


void EditorBuffer::insertCharacter(char ch) 
{
    // TODO
    Cell *temp = new Cell;
    temp->ch = ch;
    // cursor' next point at new cell
    temp->next = cursor->next;
    // new cell point back at cursor
    temp->prev = cursor;
    // cursor's next point at new cell
    cursor->next->prev = temp;
    // cursor point at new cell
    cursor->next = temp;   
    cursor = temp;
}

// Delete the character at the current cursor position
void EditorBuffer::deleteCharacter() 
{
    //TODO
    // if the cursor is at the end of buffer, delete will not work
    if (cursor->next != start)
    {
        Cell *temp = cursor->next;
        // cursor's next points at next's next
        cursor->next = temp->next;
        temp->next->prev = cursor;
        delete temp;
    }
}

/* TODO PART:
 * Implementation notes: getText and getCursor
 * -------------------------------------------
 * The getText method uses the standard linked-list pattern to loop
 * through the cells in the linked list.  The getCursor method counts
 * the characters in the list until it reaches the cursor.
 */

// Get the text in the buffer
string EditorBuffer::getText() const 
{
    // TODO
    string str = "";
    Cell *temp = start->next;
    temp = start->next;
    while (temp != start)
    {
        str += (temp->ch);
        temp = temp->next;
    }
    return str;
}

// Get the position of the cursor
int EditorBuffer::getCursor() const 
{
    // TODO
    Cell *temp = start;
    int count = 0;
    while(temp != cursor)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

/*
 * Function: executeCommand
 * Usage: executeCommand(buffer, line);
 * ------------------------------------
 * Executes the command specified by line on the editor buffer.
 */
void executeCommand(EditorBuffer & buffer, string line) {
   switch (toupper(line[0])) {
    case 'I': for (int i = 1; i < line.length(); i++) {
                 buffer.insertCharacter(line[i]);
              }
              displayBuffer(buffer);
              break;
    case 'D': buffer.deleteCharacter(); displayBuffer(buffer); break;
    case 'F': buffer.moveCursorForward(); displayBuffer(buffer); break;
    case 'B': buffer.moveCursorBackward(); displayBuffer(buffer); break;
    case 'J': buffer.moveCursorToStart(); displayBuffer(buffer); break;
    case 'E': buffer.moveCursorToEnd(); displayBuffer(buffer); break;
    case 'H': printHelpText(); break;
    case 'Q': exit(0);
    default:  cout << "Illegal command" << endl; break;
   }
}

/*
 * Function: displayBuffer
 * Usage: displayBuffer(buffer);
 * -----------------------------
 * Displays the state of the buffer including the position of the cursor.
 */

void displayBuffer(EditorBuffer & buffer) {
   string str = buffer.getText();
   for (int i = 0; i < str.length(); i++) {
      cout << " " << str[i];
   }
   cout << endl;
   cout << string(2 * buffer.getCursor(), ' ') << "^" << endl;
}

/*
 * Function: printHelpText
 * Usage: printHelpText();
 * -----------------------
 * Displays a message showing the legal commands.
 */

void printHelpText() {
   cout << "Editor commands:" << endl;
   cout << "  Iabc  Inserts the characters abc at the cursor position" << endl;
   cout << "  F     Moves the cursor forward one character" << endl;
   cout << "  B     Moves the cursor backward one character" << endl;
   cout << "  D     Deletes the character after the cursor" << endl;
   cout << "  J     Jumps to the beginning of the buffer" << endl;
   cout << "  E     Jumps to the end of the buffer" << endl;
   cout << "  H     Prints this message" << endl;
   cout << "  Q     Exits from the editor program" << endl;
}

/* DO NOT modify the main() part */
int main(){
    string cmd;
    EditorBuffer buffer;
    while(getline(cin,cmd)){
        executeCommand(buffer, cmd);
    }        
    return 0;
}