#include "PW.h"

PW::copyString(char* s1, char* s2)
{
	bool sourceStringFinished = false;
	for(int i = 0; i <= 20; ++i)
	{
		if(*(s2 + i) == '\0' && sourceStringFinished == false) {sourceStringFinished = true;}
		if(!sourceStringFinished)
		{
			*(s1 + i) = *(s2 + i);
		}
		else
		{
			*(s1 + i) = '\0';
		}
	}
	*(s1 + 21) = '\0';
}

PW::PW()
{
	siteHash = "";
	needsCap = 1;
	noSpecSymb = 0;
}

PW::PW(char* newHash, char needCapFlag, char noSpecSymbFlag)
{
	copyString(&siteHash, newHash);
	needsCap = needCapFlag;
	noSpecSymb = noSpecSymbFlag
}

PW::~PW(){}

//accessors
void getSiteHash(char* destination) const
{
	copyString(destination, &siteHash);
}

char getCapFlag() const
{
	return needsCap;
}
char getSymbolsFlag() const
{
	return noSpecSymb;
}

//modifiers
void setSiteHash(char* source)
{
	copyString(&siteHash, source);
}
void setCapFlag(char newFlag)
{
	needsCap = newFlag;
}
void setSymbolFlag(char newFlag)
{
	noSpecSymb = newFlag;
}
