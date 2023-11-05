#include "stdio.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "DateTime.h"
#include "Objects.h"
#include "Headers.h"
#include "Structs.h"
#pragma warning ( disable : 4996 )

#define O 10
#define N 26
#define DATESTRINGLEN 11

using namespace std;

void PrintObjects(HeaderC*);


void PrintObjects(HeaderC* pStruct4) {

	int CurrentDepth = 0;
	while ((pStruct4 != NULL) && (CurrentDepth < N)) {
		printf("\n(HeaderC %d) %c", CurrentDepth++, pStruct4->cBegin);
		for (int j = 0; j < N; j++) {
			Object10* pObjectTemp = (Object10*)pStruct4->ppObjects[j];
			while (pObjectTemp != 0) {
				printf("\n\t(Obj %d) PID: %s %lu %02d %s %04d", j, pObjectTemp->pID, pObjectTemp->Code, pObjectTemp->sDate3.Day,
					pObjectTemp->sDate3.pMonth, pObjectTemp->sDate3.Year);
				pObjectTemp = pObjectTemp->pNext;
			}
		}
		pStruct4 = pStruct4->pNext;

	}
}

bool CheckFormat(char* newCandidate) {
	if (newCandidate == NULL)
		return false;
	if (newCandidate[0] < 65)
		return false;
	if (newCandidate[0] > 90)
		return false;
}

HeaderC* FindExistingHeader(HeaderC* pStruct4, char* pNewID) {
	int CurrentDepth = 0;
	while ((pStruct4 != NULL) && (CurrentDepth < N)) {
		if (pNewID[0] == pStruct4->cBegin) {
			return pStruct4;
		}
		pStruct4 = pStruct4->pNext;
	}
	return NULL;
}

HeaderC* CreateNewHeaderC(HeaderC* pStruct4, char* pNewID) {
	HeaderC* newHeader = (HeaderC*)malloc(sizeof(HeaderC));
	newHeader->cBegin = (char)malloc(sizeof(pNewID[0]));
	newHeader->cBegin = pNewID[0];
	return newHeader;
}

bool DoesObjectExist(HeaderC* pStruct4, char* pNewID) {
	for (int j = 0; j < N; j++) {
		Object10* pObjectTemp = (Object10*)pStruct4->ppObjects[j];
		if (strcmp(pObjectTemp->pID, pNewID) == 0) {
			return true;
		}
	}
	return false;
}

void AddToExisting(HeaderC* pStruct4, char* pNewID, int newCode) {

}

int InsertNewObject(HeaderC** pStruct4, char* pNewID, int newCode) {
	if (CheckFormat(pNewID) == false) {
		printf("\nINVALID FORMAT\n");
		return 0;
	}
	HeaderC* existing = FindExistingHeader(*pStruct4, pNewID);
	if (existing == NULL) {
		existing = CreateNewHeaderC(*pStruct4, pNewID);
	}
	if (DoesObjectExist(*pStruct4, pNewID)) {
		printf("\n%s ALREADY EXISTS\n", pNewID);
		return 0;
	}
	AddToExisting(*pStruct4, pNewID, newCode);
}


int main()
{
	HeaderC* pStruct4 = GetStruct4(O, N);
	PrintObjects(pStruct4);

	char newID[4] = "Bzd";

	InsertNewObject(&pStruct4, newID, 10120);

	PrintObjects(pStruct4);
	/*
	RemoveExistingObject(&pStruct4, newID);

	PrintObjects(pStruct4);
	*/
	return 0;


	//printf("            Test2\n");
	// Lisada antud järjekorras objektid identifikaatoritega
	//const char* uusID[] = { "Dx", "Db", "Dz", "Dk", "Aa", "Wu","Wa", "Zw", "Za", "wk", "Wa", "WW", "W8", "W_" };
	//int m = sizeof(uusID) / sizeof(uusID[0]);
	//printf("Sisestavad uued ID%d:\n\n", m);
	//PrintObjects(pStruct4);
	//printf("            Test3\n");
	//PrintObjects(pStruct4);
	return 0;
}

