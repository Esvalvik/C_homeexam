#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"


NODE* root;

void init()
{
	root = CreateNode("root", NULL, NULL);
}

typedef void (FNPRINT) (char* name, char* strValue, ULONG ulVal);

void Enumerate(char* path)
{
	printf("Enumerating %s\n", path);
	char* pPath = strdup(path);
	int count = 0;
	int len = strlen(pPath);
	if(pPath[len - 1] == '*')
	{
		pPath[len-2] = 0;
	}
	NODE* node = findNodeByKey(pPath);
	FNPRINT *fnsPrint = &printNode;
	if(node != NULL)
	{
		for(int i = 0; i < MAX_NODES; i++)
		{
			if(node->pnNodes[i] != NULL)
			{
				if(GetTypeByNode(node->pnNodes[i]) == INT)
				{
					fnsPrint(node->pnNodes[i]->psName, NULL, node->pnNodes[i]->ulVal);
				}
				else if(GetTypeByNode(node->pnNodes[i]) == STRING)
				{
					fnsPrint(node->pnNodes[i]->psName, node->pnNodes[i]->pStrVal, NULL);
				}
				count++;
			}
		}
	}
}

typedef void (FNPRINT) (char* name, char* strValue, ULONG ulVal);

void printNode(char* name, char* strValue, ULONG ulVal)
{
	if(strValue == NULL)
	{
		printf("Name: %s, Value: %lu\n", name, ulVal);
	}
	else
	{
		printf("Name: %s, Value: %s\n", name, strValue);
	}
	
}

char* GetText(char* name, char* lang)
{
	char* str = "strings.";
	char* pPath;
	if((pPath = malloc(strlen(str) + strlen(name) + strlen(lang) + 1)) != NULL)
	{
		strcat(pPath, str);
		strcat(pPath, lang);
		strcat(pPath, ".");
		strcat(pPath, name);
	}
	
	NODE* node = findNodeByKey(pPath);
	if(node != NULL)
	{
		printf("%s text: %s\n", pPath, node->pStrVal);
	}
	else if(strcmp(lang, "no") == 0)
	{
		free(pPath);
		pPath = malloc(strlen(str) + strlen(name) + strlen(lang) + 1);
		strcat(pPath, str);
		strcat(pPath, "en");
		strcat(pPath, ".");
		strcat(pPath, name);
		
		node = findNodeByKey(pPath);
		if(node != NULL)
		{
			printf("%s text: %s\n", pPath, node->pStrVal);
		}
	}
	else if(strcmp(lang, "en") == 0)
	{
		free(pPath);
		pPath = malloc(strlen(str) + strlen(name) + strlen(lang) + 1);
		
		strcat(pPath, str);
		strcat(pPath, "no");
		strcat(pPath, ".");
		strcat(pPath, name);
		node = findNodeByKey(pPath);
		if(node != NULL)
		{
			printf("%s text: %s\n", pPath, node->pStrVal);
		}
	}
	else
	{
		printf("Node not found in any language\n");
	}
}

void Delete(char* pPath)
{
	NODE* node = findNodeByKey(pPath);
	DeleteNode(node);
}

void DeleteNode(NODE* node)
{
	if(node == NULL)
	{
		printf("Node not found\n");
	}
	
	if(GetTypeByNode(node) == 3)
	{
		for(int i = 0; i < MAX_NODES; i++)
		{
			if(node->pnNodes[i] != NULL)
			{
				DeleteNode(node->pnNodes[i]);
			}
		}
	}
	free(node);
}

//Henter en int
void GetInt(char* pPath)
{
	printf("Getting int\n");
	int typeCheck = GetType(pPath);
	if(typeCheck == 4)
	{
		printf("Node not found\n");
	}
	else if(typeCheck == FOLDER || typeCheck == STRING)
	{
		printf("Node not int\n");
	}
	else if(typeCheck == INT)
	{
		NODE* node = findNodeByKey(pPath);
		printf("%s has the value %lu\n", pPath, node->ulVal);
	}
}

