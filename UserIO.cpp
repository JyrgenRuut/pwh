#include "UserIO.h"

void UserIO::getMasterPasswordHash(char* destination)
{
	char charIn;
	char pw[51];
	int i = 0;
	CSHA1 sha1;
	printf("Enter your Master Password: ");
	charIn = _getch();
	while(charIn != 13 && i < 50)
	{
		pw[i] = charIn;
		putchar('*');
		++i;
		charIn = _getch();
	}
	pw[51] = '\0';
	putchar('\n');
	if(i == 0){printf("You decided to not enter a master password, this is\nconsidered unsafe! It is highly recommended\nthat you enter -pw and re-enter your\nMaster Password!\n");}
	sha1.Update((const unsigned char*)pw, strlen(pw));
	sha1.Final();
	sha1.GetHash((unsigned char*)destination);
	sha1.~CSHA1();
	return;
}

void UserIO::getHash(char* destination)
{
	char charIn;
	char str[51];
	int i = 0;
	CSHA1 sha1;
	printf("Enter the site name: ");
	charIn = _getch();
	while(charIn != 13 && i < 50)
	{
		str[i] = charIn;
		putchar('*');
		++i;
		charIn = _getch();
	}
	str[51] = '\0';
	putchar('\n');
	sha1.Update((const unsigned char*)str, strlen(str));
	sha1.Final();
	sha1.GetHash((unsigned char*)destination);
	sha1.~CSHA1();
	return;
}

void UserIO::getMenu() const
{
	std::cout <<"-gen : generate password to clipboard for pasting"	<< std::endl <<
				"-psw : re-enter your Master Password." 			<< std::endl <<
				"-add : add a new site's preferences."				<< std::endl <<
				"-del : delete a site's preferences." 				<< std::endl <<
				"-mod : modify an existing site's preferences."		<< std::endl << 
				"-hlp : Opens up this menu."						<< std::endl <<
				"-mnu : Opens up this menu."						<< std::endl << std::endl;
}


