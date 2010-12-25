/*auxiliary.c Khartikova*/

#include "shell.h"

char *cut(const char *path)
{
	char *name;
	int i = 0;
	int pathlen = strlen(path);

	while (*path != '\0') 
		++path;
	while (*path != '/' && i <= pathlen) 
	{
		path--;
		i++;
	}

	if (*(path+1) != '\0')
	{
		++path;
		--i;
	}

	name = (char *)malloc(i);
	strcpy(name, path);
	return name;

}