//Henter en string
void GetString(char* pPath)
{
	printf("Getting string\n");
	int typeCheck = GetType(pPath);
	if(typeCheck == 4)
	{
		printf("Node not found\n");
	}
	else if(typeCheck == FOLDER || typeCheck == INT)
	{
		printf("Node not string\n");
	}
	else if(typeCheck == STRING)
	{
		NODE* node = findNodeByKey(pPath);
		printf("%s has the value \"%s\"\n", pPath, node->pStrVal);
	}
}

//Finne typen node med path som parameter
int GetType(char* pPath)
{
	NODE* node = findNodeByKey(pPath);
	
	if(node != NULL)
	{
		if(node->pStrVal != NULL)
		{
			return STRING;
		}
		else if(node->ulVal != NULL)
		{
			return INT;
		}
		else
		{
			return FOLDER;
		}
	}
	return 4;
}

//For å kunne finne typen ved å senne inn noden som parameter
int GetTypeByNode(NODE* node)
{
	if(node != NULL)
	{
		if(node->pStrVal != NULL)
		{
			return STRING;
		}
		else if(node->ulVal != NULL)
		{
			return INT;
		}
		else
		{
			return FOLDER;
		}
	}
	return 4;
}

void SetValue(char* pPath, char* value)
{
	int strNum = getStrNum(pPath);
	int count = 1;
	const char s[2] = ".";
	char* tok = strtok(pPath, s);
	int isUlong = FALSE;
	NODE* lastNode = root;
	NODE* node = root;
	ULONG uLongVal;
	
	while(tok != NULL)
	{
		char* val = NULL;
		if(count == strNum)
		{
			val = value;
			if(checkType(val) == 2)
			{
				uLongVal = atoi(val);
				isUlong = TRUE;
			}
		}
		node = findChildNode(node, tok);
		if(node != NULL)
		{
			lastNode = node;
		}
		else
		{
			if(isUlong)
			{
				node = CreateNode(tok, uLongVal, NULL);
			}
			else
			{
				node = CreateNode(tok, NULL, val);
			}
			insertNode(lastNode, node);
			lastNode = node;
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

NODE* findChildNode(NODE* node, char* name)
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

NODE* findNodeByKey(char* pPath)
{
	char* copy = strdup(pPath);
	int strNum = getStrNum(pPath);
	int count = 1;
	const char s[2] = ".";
	char* tok = strtok(copy, s);
	NODE* node = root;
	
	while(tok != NULL)
	{
		node = findChildNode(node, tok);
		if(node == NULL)
		{
			return NULL;
		}
		
		tok = strtok(NULL, s);
		count++;
	}
	free(tok);
	return node;
}

static NODE* CreateNode(const char* pName, ULONG ulVal, const char* pStrVal)
{
	printf("Creating node %s\n", pName);
	NODE* pThis = malloc(sizeof(NODE));
	if(pThis != NULL)
	{
		memset(pThis, 0, sizeof(NODE));
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

void readFile(FILE* fp, char* line)
{
	if(fp == NULL)
	{
		printf("File is null\n");
		exit(1);
	}
	printf("Reading file\n");
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
	removeSpaces(pPath);
	SetValue(pPath, value);
	
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

void TestGetType(char* path)
{
	int type = GetType(path);
	if(type == 1)
	{
		printf("%s is type string\n", path);
	}
	else if(type == 2)
	{
		printf("%s is type int\n", path);
	}
	else if(type == 3)
	{
		printf("%s is a folder\n", path);
	}
	else
	{
		printf("%s is not found", path);
	}
}

void removeSpaces(char* string)
{
	int k = 0;
	for(int i = 0; i < strlen(string) - 1; i++)
	{
		if(string[i] != ' ')
		{
			string[k++] = string[i];
		}
	}
	string[k] = 0;
}