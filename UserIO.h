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
	
	int findHash(std::vector<PW>&);		//@param: list of PW objects to look through
	void strToClipboard(char*);			//@param: pointer to string to be sent to the clipboard
	void decapLastLetter(char*);		//@param: pointer to string from where the last letter will be de-capitalized
	void getPrefs(char*, char*);		//@param1: pointer to where to save the entered "capital letter flag"; @param2: pointer to where to save the entered maximum password length
	
public:
	//constructor and deconstructor
	UserIO();
	~UserIO();
	
	int getCommand();
	void genHash(int TYPE);							//@param TYPE: either macro GEN_TYPE_MASTER_PASSWORD or GEN_TYPE_SITE
	void printMenu() const;	
	void genPassword(std::vector<PW>&);				//@param: list where to look for a saved site hash
	void populatePrefsList(std::vector<PW>&);		//@param: list where to save all the preferences in .siteprefs file
	void deletePrefsListEntry(std::vector<PW>&);	//@param: list where to look for a saved site hash
	void savePrefs(std::vector<PW>&);				//@param: list where to save the new site hash and preferences
	void modifyPref(std::vector<PW>&);				//@param: list where to look for the site preferences to modify
	void addPref(std::vector<PW>&);					//@param: list where to save a new site hash and preferences
	
};
#endif
