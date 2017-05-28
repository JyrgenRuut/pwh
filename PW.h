#include <stdio.h>
#include <string.h>
#include <iostream>

#define HASH_STRING_SIZE 21

#ifndef PW_H
	#define PW_H

class PW 
{
private:
	char siteHash[HASH_STRING_SIZE];
	char needsCap;
	char noSpecSymb;
	char maxLength;
	void copyString(char*, char*);		//@param1: destination; @param2: source;
public:
	//(de)constructors
	PW();
	~PW();
	PW(char*, char, char);
	//accessors
	char* getSiteHash();
	char getCapFlag() const;
	char getSymbolsFlag() const;
	//modifiers
	void setSiteHash(char*);
	void setCapFlag(char);
	void setSymbolFlag(char);
};
#endif
