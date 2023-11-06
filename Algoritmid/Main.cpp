#include "stdio.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "DateTime.h"
#include "Objects.h"
#include "Headers.h"
#include "Structs.h"
#include "Main.h"
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
			while (pObjectTemp != NULL) {
				printf("\n\t(Obj %d) PID: %s %lu %02d %s %04d", j, pObjectTemp->pID, pObjectTemp->Code, pObjectTemp->sDate3.Day, pObjectTemp->sDate3.pMonth, pObjectTemp->sDate3.Year);
				//printf("\n\t(Obj %d) PID: %s %lu ", j, pObjectTemp->pID, pObjectTemp->Code);
				//if (pObjectTemp->sDate3 != 0)
				//	printf("%02d %s %04d", pObjectTemp->sDate3.Day, pObjectTemp->sDate3.pMonth, pObjectTemp->sDate3.Year);
				pObjectTemp = pObjectTemp->pNext;
				if (pObjectTemp != NULL) {
					printf("\nTODO: !!!!Linked objects not implemented, need recodeing!!!!!\n");
					printf("\n\t(Obj %d) PID: %s %lu %02d %s %04d", j, pObjectTemp->pID, pObjectTemp->Code, pObjectTemp->sDate3.Day, pObjectTemp->sDate3.pMonth, pObjectTemp->sDate3.Year);

					exit(500);
				}
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
	//for (int i = 1; newCandidate[i] != '\0'; i++) {
	//	if (newCandidate[i] < 97)
	//		return false;
	//	if (newCandidate[i] > 122)
	//		return false;
	//}
}

HeaderC* FindExistingHeader(HeaderC* pStruct4, char* pNewID) {
	while (pStruct4 != NULL) {
		if (pNewID[0] == pStruct4->cBegin) {
			return pStruct4;
		}
		pStruct4 = pStruct4->pNext;
	}
	return NULL;
}

HeaderC* FindPreviousHeader(HeaderC* pStruct4, char pID) {
	if (pStruct4 == NULL) {
		return NULL;
	}
	HeaderC* Previous = NULL;
	while (pStruct4 != NULL) {
		if (pID > pStruct4->cBegin) {
			Previous = pStruct4;
		}
		else
			return Previous;
		pStruct4 = pStruct4->pNext;
	}
	return Previous;
}

HeaderC* FindNextHeader(HeaderC* pStruct4, char pID) {
	while (pStruct4 != NULL) {
		if (pID < pStruct4->cBegin) {
			return pStruct4;
		}
		pStruct4 = pStruct4->pNext;
	}
	return NULL;
}

HeaderC* CreateNewHeaderC(HeaderC* pStruct4, char* pNewID, bool& isfirst) {
	isfirst = false;
	HeaderC* newHeader = (HeaderC*)malloc(sizeof(HeaderC));
	newHeader->cBegin = (char)malloc(sizeof(pNewID[0]));
	newHeader->cBegin = pNewID[0];
	HeaderC* Prev = FindPreviousHeader(pStruct4, pNewID[0]);
	HeaderC* Next = FindNextHeader(pStruct4, pNewID[0]);
	if (Prev != NULL) {
		Prev->pNext = newHeader;
	}
	else {
		isfirst = true;
	}
	newHeader->pNext = Next;
	newHeader->ppObjects = (void**)(new Object10[N]);
	for (int loc = 0; loc < N;loc++) {
		newHeader->ppObjects[loc] = NULL;
	}
	return newHeader;
}

bool DoesObjectExistOptionallyRemove(HeaderC* pStruct4, char* pNewID, bool removeIfExists) {
	if (pStruct4->ppObjects == NULL) {
		return false;
	}
	for (int j = 0; j < N; j++) {
		Object10* pObjectTemp = (Object10*)pStruct4->ppObjects[j];
		if (pObjectTemp == NULL) {
			continue;
		}
		if (strcmp(pObjectTemp->pID, pNewID) == 0) {
			if (removeIfExists)
			{
				//delete pObjectTemp->pID;
				//delete pObjectTemp->pNext;
				//delete pObjectTemp;
				pStruct4->ppObjects[j] = NULL;
			}
			return true;
		}
	}
	return false;
}

