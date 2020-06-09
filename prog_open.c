#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>

//declare functions
static void program(char *array, bool parent, bool child);
static char *getstr();

typedef struct timespec timespec;

int main() {
	
	char *name;

	printf("Program to launch: ");
	
	name = getstr();
	
	program(name, true, true);
	free(name);
	
	return 0;
}

char *getstr()
{
    char *string = NULL;
    size_t mem = 0, asize = 0;
    int ch = EOF;

    while (ch) {
        ch = getc(stdin);

        if (ch == '\n') ch = 0;

        if (mem <= asize) {
            mem += sizeof(char);
            string = realloc(string, mem);
        }

        string[asize++] = ch;
    }

    return string;
}

void program(char *array, bool parent, bool child) {	

	if (parent == true) {
	int parentpid = getpid();
	printf("parent process number is: %i\n", parentpid);
		}
	
	if (fork() == 0) {

	if (child == false) {	
	int out = open("/dev/null", O_WRONLY);
	dup2(out, 1);
	dup2(out, 2);
	close(out);
		}

	else {
	int childpid = getpid();
	printf("child process number is: %i\n", childpid);
		}

	execvp(array, NULL);
	exit(1);
	}

	else {
	int status;
     	wait(&status);
	
	if(WIFEXITED(status)) {
	
	timespec t;	
	t.tv_sec = 0;
	t.tv_nsec = 500000;

	nanosleep(&t, &t);
	printf("closed\n");	
		}
	}
}
