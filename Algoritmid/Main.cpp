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
#define N 35
#define DATESTRINGLEN 11

using namespace std;
int CurrentDepth = 0;
int CurrentObject10Depth = 0;

void PrintObjects(HeaderC*);
void Printob10(Object10*);


void PrintObjects(HeaderC* pStruct4) {
	//CurrentObject10Depth = 0;
	//if (++CurrentDepth > N)
	//	return;
	//if (pStruct4 == NULL) {
	//	return;
	//}
	//printf("\n(HeaderC %d) %c", CurrentDepth, pStruct4->cBegin);
	//Object10* pObjectTemp = (Object10*)pStruct4->ppObjects;
	//Printob10(pObjectTemp);
	//HeaderC* muutuja = pStruct4->pNext;
	//PrintObjects(muutuja);
	HeaderC* HeaderCtemp = pStruct4;
	while ((pStruct4 != NULL) && (CurrentDepth < N)) {
		CurrentObject10Depth = 0;
		printf("\n(HeaderC %d) %c", CurrentDepth++, pStruct4->cBegin);
		pStruct4 = pStruct4->pNext;
		Object10* pObjectTemp = (Object10*)HeaderCtemp->ppObjects;
		while ((pObjectTemp != NULL) && (CurrentObject10Depth < N)) {
			printf("\n\t(Obj %d) %s %lu %02d %s %04d", CurrentObject10Depth++, pObjectTemp->pID, pObjectTemp->Code, pObjectTemp->sDate3.Day,
				pObjectTemp->sDate3.pMonth, pObjectTemp->sDate3.Year);
			pObjectTemp = pObjectTemp->pNext;

		}
	}

}
//void Printob10(Object10* pObjectTemp) {
//	if (++CurrentObject10Depth > N)
//		return;
//	if (pObjectTemp == NULL) {
//		return;
//	}
//	printf("\n\t(Obj %d) %s %lu %02d %s %04d", CurrentObject10Depth, pObjectTemp->pID, pObjectTemp->Code, pObjectTemp->sDate3.Day,
//		pObjectTemp->sDate3.pMonth, pObjectTemp->sDate3.Year);
//	Printob10(pObjectTemp->pNext);
//}

//int InsertNewObject(HeaderC** pStruct4, char* pNewID, int NewCode) {
//
//}
//Object10* RemoveExistingObject(HeaderC** pStruct4, char* pExistingID) {
//
//}


int main()
{
	HeaderC* pStruct4 = GetStruct4(O, N);
	printf("");
	PrintObjects(pStruct4);


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
