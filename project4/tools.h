#ifndef TOOLS_H
#define TOOLS_H

#include "hashtable.h"
#include <stdio.h>

// for reading input from the user
void readString(char * inputStr, char * prompt);
int readInt(char * prompt);
float readFloat(char * prompt);
// functions for menu commands
void displayMenu();
char readCommand();
void exeCommand(const char reply, hashTable& aTable);
void getStock(data& stock);
// extra functions
void pause();
#endif