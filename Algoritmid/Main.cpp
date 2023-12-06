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
#include <regex>
#pragma warning ( disable : 4996 )

#define O 10
#define N 26

using namespace std;

void PrintObjects(HeaderC*);
bool isRegexMatch(const std::string&, const std::string&);
bool CheckFormat(char*);
HeaderC* FindExistingHeader(HeaderC*, char*);
HeaderC* FindPreviousHeader(HeaderC*, char);
HeaderC* FindNextHeader(HeaderC*, char);
HeaderC* CreateNewHeaderC(HeaderC*, char*, bool&);
bool DoesObjectExistOptionallyRemove(HeaderC*, char*, bool);
void setDate(Object10*);
void AddToExisting(HeaderC*, char*, unsigned long int);
int InsertNewObject(HeaderC**, char*, unsigned long int);
Object10* RemoveObject(HeaderC*, char*);
bool CheckifHeaderEmpty(HeaderC*);
HeaderC* RemoveHeaderifEmpty(HeaderC*, HeaderC*);
Object10* RemoveExistingObject(HeaderC**, char*);
//second part
Node* InsertNode(Node*, void*);
Node* CreateBinaryTree(HeaderC*);
Stack* Push(Stack*, void*);
Stack* Pop(Stack*, void**);
void TreeTraversal(Node*);
//Node *DeleteTreeNode(Node * , unsigned long int);
//int CompareKeys(const void* , const void* );

int main()
{
	//Var4 Ob10
	printf("\n---------------------------------Printing Inital------------------------\n");
	HeaderC* pStruct4 = GetStruct4(O, 35);
	PrintObjects(pStruct4);


	printf("\n---------------------------------InsertNewObject------------------------\n");
	printf("Lisada antud järjekorras objektid identifikaatoritega\n");
	const char* newIDs[] = { "Dx Gz", "Dx Ga", "Db Aa", "Dk Za", "Dr Wa", "Aa Aa", "Ab Ba", "Za Aa", "Za Ab", "Za Ba", "Wx Xa", "Wx Aa", "zb Kk", "Zc ca", "Dr Wa", "ZB kk", "Fa", "Fa_Fa" };
	int m = sizeof(newIDs) / sizeof(newIDs[0]);
	for (int i = 0; i < m; i++) {
		InsertNewObject(&pStruct4, (char*)newIDs[i], 123456789 + i);
		//PrintObjects(pStruct4);
	}
	PrintObjects(pStruct4);
	printf("\n---------------------------------RemoveExistingObject------------------------\n");

	for (int i = 0; i < m; i++) {
		Object10* removed = RemoveExistingObject(&pStruct4, (char*)newIDs[i]);
		delete removed;
		//PrintObjects(pStruct4);
	}
	PrintObjects(pStruct4);
	printf("\n---------------------------------SecondPart------------------------\n");
	Node* pBinaryTree = CreateBinaryTree(pStruct4);
	TreeTraversal(pBinaryTree);
	return 0;
}

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
				//if (pObjectTemp != NULL) {
				//	printf("\n\n\t!!!FOUND LINKED OBJECT!!!");
				//	//printf("\t(Obj %d) PID: %s %lu %02d %s %04d", j, pObjectTemp->pID, pObjectTemp->Code, pObjectTemp->sDate3.Day, pObjectTemp->sDate3.pMonth, pObjectTemp->sDate3.Year);

				//	//exit(500);
				//}
			}
		}
		pStruct4 = pStruct4->pNext;
	}
}


bool isRegexMatch(const std::string& text, const std::string& pattern) {
	std::regex regexPattern(pattern);
	return std::regex_search(text, regexPattern);
}

bool CheckFormat(char* newCandidate) {
	if (newCandidate == NULL)
		return false;
	//if (newCandidate[0] < 65)
	//	return false;
	//if (newCandidate[0] > 90)
	//	return false;
	std::string regexToValidate = "^[A-Z][a-z]+\\s[A-Z][a-z]+$";
	std::string text = newCandidate;

	if (!isRegexMatch(text, regexToValidate)) {
		return false;
	}
	//for (int i = 1; newCandidate[i] != '\0'; i++) {
	//	if (newCandidate[i] < 97)
	//		return false;
	//	if (newCandidate[i] > 122)
	//		return false;
	//}
	return true;
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
	HeaderC* newHeader = new HeaderC; //(HeaderC*)malloc(sizeof(HeaderC));
	//newHeader->cBegin = (char)malloc(sizeof(pNewID[0]));
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
		if (strcmp(pObjectTemp->pID, pNewID) == NULL) {
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
	Date3* pResult = new Date3;
	char* monthBuffer = (char*)malloc(10);
	time_t RawTime = time(NULL);
	if (GetDate3(RawTime, 10, monthBuffer, pResult) == 1) {
		newobj->sDate3.Day = pResult->Day;
		newobj->sDate3.pMonth = strdup(pResult->pMonth);
		newobj->sDate3.Year = pResult->Year;
	}
	else {
		printf("Date not aquired!");
		exit(EXIT_FAILURE);
	}

	//newobj->sDate3.Day = 07; // = new Date3;//(Date3*)malloc(sizeof(newobj->sDate3));
	//newobj->sDate3.pMonth = new char[9] {'N', 'o', 'v', 'e', 'm', 'b', 'e', 'r', '\0'};
	//newobj->sDate3.Year = 2023;
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
	//newobj->pNext = new Object10;//(Object10*)malloc(sizeof(newobj->pNext));
	//newobj->pNext = (Object10*)pStruct4->ppObjects[0];
	newobj->pNext = NULL;//(Object10*)malloc(sizeof(newobj->pNext));
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
			TempPrev->pNext = TempNext;
			return NULL;
		}
		TempPrev->pNext = TempNext;
	}
	return NULL;
}

