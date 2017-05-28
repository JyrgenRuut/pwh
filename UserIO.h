#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "SHA1.h"
#include "PW.h"

#define CMD_GEN 1
#define CMD_PSW 2
#define CMD_ADD 3
#define CMD_DEL 4
#define CMD_MOD 5
#define CMD_HLP 6
#define CMD_MNU 7
#define CMD_EXT 8


#ifndef USERIO_H
	#define USERIO_H

class UserIO
{
public:
	UserIO();
	~UserIO();
	
	void genMasterPasswordHash();
	void genHash(char*);
	void getMenu() const;
	void strToClipboard(char* str);
	void populatePrefsList(std::vector<PW>&);
	int findHash(char*, std::vector<PW>&);
	int getCommand();
	
	//Accessors
	char* getMasterPasswordHash();
private:
	char masterPasswordHash[HASH_STRING_SIZE];
};
#endif
