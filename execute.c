/*execute.c Khartikova*/

#include "shell.h"
#include "execute.h"
int pid;
int bg = 0;

void sighandler(int s)
{
	signal(SIGINT, sighandler);
	kill(pid, SIGINT);

}

void redirect(struct TList *job, int mode)
{
	struct TArg *arg;
	int fd;

	arg = job->arg;

	while (arg != NULL)
	{
		if (arg->norm == 0)
		{	
			if (mode == 1 || mode == 0)
			{
				if((fd = open(arg->start, O_RDONLY)) == -1)
				{
						printf("Нет такого файла!\n");
						exit(2);
				}
				dup2(fd, 0);
				close(fd);
			}
			else
			{
				printf("Перенаправление ввода в pipe!\n");
				exit(2);			
			}
		}
		if (arg->norm == 1 || arg->norm == 2)
		{
			if (mode == -1 || mode == 0)
			{
				if ((fd = open(arg->start, O_WRONLY | O_CREAT)) == -1)
				{
					printf("Ошибка записи в файл!\n");
					exit(2);
				}
				dup2(fd, arg->norm);
				close(fd);
			}
			else
			{
				printf("Перенаправление вывода в pipe!\n");
				exit(2);
			}
		}
		if (arg->norm == 3)
		{
		/*фоновый режим не забыть про mode*/
				if (mode == 0) 
					/*signal(SIGINT, SIG_IGN);*/
				{
					/*setpgrp();*/
					signal(SIGINT, SIG_IGN);
					kill(getppid(), SIGUSR1);
					close(0);
				}
				else
					printf("Bacground mode not available\n");
		}

		arg = arg->next;
	
	}
}

void exe_cute(struct TList *curr)
{
			execvp(curr->arg->start, curr->pv);
			perror(cut(curr->arg->start));
			exit(1);
}

void bg_wait(int s)
{
	bg = 1;
}

void pipe_exec(struct TList *first, int count, int op)
{
	int fd[2];
	int i;
	int status;
	bg = 0;

	signal(SIGUSR1, bg_wait);

	struct TList *curr, *extra ;
	curr = first;
	extra = curr;

	if ((pid = fork()) != 0)
	{
			signal(SIGINT, sighandler);
			while (bg == 0 && wait(&status) == -1);
			/*if 	(WIFEXITED(status) == 0) 
					printf("Заданная команда завершилась неудачей\n");*/
	
	}
	else	
	{
		if (count != 1)
		{
			for (i = 1; i <= count - 1; i++)
			{

				pipe(fd);
				curr = extra;
				extra = curr->right;
				if (fork() == 0)
				{

					dup2(fd[1], 1);
					close(fd[0]);
					close(fd[1]);

					redirect(curr, i);
					exe_cute(curr);
				}
				else
				{
					dup2(fd[0], 0);
					close(fd[0]);
					close(fd[1]);
				}
		
			}
			/*exec last*/
			while (curr->right != NULL) 
					curr = curr->right;
			redirect(curr, -1);
			exe_cute(curr);
		}
		else
		{
		/*exec this*/
			redirect(curr, 0);
			exe_cute(curr);
		}
	}

}
