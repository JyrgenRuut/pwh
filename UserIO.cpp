#include "UserIO.h"

UserIO::UserIO()	//constructor
{
	memset(masterPasswordHash, 0, HASH_STRING_SIZE);
	memset(siteHash, 0, HASH_STRING_SIZE);
}

UserIO::~UserIO(){}		//deconstructor

void UserIO::genHash(int TYPE)		//asks for password/site name, generates SHA1 hash into masterPasswordHash/siteHash, depending on whether @param is GEN_TYPE_MASTER_PASSWORD or GEN_TYPE_SITE
{
	char* destination;
	if(TYPE == GEN_TYPE_MASTER_PASSWORD) {printf("Enter your Master Password: "); destination = masterPasswordHash; memset(masterPasswordHash, 0, HASH_STRING_SIZE);}
	else if(TYPE == GEN_TYPE_SITE) {printf("Enter site name: "); destination = siteHash; memset(siteHash, 0, HASH_STRING_SIZE);}
	char charIn;
	char pw[51] = { 0 };
	int i = 0;
	CSHA1 sha1;
	
	charIn = _getch();
	while(charIn != 13 && i < 50)
	{
		pw[i] = charIn;
		if(TYPE == GEN_TYPE_MASTER_PASSWORD) {putchar('*');}
		else {putchar(charIn);}
		++i;
		charIn = _getch();
	}
	putchar('\n');
	
	if(TYPE == GEN_TYPE_MASTER_PASSWORD) {if(i == 0){printf("You decided to not enter a master password, this is\nconsidered unsafe! It is highly recommended\nthat you enter -psw and re-enter your\nMaster Password!\n");}}
	sha1.Update((const unsigned char*)pw, strlen(pw));
	sha1.Final();
	sha1.GetHash((unsigned char*)destination);
	sha1.~CSHA1();
	
	return;
}

void UserIO::printMenu() const		//Prints out the menu choices
{
	std::cout << std::endl <<
				"-gen : Generate password to clipboard for pasting"	<< std::endl <<
				"-psw : Re-enter your Master Password." 			<< std::endl <<
				"-add : Add a new site's preferences."				<< std::endl <<
				"-del : Delete a site's preferences." 				<< std::endl <<
				"-mod : Modify an existing site's preferences."		<< std::endl << 
				"-hlp : Opens up this menu."						<< std::endl <<
				"-mnu : Opens up this menu."						<< std::endl <<
				"-ext : Exits the program."							<< std::endl << std::endl;
	return;
}

void UserIO::strToClipboard(char* str)		//copies the string pointed to by @param into system clipboard
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

int UserIO::getCommand()		//Receives input from user to determine what the user wishes to do; returns the command macro. 
{
	char input[5];
	fgets(input, 5, stdin);
	fflush(stdin);
	if(!strcmp(input, "-gen")){return CMD_GEN;}
	else if(!strcmp(input, "-add")){return CMD_ADD;}
	else if(!strcmp(input, "-psw")){return CMD_PSW;}
	else if(!strcmp(input, "-hlp")){return CMD_HLP;}
	else if(!strcmp(input, "-mnu")){return CMD_MNU;}
	else if(!strcmp(input, "-del")){return CMD_DEL;}
	else if(!strcmp(input, "-mod")){return CMD_MOD;}
	else if(!strcmp(input, "-ext")){return CMD_EXT;}
	return 0;
}

void UserIO::populatePrefsList(std::vector<PW>& list)		//loads stored site preferences from .siteprefs file
{
	//char byteIn;
	int listCounter = 0;
	char tempHash[HASH_STRING_SIZE];
	char capFlag;
	char maxLength;
	
	FILE* fi = fopen(".siteprefs", "r");	//open and/or check the .siteprefs file
	if(fi == NULL) {return;}
	
	while(1)
	{
		fseek(fi, 1, SEEK_CUR);		//Checks to see if there is any more data expected
		if(feof(fi)) {break;}
		fseek(fi, -1, SEEK_CUR);
	
		fread(tempHash, 1, HASH_STRING_SIZE, fi);		//reads in the hash, capital letter flag and max password length in repsective order
		capFlag = fgetc(fi);
		if(capFlag == EOF) {break;}
		maxLength = fgetc(fi);
		if(maxLength == EOF) {break;}
		
		PW element(tempHash, capFlag, maxLength);		//adds the new element to the list of preferences for later use
		list.push_back(element);
		++listCounter;
	}
	fclose(fi);
	return;
	
}

