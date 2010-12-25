/*main.c Khartikova*/

#include "shell.h"

int main()
{
	TMemory *mem = NULL;

	for (;;) 
	{
		int t;

		/*save environment*/
		t = open("dev/tty", O_RDWR, 0);
		dup2(t, 0);
		dup2(t, 1);

		/*greeting*/
		printf("khash:%s[", getenv("USER"));
		if (strcmp(getenv("PWD"), getenv("HOME")) == 0) 
			printf("~]");
		else 
			printf("%s]", cut(getenv("PWD")));	
		if (getuid()) 
			printf("$ ");
		else 
			printf("# ");
		
		signal(SIGINT, SIG_DFL);	

		/*string processing*/	
		mem = (TMemory *)malloc(sizeof(TMemory));
		mem->end = mem->beg;
		
		if (readme(mem) != -1)
		{
			/*signal(SIGINT, SIG_IGN);*/
			
			analyze_this(mem);
	       
			/*restore environment*/
			close(t);	
			if (mem->end != mem->beg) 
					free(mem->beg);
			mem->end = mem->beg;
		}	

	}
	return 0;
}
