/*analyze.h Khartikova*/

TList *new_job(); /*новый процесс*/

TArg *new_arg();  /*новый аргумент*/

void analyze_that(TList *job); /*анализ процесса: построение списка аргументов для execvp*/  

#define skip(p)		while (*p != '\0' && p <= mem->end) p++; while (*p == '\0' && p <= mem->end) p++;
/*макрос для перехода на другое слово*/
