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
void Printob10(Object10*);


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


//int InsertNewObject(HeaderC** pStruct4, char* pNewID, int NewCode) {
//
//}
//Object10* RemoveExistingObject(HeaderC** pStruct4, char* pExistingID) {
//
//}


int main()
{
	HeaderC* pStruct4 = GetStruct4(O, N);
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
