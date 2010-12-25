/*analyze.c Khartikova*/

#include "shell.h"
#include "analyze.h"

TList *new_job()
{
	TList *p;

	p = (TList *)malloc(sizeof(TList));
	
	p->first = NULL;
	p->right = NULL;
	p->arg = NULL;
	
	return p;	
}

TArg *new_arg()
{
	TArg *p;
	
	p =(TArg *)malloc(sizeof(TArg));
	
	p->start = NULL;
	p->end = NULL;
	p->next = NULL;

	(*p).norm = -1; 
	/*0 - '<'
	1 -'>'
	2 - ">>"
	3 - '&'*/
	
	return p;
}

void analyze_that(TList *job)
{
	TArg *arg;
	arg = job->arg;

	char **pv;
	int count = 0;


	while (arg != NULL)
	{
		count++;
		arg = arg->next;
	}

	arg = job->arg;
	
	pv = (char **)malloc((count+1)*sizeof(char *));
	job->pv = pv;

	while (arg != NULL)
	{
				
		if ((*arg).norm == -1)
		{	
			*pv = arg->start;	
		}
	
		arg = arg->next;
		pv++;

	}

	*pv = (char *) 0;

}

void analyze_this(TMemory *mem)
{
	char *p;
	TList *job;
	TArg *arg;
	int n = -1;
	int norm = -1;
	int op;

	int jobcount = 0;
	
	p = mem->beg;
	while (p <= mem->end)
	{
		
		if (jobcount == 0)
		{
				job = new_job();	
				job->first = job;
		}
	
		job->arg = new_arg();
		
		arg = job->arg;
		arg->start = p;
		skip(p);
		arg->end = p;
		
		norm = -1;

		while (strcmp(p, ";") != 0 && strcmp(p, "|") != 0 && p <= mem->end)
		{
			if (p != NULL)
			{
				if ((n = strcmp(p, "<")) == 0 || 
					(n = strcmp(p, ">") + 1) == 1 || 
					(n = strcmp(p, ">>") + 2) == 2 || 
					(n = strcmp(p, "&") + 3) == 3)
				{
						norm = n;
						if (n == 3)
						{	
							arg->norm = norm;
							norm = -1;	
						}
						skip(p);
				}
				else
				{
					arg->next = new_arg();
					arg = arg->next;

					arg->start = p;
					skip(p);
					arg->end = p;

					arg->norm = norm;
					norm = -1;
				}	
			}

		}

		analyze_that(job);

		if (strcmp(p, "|") == 0)
		{
			job->right = new_job();
			
			(job->right)->first = job->first;
			
			jobcount++;
			job = job->right;
			skip(p);
		}
		
		if ((op = strcmp(p, ";")) == 0 || (op = strcmp(p, "||") + 1) == 1 || (op = strcmp(p, "&&") + 2) == 2 || p >= mem->end)
		{
			jobcount++;
			pipe_exec(job->first, jobcount, op);
			jobcount = 0;
			skip(p);
		}		

	}

}
