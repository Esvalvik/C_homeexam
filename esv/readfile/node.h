#include <stdio.h>

#ifndef _NODE_H_
#define _NODE_H_

#define ULONG unsigned long
#define MAX_NODES 10

#define FALSE 0
#define TRUE !FALSE

#define STRING 1
#define INT 2
#define FOLDER 3

typedef struct _NODE
{
	char* psName; //Navnet på denne noden.
	ULONG ulVal; // Hvis numerisk er dette verdien.
	char* pStrVal; // Peker til streng eller NULL hvis numerisk
	struct _NODE* pnNodes[MAX_NODES]; // Pekere til under-noder.
} NODE;

void readFile(FILE* fp, char* line);
void Delete(char* pPath);
void DeleteNode(NODE* node);
void trim(char* string);
NODE* findNodeByKey(char* pPath);
NODE* findChildNode(NODE* node, char* pPath);
int checkType(char* value);
static NODE* CreateNode(const char* pName, ULONG uLong, const char* pStrVal);
void TestGetType(char* path);
void removeSpaces(char* string);
void printNode(char* name, char* strValue, ULONG ulVal);

#endif