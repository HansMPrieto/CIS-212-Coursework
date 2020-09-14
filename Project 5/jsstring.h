#ifndef __JSSTRING_H_
#define __JSSTRING_H_
#include <string.h>

char *jsStrchr(const char *s, int c);
int jsStrcmp(const char *s1, const char *s2);
char *jsStrcpy(char *dest, const char *src);
char *jsStrdup(const char *s);
size_t jsStrlen(const char *s);
int jsStrncmp(const char *s1, const char *s2, size_t n);
char *jsStrstr(const char *haystack, const char *needle);
#endif /* __JSSTRING_H_ */