Object10* RemoveExistingObject(HeaderC** pStruct4, char* pNewID) {
	if (CheckFormat(pNewID) == false) {
		printf("\n[%s] INVALID FORMAT\n", pNewID);
		return NULL;
	}
	HeaderC* existing = FindExistingHeader(*pStruct4, pNewID);
	if (existing == NULL) {
		printf("Headerit ei eksisteeri");
		return NULL;
	}
	if (DoesObjectExistOptionallyRemove(existing, pNewID, false) == false) {
		printf("[%s] Objekti ei eksisteerinud", pNewID);
		return NULL;
	}
	Object10* removedObject = RemoveObject(existing, pNewID);
	HeaderC* newBeginning = RemoveHeaderifEmpty(existing, *pStruct4);
	if (newBeginning != NULL) {
		*pStruct4 = newBeginning;
	}
	printf("\n[%s] Removing \n", pNewID);
	return removedObject;
}

//int CompareKeys(const void* pKey, const void* pRecord)
//{
//	return strcmp((const char*)pKey, ((const Object10*)pRecord)->pID);
//}

Node* InsertNode(Node* pTree, void* pObject) {
	Node* pNew = (Node*)malloc(sizeof(Node));
	if (pNew == NULL) {
		printf("\nERROR ALLOCATING MEMORY FOR BINARY TREE NODE\n");
	}
	pNew->pObject = pObject;
	pNew->pLeft = pNew->pRight = NULL;
	if (pTree == NULL) {
		printf("\nStarted tree\n");
		return pNew;
	}
	for (Node* p = pTree; 1;) {
		Object10* pObjectTemp = (Object10*)p->pObject;
		if (((Object10*)pObject)->Code < pObjectTemp->Code) {
			if (p->pLeft == NULL) {
				p->pLeft = pNew;
				return pTree;
			}
			else {
				p = p->pLeft;
			}
		}
		else {
			if (p->pRight == NULL) {
				p->pRight = pNew;
				return pTree;
			}
			else {
				p = p->pRight;
			}
		}
	}
	printf("\n ERROR \n");
	return 0;
}

Node* CreateBinaryTree(HeaderC* pStruct4) {
	Object10* pObjectTemp;
	int i;
	int j = 0;
	Node* pTree = NULL;

	// Loop through pStruct4 data structure
	for (HeaderC* pStruct = pStruct4; pStruct; pStruct = pStruct->pNext) {
		for (i = 0; i < N; i++) {
			pObjectTemp = (Object10*)pStruct->ppObjects[i];
			if (pObjectTemp != NULL) {
				for (Object10* obj = pObjectTemp; pObjectTemp; pObjectTemp = pObjectTemp->pNext) {
					j++;
					pTree = InsertNode(pTree, pObjectTemp);
					printf("\n\t(Obj %d) PID: %s %lu ", j, pObjectTemp->pID, pObjectTemp->Code);

				}
			}
		}
	}
	printf("%d\n", j);
	printf("\nBinary tree complete\n");
	return pTree;
}

Stack* Push(Stack* pStack, void* pRecord)
{
	errno = 0;
	Stack* pNew;
	if (!pRecord)
	{
		errno = EINVAL;
		return pStack;
	}
	pNew = (Stack*)malloc(sizeof(Stack));
	pNew->pObject = pRecord;
	pNew->pNext = pStack;
	return pNew;
}

//Delete from Stack
Stack* Pop(Stack* pStack, void** pResult)
{
	Stack* p;
	if (!pStack)
	{
		*pResult = NULL;
		return pStack;
	}
	*pResult = (Object10*)pStack->pObject;
	p = pStack->pNext;
	free(pStack);
	return p;
}

//fn traverses tree symmetrical, sorted output (left-root-right)
void TreeTraversal(Node* pTree)
{
	printf("\n---------------------------------Printing Sorted Tree------------------------\n");
	int i = 1;
	Stack* pStack = 0;
	Node* p1 = pTree, * p2;
	if (!pTree) {
		return;
	}
	do {
		while (p1) {
			pStack = Push(pStack, p1);
			p1 = p1->pLeft;
		}
		pStack = Pop(pStack, (void**)&p2);
		printf("\n\t(Node %d) PID: %s  %dS", i++, ((Object10*)p2->pObject)->pID, ((Object10*)p2->pObject)->Code);
		p1 = p2->pRight;
	} while (!(!pStack && !p1));
}

//Node *DeleteTreeNode(Node *pTree, unsigned long int Code);