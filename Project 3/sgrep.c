/*
 * Author: Hans Prieto
 *
 * C version of the 'grep' utility'
 *
 * SYNOPSIS:
 * 		sgrep [options] string [file...]
 */
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 2048

typedef struct tuple_file{
	FILE *fp;
	char filename[SIZE];
} Tuple_file;

void sgrep (bool ifcase, bool invert, bool count, char string[SIZE], Tuple_file files[SIZE], int num_files) {
	int i;
	char line[SIZE];
	char prefix[256];
	char tomatch[SIZE];
	bool matches;

	for(i = 0; files[i].fp != NULL; i++) {
		int N = 0;
		if (num_files > 1) {
			char colon[SIZE];
			strcpy(colon, ":");
			strcpy(prefix, files[i].filename);
			strcat(prefix, colon);				
		}

		else {
			prefix[0] = '\0';
		}
		
		while (fgets (line, SIZE, files[i].fp) != NULL) {
			matches = false;
			if (ifcase) {
				strcpy(tomatch, line);
			}

			else { 	
				int j;
				char lower[SIZE];
				strcpy(lower, line);
				for(j = 0; lower[j] != '\0'; j++) {
					lower[j] = tolower(lower[j]);
				}	
				strcpy(tomatch, lower);
			}	
			if (invert) {
				if (strstr(tomatch, string) == NULL) {
					matches = true;
				}
			}

			else {
				if (strstr(tomatch, string) != NULL) {
					matches = true;
				}
			}

			if (matches) {
				if (count) {
					N++;
				}
				else {
					printf("%s%s", prefix, line); 
				}
			}
		}	
		if (files[i].fp != stdin) {
			fclose(files[i].fp);
		}
		if (count) {
			printf("%s%d\n", prefix, N);
		}
	}
}

int main(int argc, char * argv[]) {
	char string[SIZE];
	bool ifcase = true;
	bool invert = false;
	bool count = false;
	int i;

	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			int j;
			for (j = 1; argv[i][j] != '\0'; j++) {
				if (argv[i][j] == 'i') {
					ifcase = false;
				}
				if (argv[i][j] == 'v') {
					invert = true;
				}
				if (argv[i][j] == 'c') {
				       count = true;
				}
			}		
		}
		else {
			break;
		}
	}	
	
	if (i >= argc) {
		fprintf(stderr, "Invoked without the required STRING parameter\n");
		return 1;
	}

	else {
		if (ifcase) {
			strcpy(string, argv[i]);
		}
		else {
			int k;
			char lower[SIZE];
			strcpy(lower, argv[i]);

			for(k = 0; lower[k] != '\0'; k++) {
				lower[k] = tolower(lower[k]); 
			}
			strcpy(string, lower);
		}

		i++;
		
		Tuple_file files[SIZE];
		int n = 0;
		int num_files;	
		if (i < argc) { 
		       while (i < argc) {
		     		files[n].fp = fopen(argv[i], "r");
				strcpy(files[n].filename, argv[i]);
				i++;
				n++;	
		       }
			num_files = n;		
		}	       
		else {
			num_files = 1;
			files[n].fp = stdin;
			strcpy(files[n].filename, "");
		}

		sgrep (ifcase, invert, count, string, files, num_files);
	}
		
	return 0;
}