void setDate(Object10* newobj) {
	//time_t rawtime = time(NULL);						//Gets current time
	//time(&rawtime);
	//Date3* pResult = (Date3*)malloc(sizeof(Date3));	//Allocate memory for Date3 structure
	//char* monthBuffer = (char*)malloc(10);            //Create buffer for month pointer
	//GetDate3(time_t RawTime, int nMonthBuf, char *pMonthBuf, Date3 *pDate3);
	/*
	* 	if (GetDate3(RawTime, 10, monthBuffer, pResult) == 1) //Makes date format from RawTime
	{
		newobj->sDate3.Day = pResult->Day; //Write day to structure

		newobj->sDate3.pMonth = strdup(pResult->pMonth); //Write month to structure

		////newobj->sDate3.pMonth[sizeof(newobj->sDate3.pMonth) - 1] = '\0'; //EOF to month

		newobj->sDate3.Year = pResult->Year; //Write year to structure
	}
	else
	{
		printf("Date not aquired!");
		exit(EXIT_FAILURE);
	}
	*/
	newobj->sDate3.Day = 06; // = new Date3;//(Date3*)malloc(sizeof(newobj->sDate3));
	newobj->sDate3.pMonth = new char[9] {'N', 'o', 'v', 'e', 'm', 'b', 'e', 'r', '\0'};
	newobj->sDate3.Year = 2023;
	printf("TODO FIX ME DATETIME");
}

void AddToExisting(HeaderC* pStruct4, char* pNewID, unsigned long int newCode) {
	//Object10* newobj = (Object10*)malloc(sizeof(Object10));
	//struct ob10* newobj = (struct ob10*)malloc(sizeof(struct ob10));
	Object10* newobj = new Object10;
	newobj->pID = (char*)malloc(sizeof(newobj->pID));
	newobj->pID = pNewID;
	newobj->Code = (unsigned long int)malloc(sizeof(newobj->Code));
	newobj->Code = newCode;
	//newobj->pNext = (Object10*)malloc(sizeof(newobj->pNext));
	newobj->pNext = new Object10;//(Object10*)malloc(sizeof(newobj->pNext));
	newobj->pNext = (Object10*)pStruct4->ppObjects[0];
	setDate(newobj);
	void** old = pStruct4->ppObjects;
	pStruct4->ppObjects = (void**)(new Object10[N]);
	pStruct4->ppObjects[0] = newobj;
	int loc = 1;
	for (int j = 0; j < N; j++) {
		Object10* pObjectTemp = (Object10*)old[j];
		if (pObjectTemp == NULL) {
			continue;
		}
		if (loc >= N)
			break;
		pStruct4->ppObjects[loc++] = pObjectTemp;
	}
	for (loc;loc < N;loc++) {
		pStruct4->ppObjects[loc] = NULL;
	}
}

/// <summary>
/// Inserts new object header and / or object
/// </summary>
/// <param name="pStruct4"></param>
/// <param name="pNewID"></param>
/// <param name="newCode"></param>
/// <returns>1 if added, 0 if not added</returns>
int InsertNewObject(HeaderC** pStruct4, char* pNewID, unsigned long int newCode) {
	if (CheckFormat(pNewID) == false) {
		printf("\n[%s] INVALID FORMAT\n", pNewID);
		return 0;
	}
	HeaderC* existing = FindExistingHeader(*pStruct4, pNewID);
	if (existing == NULL) {
		bool isfirst = false;
		existing = CreateNewHeaderC(*pStruct4, pNewID, isfirst);
		if (isfirst) {
			*pStruct4 = existing;
		}
	}
	if (DoesObjectExistOptionallyRemove(existing, pNewID, false)) {
		printf("\n[%s] ALREADY EXISTS\n", pNewID);
		return 0;
	}
	printf("[%s] Adding \n", pNewID);
	AddToExisting(existing, pNewID, newCode);
	return 1;
}

