// list.h: Lession 7, exercise 3
//
//
#ifndef _LIST_H_
#define _LIST_H_

#define OK      0
#define ERROR   1

// The list type:

typedef struct _NODE
{
	char* pName; //Navnet på denne noden.
	ULONG ulIntVal; // Hvis numerisk er dette verdien.
	char* pString; // Peker til streng eller NULL hvis numerisk
	struct _NODE *pNodes[MAX_NODES]; // Pekere til under-noder.
} NODE;

// Prototypes - functions return OK or ERROR.

int InsertInList (LIST **ppHead, void *pvData, int iSze);
int AddToList (LIST **ppHead, void *pvData, int iSze);
int RemoveFromList (LIST **ppHead, LIST *pToDelete);

#endif // ndef _LIST_H
