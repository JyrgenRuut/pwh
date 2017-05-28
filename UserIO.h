#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <iostream>
#include <string.h>
#include "SHA1.h"

#ifndef USERIO_H
	#define USERIO_H

class UserIO
{
public:
	void getMasterPasswordHash(char*);
	void getHash(char*);
	void getMenu() const;
	void strToClipboard(char* str);
	
private:
	
	
};
#endif
