/*
 * wordperline.c
 *
 * Author: Hans Prieto
 * Usage: ./wordperline [-lp] [FILE...]
 */

#include "iterator.h"
#include "arraylist.h"
#include "stringADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 4096

typedef struct my_file {
	FILE *f;
} MyFile;

int wordperline(int lowercase, int punct, MyFile files[], int nFiles) {
	/*
	 * Prints each word in the specified files on a line of its 
	 * own on standard output.
	 * If no files are specified, standard input is processed.
	 */
	char line [SIZE];
	int i;
	for (i = 0; i < nFiles; i++) {
		while(fgets(line, SIZE, files[i].f) != NULL) {
			const String *st = String_create(line);
			st->strip(st);
			int length = st->len(st);
			if (length == 0) {
				continue;
			}
			if(lowercase) {
				st -> lower(st);
			}
			if(punct) {
				int j;
				for(j = 0; j < length; j++) {
					const String *str2 = st->slice(st, j, j + 1);
					if (ispunct(str2->convert(str2)[0])){
						st -> replace(st, str2->convert(str2), " ");
					}
					str2->destroy(str2);
				}
			}
			st->strip(st);
			length = st->len(st);
			if (length == 0) {
				continue;
			}
			const ArrayList *al = st->split(st,"");
			for(long k = 0L; k< al->size(al); k++) {
				char *sp;
				(void) al->get(al, k, (void **)&sp);
				printf("%s\n", sp);
			}
			al->destroy(al, free);
			st->destroy(st);		
		}
		if(files[i].f != stdin) {
			fclose(files[i].f);
		}
	}
	return 0;
}	


int main(int argc, char *argv[]) {
	/* Parses the specified flags.
	 * Parses the files, if no files are specified,
	 * defaults to standard input.
	 * Calls the wordperline function.
	 */
	int lowercase = 0, punct = 0, i, nFiles = 0;

	for (i = 1; i < argc; i++) {
		if(argv[i][0] == '-') {
			int j;
			for(j = 1; argv[i][j] != '\0'; j++) {
				if(argv[i][j] != 'l' && argv[i][j] != 'p') {
					fprintf(stderr, "illegal option -- %c\n", argv[i][j]);
					return 1;
				}
				if(argv[i][j] == 'l') {
					lowercase = 1;
				}
				if (argv[i][j] == 'p') {
					punct = 1;
				}
			}
		}
		else {
			break;
		}
	}	
	MyFile files[100];
	for(; i < argc; i++) {
		FILE *fd = fopen(argv[i], "r");
		if (fd == NULL) {
			fprintf(stderr, "Unable to open file: %s\n", argv[i]);
			return 1;
		}
		files[nFiles].f = fd;
		nFiles++;
	}
	if (nFiles == 0) {
		files[nFiles].f = stdin;
		nFiles++; 
	}
	wordperline(lowercase, punct, files, nFiles);
	return 0;
}

