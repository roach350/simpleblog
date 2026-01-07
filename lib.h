/*
	SimpleBlog string functions
*/

#ifndef LIB_H
#define LIB_H

void initStr(char *str, int len);
int countNonZero(char *str, int len);
void appendStr(char *base, const char *addition, int index);
int countChar(char *str, int key);
#endif
