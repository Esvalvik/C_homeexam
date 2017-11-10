#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ULONG unsigned long
#define MAX_NODES 10
#define FALSE 0
#define TRUE !FALSE
#define STRING 1
#define INT 2


typedef struct _NODE
{
	char* psName; //Navnet på denne noden.
	ULONG ulVal; // Hvis numerisk er dette verdien.
	char* pStrVal; // Peker til streng eller NULL hvis numerisk
	struct _NODE* pnNodes[MAX_NODES]; // Pekere til under-noder.
} NODE;

void readFile(FILE* fp, char* line);
void printNode(NODE* node);
void trim(char* string);
void addNode(char* node, char* value);
NODE* findNode(NODE* node, char* pPath);
int checkType(char* value);
static NODE* CreateNode(const char* pName, ULONG uLong, const char* pStrVal);



NODE* root;

int main(void)
{
	FILE* fp = fopen("test.txt", "r");
	char* line = NULL;
	root = CreateNode("root", NULL, NULL);
	
	//printNode(root);
	readFile(fp, line);
	getchar();
}

void printNode(NODE* node)
{
	if(node == NULL)
	{
		return;
	}
	char* name = node->psName;
	ULONG ulVal = node->ulVal;
	char* stVal = node->pStrVal;
	printf("Name: %s\nULong value: %s\nString value: %s\n", name, ulVal, stVal);
}

void readFile(FILE* fp, char* line)
{
	if(fp == NULL)
	{
		printf("File is null\n");
		exit(1);
	}
	size_t len = 0;
	
	while(getline(&line, &len, fp) != -1)
	{
		splitValue(line);
	}
}

void splitValue(char* line)
{
	const char s[2] = "=";
	
	char* pPath = strtok(line, s);
	char* value = strtok(NULL, s);
	trim(value);
	addNode(pPath, value);
	
}

void trim(char* value)
 {
	int len = strlen(value) - 1;
	int i, k = 0;
	int isString = FALSE;
	while(i < len)
	{
		if(value[i] == '"' && !isString)
		{
			isString = TRUE;
		}
		else if(value[i] == '"' && isString)
		{
			isString = FALSE;
		}
		else if(isString)
		{
			value[k++] = value[i];
		}
		else if(isdigit(value[i]) && !isString)
		{
			value[k++] = value[i];
		}
		i++;
	}
	value[k] = 0;
}

void addNode(char* pPath, char* value)
{
	if(checkType(value) == 1)
	{
		SetString(pPath, value);
	}
	else if(checkType(value) == 2)
	{
		ULONG iVal = atoi(value);
		SetInt(pPath, iVal);
	}
}


int checkType(char* value)
{
	int len = strlen(value);
	int isDigit = TRUE;
	
	for(int i = 0; i < len - 1; i++)
	{
		if(!isdigit(value[i]))
		{
			isDigit = FALSE;
		}
	}
	if(isDigit)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

static NODE* CreateNode(const char* pName, ULONG ulVal, const char* pStrVal)
{
	NODE* pThis = malloc(sizeof(NODE));
	if(pThis != NULL)
	{
		memset(pThis, 0, sizeof(NODE));
		//pThis->psName = malloc(sizeof(pName));
		//strncpy(pThis->psName, pName, strlen(pName));
		pThis->psName = strdup(pName);
		
		if(ulVal)
		{
			pThis->ulVal = ulVal;
		}
		else if(pStrVal)
		{
			pThis->pStrVal = strdup(pStrVal);
		}
	}
}


NODE* findNode(NODE* node, char* name)
{
	for(int i = 0; i < MAX_NODES; i++)
	{
		if(node->pnNodes[i] == NULL)
		{
			return NULL;
		}
		if(strcmp(node->pnNodes[i]->psName, name) == 0)
		{
			return node->pnNodes[i];
		}
	}
	return NULL;
}


void SetInt(char* pPath, int value)
{
	int strNum = getStrNum(pPath);
	int count = 1;
	const char s[2] = ".";
	char* tok = strtok(pPath, s);
	NODE* lastNode = root;
	NODE* node = root;
	
	while(tok != NULL)
	{
		int val = NULL;
		if(count == strNum)
		{
			val = value;
		}
		node = findNode(node, tok);
		if(node != NULL)
		{
			lastNode = node;
			//node = findNode(node, tok);
		}
		else
		{
			NODE* tmpNode = CreateNode(tok, val, NULL);
			insertNode(lastNode, tmpNode);
			lastNode = tmpNode;
			node = tmpNode;
		}
		
		tok = strtok(NULL, s);
		count++;
	}
}

void SetString(char* pPath, char* value)
{
	int strNum = getStrNum(pPath);
	int count = 1;
	const char s[2] = ".";
	char* tok = strtok(pPath, s);
	NODE* lastNode = root;
	NODE* node = root;
	
	while(tok != NULL)
	{
		char* val = NULL;
		if(count == strNum)
		{
			val = value;
		}
		node = findNode(node, tok);
		if(node != NULL)
		{
			lastNode = node;
			//node = findNode(node, tok);
		}
		else
		{
			NODE* tmpNode = CreateNode(tok, NULL, val);
			insertNode(lastNode, tmpNode);
			lastNode = tmpNode;
			node = tmpNode;
		}
		
		tok = strtok(NULL, s);
		count++;
	}
}

int getStrNum(char* pPath)
{
	int count = 1;
	int len = strlen(pPath) - 1;
	for(int i = 0; i < len; i++)
	{
		if(pPath[i] == '.')
		{
			count++;
		}
	}
	return count;
}

void insertNode(NODE* pParentNode, NODE* pNode)
{
	int inserted = FALSE;
	for(int i = 0; i < MAX_NODES; i++)
	{
		if(pParentNode->pnNodes[i] == NULL)
		{
			pParentNode->pnNodes[i] = pNode;
			inserted = TRUE;
			break;
		}
	}
	if(!inserted)
	{
		printf("Parentnode full\n");
	}
}


