#include <stdio.h>
#include <iostream>
#include <windows.h>
#include "SHA1.h"
#include <conio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "PW.h"


#define CMD_GEN 1
#define CMD_PSW 2
#define CMD_ADD 3
#define CMD_DEL 4
#define CMD_MOD 5
#define CMD_HLP 6
#define CMD_MNU 7
#define CMD_EXT 8

#define GEN_TYPE_MASTER_PASSWORD 1
#define GEN_TYPE_SITE 2


#ifndef USERIO_H
	#define USERIO_H

class UserIO
{
private:
	char masterPasswordHash[HASH_STRING_SIZE];
	char siteHash[HASH_STRING_SIZE];
	int findHash(std::vector<PW>&);
	
	void strToClipboard(char* str);
	void capLastLetter(char*);
	
public:
	UserIO();
	~UserIO();
	
	void genHash(int TYPE);
	void genPassword(std::vector<PW>&);
	void getMenu() const;
	void populatePrefsList(std::vector<PW>&);
	void deletePrefsListEntry(std::vector<PW>&);
	void savePrefs(std::vector<PW>&);
	int getCommand();
	
};
#endif
