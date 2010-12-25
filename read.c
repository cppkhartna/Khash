/*read.c Khartikova*/

#include "shell.h"
#include "read.h"

int readme(TMemory *mem)
{
	int c = 0;
	int prev = 0;
	int k = 0;

	char s[DUMPLEN];

	int quotes = 0;
	int spaces = 0;
	
	while ((c = getchar()) != EOF && c != '\n')
	{
		if (c == '\"')
			quotes++;
		if (quotes > 0 && prev == '\"' && c == ' ')
			quotes = 0;
		if (spaces >= 0 && quotes == 0 && c == ' ')
			spaces++;
		if (c != ' ')
			spaces = 0;
		
		if (c != ' ' && c != '\"' && c != '(' && c != ')' && c != '|' && c != ';' && c != '&' && c != '>' && c != '<')
			s[k++] = c;
		if (spaces == 1)
			s[k++] = '\0';

		if (c == '(' || c == ')' || ((c == ';' || c == '|' || c =='&' || c == '>' || c == '<') && prev != c)) 
		{
			s[k++] = '\0';
			s[k++] = c;
			s[k++] ='\0';
		}

		if (c == '|' || c == '&' || c == '>')
			   if (prev == c)
			   {
			   		s[--k] = c;
					s[++k] = '\0';
					k++;
			   } 		


		if (k >= DUMPLEN - 5) 
		{
			s[k++] = '\0';
			dump(mem, s, k);
			k = 0;		
		}

		prev = c;
	}

	if (k > 0)
	{
		s[k++] = '\0';
		dump(mem, s, k);
		k = 0;
		return 0;
	} 
	else
		return -1;
}

void dump(TMemory *mem, char *s, int size)
{
	char *p;
	char *new;
	int i;
	

	if (mem != NULL && mem->beg != mem->end)
	{
		new = (char *)malloc(mem->end - mem->beg + size);
		p = new;
		for (i = 0; i < mem->end - mem->beg; i++)
		{
			*p++ = *(mem->beg)++;
		}

	}
	else 
	{
		new = (char *)malloc(size);
		p = new;
	}

	for (i = 0; i < size; i++)
	{
		*p++ = *s++;
	}

	if (mem != NULL)
			if (mem->beg != mem->end)
					free(mem->beg);
	
	mem->end = p;
	mem->beg = new;
}