int UserIO::findHash(std::vector<PW>& list)		//checks to see if a site has preferences saved previously; returns the position in the list or HASH_FIND_FAILED macro if the site was not found.
{
	for(int i = list.size() - 1; i >= 0; --i)
	{
		if(strcmp(siteHash, list[i].getSiteHash()) == 0) {return i;}
	}
	return HASH_FIND_FAILED;
}

void UserIO::genPassword(std::vector<PW>& list)		//generates the final password onto the clipboard based on master password hash and site hash, hashing them together.
{
	int listPointer = findHash(list);				//see if the site entered has preferences saved
	char password[(PASSWORD_HARD_MAX_LENGTH + 1)];
	memset(password, 0, PASSWORD_HARD_MAX_LENGTH + 1);
	CSHA1 sha1;		//start of hashing
	sha1.Update((const unsigned char*)masterPasswordHash, HASH_STRING_SIZE);		
	sha1.Update((const unsigned char*)siteHash, HASH_STRING_SIZE);
	sha1.Final();
	sha1.ReportHash(password, CSHA1::REPORT_HEX_SHORT);
	password[PASSWORD_HARD_MAX_LENGTH] = '\0';
	sha1.~CSHA1();		//end of hashing
	
	if(listPointer == HASH_FIND_FAILED) {strToClipboard(password);}		//if site was not found in the preferences list, default to just copying the resulting string to clipboard
	else 		//else use the site preferences to determine is and what the restrictions on the password are. 
	{
		char maxLength = list[listPointer].getMaxLength();
		if((unsigned char)maxLength < PASSWORD_HARD_MAX_LENGTH) {memset((password + maxLength), 0, (PASSWORD_HARD_MAX_LENGTH - maxLength));}
		if(list[listPointer].getCapFlag()) {decapLastLetter(password);}
		strToClipboard(password);
	}
	std::cout << "Password successfully added to your clipboard!" << std::endl;
	
	return;
}

void UserIO::decapLastLetter(char* str)		//decapitalizes the lastmost uppercase letter (all letters in the SHA1 digest are upper-case by default)
{
	for(int i = (strlen(str) - 1); i >= 0; --i)
	{
		if(*(str + i) >= 'A') {*(str + i) = *(str + i) + 0x20; break;}
	}
	return;
}

void UserIO::deletePrefsListEntry(std::vector<PW>& list)		//erases a site preferences from list of preferences if the site has previously been added
{
	int toDelete = findHash(list);
	if(toDelete != HASH_FIND_FAILED) {list.erase(list.begin() + toDelete);}
	return;
}

void UserIO::savePrefs(std::vector<PW>& list)		//stores the list of preferences in .siteprefs file
{
	FILE* fo = fopen(".siteprefs", "w");
	for(int i = (list.size() - 1); i >= 0; --i)
	{
		fwrite(list[i].getSiteHash(), 1, HASH_STRING_SIZE, fo);
		fputc(list[i].getCapFlag(), fo);
		fputc(list[i].getMaxLength(), fo);
	}
	fclose(fo);
	return;
}

void UserIO::modifyPref(std::vector<PW>& list)		//modifies an existing site's preferences or adds a new one if the site entered was new
{
	char newMaxLen, newCapFlag;
	getPrefs(&newCapFlag, &newMaxLen);
	int modify = findHash(list);
	
	if(modify == HASH_FIND_FAILED)
	{
		PW newEntry(siteHash, newCapFlag, newMaxLen);
		list.push_back(newEntry);
	}
	else
	{
		list[modify].setCapFlag(newCapFlag);
		list[modify].setMaxLength(newMaxLen);
	}
	
	return;
}

void UserIO::addPref(std::vector<PW>& list)		//adds a new site hash and preferences to the list of preferences
{
	char capflag, maxlen;
	int p;
	p = findHash(list);
	if(p != HASH_FIND_FAILED)
	{
		modifyPref(list);
	}
	else
	{
		getPrefs(&capflag, &maxlen); 
		PW newEntry(siteHash, capflag, maxlen);
		list.push_back(newEntry);
	}
	
	return;
}

void UserIO::getPrefs(char* capflag, char* maxlen) 		//asks user for a site's preferences 
{
	int temp;
	
	std::cout << std::endl << "Is a non-capitalized letter nessecary? 0 = no, 1 = yes	:	";
	std::cin >> temp;
	*capflag = (char)temp;
	fflush(stdin);
	std::cout << std::endl << 	"If there is a maximum length for the password, set it here."			<< std::endl << 
								"If the max length is longer than 40 or length is not limited, enter 0"	<< std::endl <<
								"Maximum password length: ";
	std::cin >> temp;
	fflush(stdin);
	
	if(temp == 0) {*maxlen = PASSWORD_HARD_MAX_LENGTH;}
	else {*maxlen = (char)temp;}
	
	return;
}

