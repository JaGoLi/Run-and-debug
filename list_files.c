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

void main() {
	const int avsize = getdirnum("/usr/bin");
	printf("Number of files: %i\n", avsize);

	char list[avsize][asizeh];
	getdirfiles("/usr/bin", list);
	
	char test[asizeh];	
	strcpy(test ,list[1000]);
	
	printf("%s\n", test);	
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

	
