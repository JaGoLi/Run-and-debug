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

static const int asizeh = 256; /* max number of characters in a file - same as in struct dirent - do not change */
static int getdirfiles(char directory[], char database[][asizeh]);
static int getdirnum(char directory[]);
static int sortalpha(const void *p, const void *q);

void main() {
	char pwd[] = "/usr/bin"; 

	const int avsize = getdirnum(pwd);

	char list[avsize][asizeh];
	getdirfiles(pwd, list);

	qsort(list, avsize, asizeh, sortalpha);

	int i;
	for (i = 3; i < avsize; i++){	
	char test[asizeh];	
	strcpy(test ,list[i]);
	
	printf("%s\n", test);	
		}
	printf("Number of files: %i\n", avsize + 1);
} 


int sortalpha(const void *p, const void *q) {
	const char *cp = (const char *) p;
	const char *cq = (const char *) q;
	return strcmp(cp, cq);
}	

 
int getdirfiles(char directory[], char database[][asizeh])
{
    int asizev = 0;
    DIR *current = opendir(directory);
    struct dirent *dirstc;

    if (current == NULL) {
	printf("error");
	return 1;
	}
    
    while ((dirstc = readdir(current)) != NULL) {
	strcpy(database[asizev], dirstc->d_name);
	asizev++; 
	}
    
	closedir(current);
    return 0;
}

int getdirnum(char directory[]) {
	int i;
	struct dirent *dirstc;
	DIR *current = opendir(directory);

	if (current == NULL) printf("ERROR");

	for(i = 0; (dirstc = readdir(current)) != NULL; i++);
	return i;

	closedir(current);
}

