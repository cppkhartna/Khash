/*Shell.h Khartikova*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
#include <string.h>
#include <signal.h>

typedef struct TArg
{
	char *start;
	char *end;
	struct TArg *next;

	int norm;

} TArg; /*список аргументов процесса*/

typedef struct TList
{
	struct TList *first;
	struct TList *right;
 
	struct TArg *arg;

	char **pv;	

} TList; /*список процессов*/


typedef struct
{
	char *beg;
	char *end;
} TMemory;		/*память*/

int readme(TMemory *mem);				 		/*read.c: читает со входного потока, сохраняет в память, разделяет на слова*/
void analyze_this(TMemory *mem);				/*analyze.c: анализ входных данных, запуск pipe_exec*/
void pipe_exec(struct TList *first, int count, int op); /*execute.c: выполнение связки процессов*/

/*auxiliary*/
char *cut(const char *path); /*cut the path to the short name*/
