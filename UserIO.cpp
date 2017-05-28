#include "UserIO.h"

UserIO::UserIO()
{
	memset(&masterPasswordHash, 0, 21);
}

User:IO::~UserIO(){}


void UserIO::genMasterPasswordHash()
{
	char* destination = getMasterPasswordHash();
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

void UserIO::genHash(char* destination)
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
	std::cout <<"-gen : Generate password to clipboard for pasting"	<< std::endl <<
				"-psw : Re-enter your Master Password." 			<< std::endl <<
				"-add : Add a new site's preferences."				<< std::endl <<
				"-del : Delete a site's preferences." 				<< std::endl <<
				"-mod : Modify an existing site's preferences."		<< std::endl << 
				"-hlp : Opens up this menu."						<< std::endl <<
				"-mnu : Opens up this menu."						<< std::endl <<
				"-ext : Exits the program."							<< std::endl << std::endl;
	return;
}

void UserIO::strToClipboard(char* str)
{
	OpenClipboard(0);
	EmptyClipboard();	
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, strlen(str));
	if (!hg)
	{
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), str, strlen(str) + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
	return;
}

int UserIO::getCommand()
{
	char input[5];
	fgets(input, 5, stdin);
	fflush(stdin);
	if(strcmp(input, "-gen")){return CMD_GEN;}
	else if(strcmp(input, "-add")){return CMD_ADD;}
	else if(strcmp(input, "-psw")){return CMD_PSW;}
	else if(strcmp(input, "-hlp")){return CMD_HLP;}
	else if(strcmp(input, "-mnu")){return CMD_MNU;}
	else if(strcmp(input, "-del")){return CMD_DEL;}
	else if(strcmp(input, "-mod")){return CMD_MOD;}
	else if(strcmp(input, "-ext")){return CMD_EXT;}
	return 0;
}






char* UserIO::getMasterPasswordHash()
{
	return masterPasswordHash;
}
