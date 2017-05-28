#include <stdio.h>
#include <iostream>

#ifndef PW_H
	#define PW_H

class PW 
{
private:
	char siteHash[21];
	char needsCap;
	char noSpecSymb;
	void copyString(char*, char*);		//@param1: destination; @param2: source;
public:
	//(de)constructors
	PW();
	~PW();
	PW(char*, char, char);
	//accessors
	void getSiteHash(char*);
	char getCapFlag() const;
	char getSymbolsFlag() const;
	//modifiers
	void setSiteHash(char*);
	void setCapFlag(char);
	void setSymbolFlag(char);
};
#endif