/// <summary>
/// Not in use. DoesObjectExist extra parameter does the same.
/// </summary>
/// <param name="existing"></param>
/// <param name="pNewID"></param>
Object10* RemoveObject(HeaderC* existing, char* pNewID) {
	for (int j = 0; j < N; j++) {
		Object10* pObjectTemp = (Object10*)existing->ppObjects[j];
		if (pObjectTemp == NULL) {
			continue;
		}
		if (strcmp(pObjectTemp->pID, pNewID) == 0) {
			existing->ppObjects[j] = NULL;
			return pObjectTemp;
		}
	}
	return NULL;
}

bool CheckifHeaderEmpty(HeaderC* existing) {
	for (int i = 0; i < N; i++) {
		if ((existing->ppObjects[i]) != NULL) {
			return false;
		}
	}
	return true;
}

HeaderC* RemoveHeaderifEmpty(HeaderC* existing, HeaderC* veryfirst) {
	if (CheckifHeaderEmpty(existing) == true) {
		HeaderC* TempNext = existing->pNext;
		HeaderC* TempPrev = FindPreviousHeader(veryfirst, existing->cBegin);
		//delete existing->ppObjects;
		//delete existing->pNext;
		//delete existing;
		if (TempPrev == NULL) {
			return TempNext;
		}
		else {
			return NULL;
		}
		TempPrev->pNext = TempNext;
	}
}

Object10* RemoveExistingObject(HeaderC** pStruct4, char* pNewID) {
	if (CheckFormat(pNewID) == false) {
		printf("\nINVALID FORMAT\n");
		return NULL;
	}
	HeaderC* existing = FindExistingHeader(*pStruct4, pNewID);
	if (existing == NULL) {
		printf("Headerit ei eksisteeri");
		return NULL;
	}
	if (DoesObjectExistOptionallyRemove(existing, pNewID, false) == false) {
		printf("Objekti ei eksisteerinud");
		return NULL;
	}
	Object10* removedObject = RemoveObject(existing, pNewID);
	HeaderC* newBeginning = RemoveHeaderifEmpty(existing, *pStruct4);
	if (newBeginning != NULL) {
		*pStruct4 = newBeginning;
	}
	return removedObject;
}


int main()
{
	printf("\n---------------------------------Printing Inital------------------------\n");
	HeaderC* pStruct4 = GetStruct4(O, N);
	PrintObjects(pStruct4);



	printf("\n---------------------------------InsertNewObject------------------------\n");
	char newID[6] = "Dx Gz";
	int RT = InsertNewObject(&pStruct4, newID, 12345);
	printf("\n---RT=%d\n", RT);
	PrintObjects(pStruct4);

	//printf("\n---------------------------------Test3------------------------\n");
	//char newID1[20] = "Dldo Gjtls";
	//int TT = InsertNewObject(&pStruct4, newID1, 10120);
	//printf("\n---TT=%d\n", TT);
	//PrintObjects(pStruct4);

	printf("\n---------------------------------RemoveExistingObject------------------------\n");
	RemoveExistingObject(&pStruct4, newID);
	PrintObjects(pStruct4);

	printf("\n---------------------------------Multiple val------------------------\n");
	printf("Lisada antud järjekorras objektid identifikaatoritega\n");
	const char* newIDs[] = { "Dx Gz", "Dx Ga", "Db Aa", "Dk Za", "Dr Wa", "Aa Aa", "Ab Ba", "Za Aa", "Za Ab", "Za Ba", "Wx Xa", "Wx Aa", "zb Kk", "Zc ca", "Dr Wa", "ZB kk", "Fa", "Fa_Fa" };
	int m = sizeof(newIDs) / sizeof(newIDs[0]);
	for (int i = 0; i < m; i++) {
		InsertNewObject(&pStruct4, (char*)newIDs[i], 12345);
		PrintObjects(pStruct4);
	}
	return 0;
}

