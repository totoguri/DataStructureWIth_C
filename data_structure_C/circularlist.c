#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circularlist.h"

int addCLElement(CircularList* pList, int position, CircularListNode element) {
	int ret = FALSE;
	int i = 0;
	CircularListNode* pPreNode = NULL;
	CircularListNode* pNewNode = NULL;
	CircularListNode* pLastNode = NULL;

	if (pList != NULL) {
		if (position >= 0 && position <= pList->currentElementCount) {
			pNewNode = (CircularListNode*)malloc(sizeof(CircularListNode));
			if (pNewNode == NULL) {
				printf("Error - memory for addCLElement()\n");
				return ret;
			}

			*pNewNode = element;
			pNewNode->pLink = NULL;

			if (position == 0) {
				if (pList->currentElementCount == 0) {
					pList->pLink = pNewNode;
					pNewNode->pLink = pNewNode;
				}
				else {
					pLastNode = pList->pLink;	// 출발점. 첫번째 노드 이름을 단순히 pLastNode로 설정. 밑에 while에서 돌면서 결국 pLastNode가 진짜 마지막 노드가 됨.
					while (pLastNode->pLink != pList->pLink) {	// 마지막 노드 직전 노드까지 루프. 마지막 노드 다음은 첫번째 노드.
						pLastNode = pLastNode->pLink;	// 여기서 pLastNode가 최종적으로 마지막 노드로 확정.
					}
					pList->pLink = pNewNode;
					pNewNode->pLink = pLastNode->pLink;
					pLastNode->pLink = pNewNode;
				}
			}
			else {
				pPreNode = pList->pLink;
				for (i = 0; i < position - 1; i++) {
					pPreNode = pPreNode->pLink;
				}
				pNewNode->pLink = pPreNode->pLink;
				pPreNode->pLink = pNewNode;
			}
			pList->currentElementCount++;
			ret = TRUE;
		}
		else {
			printf("Error, position - [%d] addCLElement()\n", position);
		}
	}
	return ret;
}

int removeCLElement(CircularList* pList, int position) {
	int ret = FALSE;
	int i = 0, arrayCount = 0;
	CircularListNode* pPreNode = NULL;
	CircularListNode* pDelNode = NULL;
	CircularListNode* pLastNode = NULL;

	if (pList != NULL) {
		arrayCount = getCircularListLength(pList);
		if (position >= 0 && position < arrayCount) {
			if (position == 0) {
				pDelNode = pList->pLink;
				if (arrayCount == 1) {
					free(pDelNode);
					pList->pLink = NULL;
				}
				else {
					pLastNode = pList->pLink;
					while (pLastNode->pLink != pList->pLink) {
						pLastNode = pLastNode->pLink;
					}
					pLastNode->pLink = pDelNode->pLink;
					pList->pLink = pDelNode->pLink;
					free(pDelNode);
				}
			}
			else {
				pPreNode = pList->pLink;
				for (i = 0; i < position - 1; i++) {
					pPreNode = pPreNode->pLink;
				}
				pDelNode = pPreNode->pLink;
				pPreNode->pLink = pDelNode->pLink;
				free(pDelNode);
			}
			pList->currentElementCount--;
			ret = TRUE;
		}
		else {
			printf("Error, position - [%d] removeCLElement()\n", position);
		}
	}
	return ret;
}

CircularListNode* getCLElement(CircularList* pList, int position) {
	int i = 0;
	CircularListNode* pNode = NULL;
	if (pList != NULL) {
		if (position >= 0 && position < pList->currentElementCount) {
			pNode = pList->pLink;
			for (i = 0; i < position; i++) {
				pNode = pNode->pLink;
			}
		}
	}
	return pNode;
}

CircularList* createCircularList() {
	CircularList* pReturn = NULL;
	int i = 0;

	pReturn = (CircularList*)malloc(sizeof(CircularList));
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(CircularList));
	}
	else {
		printf("Error, memory for createCircularList()\n");
		return NULL;
	}
	return pReturn;
}

void displayCircularList(CircularList* pList) {
	int i = 0;
	if (pList != NULL) {
		printf("Number of values: %d\n", pList->currentElementCount);
		for (i = 0; i < pList->currentElementCount; i++) {
			printf("[%d] -> %d\n", i, getCLElement(pList, i)->data);
		}
	}
	else {
		printf("None of value\n");
	}
}

int getCircularListLength(CircularList* pList) {
	int ret = 0;
	if (pList != NULL) {
		ret = pList->currentElementCount;
	}
	return ret;
}

void deleteCircularList(CircularList* pList) {
	int i = 0;
	if (pList != NULL) {
		clearCircularList(pList);
		free(pList);
	}
}

void clearCircularList(CircularList* pList) {
	if (pList != NULL) {
		while (pList->currentElementCount > 0)
			removeCLElement(pList, 0);
	}
}