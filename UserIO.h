#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include "SHA1.h"
#include "PW.h"

//Define menu commands
#define CMD_GEN 1
#define CMD_PSW 2
#define CMD_ADD 3
#define CMD_DEL 4
#define CMD_MOD 5
#define CMD_HLP 6
#define CMD_MNU 7
#define CMD_EXT 8

//various other macros
#define GEN_TYPE_MASTER_PASSWORD 1		/*	used to tell genHash function where to store the resulting hash and	*/
#define GEN_TYPE_SITE 2					/*	whether to conceal what is written on the console or not.			*/
#define HASH_FIND_FAILED -1			//	Macro used for checking if a site existed in .siteprefs file.


#ifndef USERIO_H
	#define USERIO_H

class UserIO
{
private:
	char masterPasswordHash[HASH_STRING_SIZE];
	char siteHash[HASH_STRING_SIZE];
	
	int findHash(std::vector<PW>&);
	void strToClipboard(char* str);
	void decapLastLetter(char*);
	void getPrefs(char* capflag, char* maxlen);
	
public:
	UserIO();
	~UserIO();
	
	int getCommand();
	void genHash(int TYPE);
	void printMenu() const;
	void genPassword(std::vector<PW>&);
	void populatePrefsList(std::vector<PW>&);
	void deletePrefsListEntry(std::vector<PW>&);
	void savePrefs(std::vector<PW>&);
	void modifyPref(std::vector<PW>&);
	void addPref(std::vector<PW>&);
	
};
#endif
