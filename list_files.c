#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include <dirent.h>
#include <ncurses.h>

//functions
static const int asizeh = 256; /* max number of characters in a file - same as in struct dirent - do not change */
static int getdirfiles(int vplace, char directory[], char database[][asizeh]);
static int getdirnum(char directory[]);
static int sortalpha(const void *p, const void *q);
static void program(char *array, bool parent, bool child); 
static void printmatches(const int num_progs, char database[][asizeh]);
static void startwin();

//string vars
char uprompt[] = "Search for program: ";
char *string = NULL;
char *selprog;
size_t mem = 0, charsize = 0;
int ch = EOF;

//path direcotires
char pwd1[] = "/usr/bin";
char pwd2[] = "/usr/local/bin"; 

//structs
typedef struct {
	int term_rows;
	int term_cols;
} WinProps;

WinProps *wp;

typedef struct timespec timespec;


int main() {

	const int avsize1 = getdirnum(pwd1);
	const int avsize2 = getdirnum(pwd2);

	const int avtotal = avsize1 + avsize2;
	char list[avtotal][asizeh];

	getdirfiles(0, pwd1, list);
	getdirfiles(avsize1, pwd2, list);

	qsort(list, avtotal, asizeh, sortalpha);

	startwin();

	wp = malloc(sizeof(int));
	
	getmaxyx(stdscr, wp->term_rows, wp->term_cols);

	printw(uprompt);
	move(1,0);
	
	int i;
	int linetot = wp->term_rows + 4;

	for (i = 5; i < linetot; i++) {
		char temp[asizeh];
		strcpy(temp, list[i]);
		printw("%s\n", temp);
		}

	move(0, strlen(uprompt));

    while ((ch = getch()) != ('\n')) {
     switch (ch) {
	case 127: {
		if (charsize > 0) {
		mvdelch(0, strlen(uprompt) + charsize - 1);
		string[--charsize] = 0;
		move(1,0);
		clrtobot();

		printmatches(avtotal, list);
			}
		break;
		}	


	default: { 
	printw("%c", ch);
	move(1,0);
	clrtobot();

        if (mem <= charsize) {
            mem += sizeof(char);
            string = realloc(string, mem);
        }

        string[charsize++] = ch;
	
	printmatches(avtotal, list);
    	    	}
	   }
	}

	endwin();
	program(selprog, true, true);
	return 0;
} 

void startwin() {
	initscr();
	noecho();
	cbreak();
}

void printmatches(const int num_progs, char finaldata[][asizeh]) {
	int i;
	int selines = 1;
	for (i = 5; i < num_progs; i++){	
	char test[asizeh];	

	if ((strncmp(finaldata[i], string, strlen(string)) == 0) && (selines < wp->term_rows)) {	
		if(selines == 1) { 
			selprog = NULL;
			selprog = malloc(256 * sizeof(char));
			strcpy(selprog, finaldata[i]);
		}
	
	
	strcpy(test, finaldata[i]);
	selines++;

	printw("%s\n", test);
			}
	else continue;
		}

	move(0, charsize + strlen(uprompt));
}

int sortalpha(const void *p, const void *q) {
	const char *cp = (const char *) p;
	const char *cq = (const char *) q;
	return strcasecmp(cp, cq);
}	

 
int getdirfiles(int vplace, char directory[], char database[][asizeh])
{
    DIR *current = opendir(directory);
    struct dirent *dirstc;

    if (current == NULL) {
	printf("error");
	return 1;
	}
    
    while ((dirstc = readdir(current)) != NULL) {
	strcpy(database[vplace], dirstc->d_name);
	vplace++; 
	}
    
	closedir(current);
    return 0;
}

int getdirnum(char directory[]) {
	int i;
	struct dirent *dirstc;
	DIR *current = opendir(directory);

	if (current == NULL) printf("error");

	for(i = 1; (dirstc = readdir(current)) != NULL; i++);

	closedir(current);
	return i;
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
	
	char *cmd[] = { "st", array, (char *)0 };
	execvp(cmd[0], cmd);

	exit(0);
	}

	else {
	timespec t;	
	t.tv_sec = 0;
	t.tv_nsec = 500000;

	nanosleep(&t, &t);
	printf("Successfully launched\n");	
	}
}
