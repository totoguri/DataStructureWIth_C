// Data Structure
// Circular Linked List
// 26, Oct, 2021

#ifndef _CIRCULARLIST_
#define _CIRCULARLIST_

typedef struct CircularListNodeType {
	int data;
	struct CircularListNodeType* pLink;
} CircularListNode;

typedef struct CircularListType {
	int currentElementCount;
	CircularListNode* pLink;	// head pointer
} CircularList;

CircularList* createCircularList();
void deleteCircularList(CircularList* pList);
int addCLElement(CircularList* pList, int position, CircularListNode element);
int removeCLElement(CircularList* pList, int position);
void clearCircularList(CircularList* pList);
int getCircularListLength(CircularList* pList);
CircularListNode* getCLElement(CircularList* pList, int position);
void displayCircularList(CircularList* pList);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE 1
#define FALSE 0

#endif