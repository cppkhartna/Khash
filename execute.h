/*execute.h Khartikova*/

void sighandler(int s);
void exe_cute(struct TList *curr);
void redirect(struct TList *job, int mode);
/*mode:
 * 0 - не внутри pipe
 * 1 - первый процесс pipe
 * (-1) - второй процесс pipe
 * ост - середина pipe*/
