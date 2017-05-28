#include "PW.h"


PW::PW()
{
	needsCap = 1;
	noSpecSymb = 0;
}

PW::PW(char* newHash, char needCapFlag, char noSpecSymbFlag)
{
	copyString(siteHash, newHash);
	needsCap = needCapFlag;
	noSpecSymb = noSpecSymbFlag;
}

PW::~PW(){}

//accessors
void PW::getSiteHash(char* destination)
{
	copyString(destination, siteHash);
}

char PW::getCapFlag() const
{
	return needsCap;
}
char PW::getSymbolsFlag() const
{
	return noSpecSymb;
}

//modifiers
void PW::setSiteHash(char* source)
{
	copyString(siteHash, source);
}
void PW::setCapFlag(char newFlag)
{
	needsCap = newFlag;
}
void PW::setSymbolFlag(char newFlag)
{
	noSpecSymb = newFlag;
}

void PW::copyString(char* s1, char* s2)
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
