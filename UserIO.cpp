#include "UserIO.h"

void IO::getMasterPasswordHash(char* destination)
{
	char charIn;
	char pw[50];
	int i = 0;
	CSHA1 sha1;
	charIn = _getch();
	while(charIn != 13 && i < 50)
	{
		pw[i] = charIn;
		printf("*");
		++i;
		charIn = _getch();
	}
	sha1.Update((const unsigned char*)pw, strlen(pw));
	sha1.Final();
	sha1.GetHash((unsigned char*)destination);
	sha1.~CSHA1();
	return;
}
