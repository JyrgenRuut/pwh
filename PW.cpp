#include "PW.h"


PW::PW()
{
	memset(siteHash, 0, HASH_STRING_SIZE);
	needsCap = 1;
	maxLength = PASSWORD_HARD_MAX_LENGTH;
}

PW::PW(char* newHash, char needCapFlag, char newMaxLength)
{
	copyString(siteHash, newHash);
	needsCap = needCapFlag;
	maxLength = newMaxLength;
}

PW::~PW(){}

//accessors
char* PW::getSiteHash()
{
	return siteHash;
}

char PW::getCapFlag() const
{
	return needsCap;
}

char PW::getMaxLength() const
{
	return maxLength;
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

void PW::setMaxLength(char newMaxLength)
{
	maxLength = newMaxLength;
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
	*(s1 + HASH_STRING_SIZE) = '\0';
}
