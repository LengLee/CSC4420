#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int makeargv(const char *s, const char *delimiters, char ***argvp) {
int error;
int i;
int numtokens;
const char *snew;
char *t;

if ((s == NULL) || (delimiters == NULL) || (argvp == NULL)) {
errno = EINVAL;
return -1;
}
*argvp = NULL;   
snew = s + strspn(s, delimiters); /* snew is real start of string */
if ((t = malloc(strlen(snew) + 1)) == NULL)
return -1;
strcpy(t, snew);   
numtokens = 0;
if (strtok(t, delimiters) != NULL) /* count the number of tokens in s */
for (numtokens = 1; strtok(NULL, delimiters) != NULL; numtokens++) ;

/* create argument array for ptrs to the tokens */
if ((*argvp = malloc((numtokens + 1)*sizeof(char *))) == NULL) {
error = errno;
free(t);
errno = error;
return -1;
}
/* insert pointers to tokens into the argument array */
if (numtokens == 0)
free(t);
else {
strcpy(t, snew);
**argvp = strtok(t, delimiters);
for (i = 1; i < numtokens; i++)
*((*argvp) + i) = strtok(NULL, delimiters);
}
*((*argvp) + numtokens) = NULL; /* put in final NULL pointer */
return numtokens;
}   

int main()
{
    int PID;
    char lineGot[256];
    char* cmd;
    char **arguments;
    while(1)
    {
       printf("cmd: ");
       fgets(lineGot, 256, stdin);
       cmd = strtok(lineGot, "\n");
       if(strcmp(cmd, "e") == 0)
           exit(0);
       if((PID=fork()) > 0)
           wait(NULL);
       else if(PID == 0)
       {
          makeargv(lineGot, " ", &arguments);
          execvp(arguments[0], arguments);
          fprintf(stderr, "Cannot execute %s\n", cmd);
          exit(1);
       }      
       else if(PID == -1)
       {
          fprintf(stderr, "Cannot create a new process\n");
          exit(2);
       }
    }
}
