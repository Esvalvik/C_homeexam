#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ULONG unsigned long
#define MAX_NODES 10
#define FALSE 0
#define TRUE !FALSE


void readFile(FILE* fp, char* line);
void splitValue(char* line);


typedef struct _NODE
{
	char *pszName; //Navnet på denne noden.
	ULONG ulIntVal; // Hvis numerisk er dette verdien.
	char *pszString; // Peker til streng eller NULL hvis numerisk
	struct _NODE *pnNodes[MAX_NODES]; // Pekere til under-noder.
} NODE;


int main(void)
{
	FILE* fp = fopen("test.txt", "r");
	char* line = NULL;
	readFile(fp, line);
}

void readFile(FILE* fp, char* line)
{
	if(fp == NULL)
	{
		printf("File is null\n");
		exit(1);
	}
	size_t len = 0;
	int lineLen = 0;
	
	while(getline(&line, &len, fp) != -1)
	{
		int dotCount = 0;
		lineLen = strlen(line);
		splitValue(line);
	}
}

void splitValue(char* line)
{
	char* nodes = strtok(line, s);
	char* value = strtok(NULL, s);
	
	const char s[2] = "=";
	
	printf("Nodes: %s\nValue: %s\n", nodes, value);
}




