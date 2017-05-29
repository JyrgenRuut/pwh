#include "UserIO.h"


UserIO::UserIO()
{
	memset(masterPasswordHash, 0, HASH_STRING_SIZE);
	memset(siteHash, 0, HASH_STRING_SIZE);
}

UserIO::~UserIO(){}

void UserIO::genHash(int TYPE)
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

void UserIO::printMenu() const
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

void UserIO::populatePrefsList(std::vector<PW>& list)
{
	//char byteIn;
	int listCounter = 0;
	char tempHash[HASH_STRING_SIZE];
	char capFlag;
	char maxLength;
	
	FILE* fi = fopen(".siteprefs", "r");
	if(fi == NULL)
	{
		printf("\nSite preferences file missing, creating a new one.\n");
		FILE* fgen = fopen(".siteprefs", "w");
		fclose(fgen);
		return;
	}
	
	while(1)
	{
		fseek(fi, 1, SEEK_CUR);		//Checks to see if there is any more data expected
		if(feof(fi)) {break;}
		fseek(fi, -1, SEEK_CUR);
	
		fread(tempHash, 1, HASH_STRING_SIZE, fi);
		capFlag = fgetc(fi);
		if(capFlag == EOF) {break;}
		maxLength = fgetc(fi);
		if(maxLength == EOF) {break;}
		
		PW element(tempHash, capFlag, maxLength);
		list.push_back(element);
		++listCounter;
	}
	fclose(fi);
	return;
	
}

int UserIO::findHash(std::vector<PW>& list)
{
	for(int i = list.size() - 1; i >= 0; --i)
	{
		if(strcmp(siteHash, list[i].getSiteHash()) == 0) {return i;}
	}
	return HASH_FIND_FAILED;
}

void UserIO::genPassword(std::vector<PW>& list)
{
	int listPointer = findHash(list);
	char password[(PASSWORD_HARD_MAX_LENGTH + 1)];
	memset(password, 0, PASSWORD_HARD_MAX_LENGTH + 1);
	CSHA1 sha1;
	sha1.Update((const unsigned char*)masterPasswordHash, HASH_STRING_SIZE);
	sha1.Update((const unsigned char*)siteHash, HASH_STRING_SIZE);
	sha1.Final();
	sha1.ReportHash(password, CSHA1::REPORT_HEX_SHORT);
	password[PASSWORD_HARD_MAX_LENGTH] = '\0';
	sha1.~CSHA1();
	
	if(listPointer == HASH_FIND_FAILED) {strToClipboard(password);}
	else
	{
		char needsCap = list[listPointer].getCapFlag();
		char maxLength = list[listPointer].getMaxLength();
		if(needsCap > 0) {decapLastLetter(password);}
		if((unsigned char)maxLength < PASSWORD_HARD_MAX_LENGTH) {memset((password + maxLength), 0, (PASSWORD_HARD_MAX_LENGTH - maxLength));}
		printf("%s\n", password);
		strToClipboard(password);
	}
	std::cout << "Password successfully added to your clipboard!" << std::endl;
	
	return;
}

void UserIO::decapLastLetter(char* str)
{
	for(int i = (strlen(str) - 1); i >= 0; --i)
	{
		if(*(str + i) < 61) {*(str + i) += 0x20; break;}
	}
	return;
}

void UserIO::deletePrefsListEntry(std::vector<PW>& list)
{
	int toDelete = findHash(list);
	if(toDelete != HASH_FIND_FAILED) {list.erase(list.begin() + toDelete);}
	return;
}

void UserIO::savePrefs(std::vector<PW>& list)
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

void UserIO::modifyPref(std::vector<PW>& list)
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

void UserIO::addPref(std::vector<PW>& list)
{
	char capflag, maxlen;
	getPrefs(&capflag, &maxlen);
	PW newEntry(siteHash, capflag, maxlen);
	list.push_back(newEntry);
	
	return;
}

void UserIO::getPrefs(char* capflag, char* maxlen) 
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

