#ifndef INSPIRATION_H
#define INSPIRATION_H

typedef struct inspiration 
{
	int community;
	int dailyLife;
	int nature;
	int tech;
	int entertainment;
	int quality;
} Inspiration;

typedef struct artPiece 
{
	int value;
} ArtPiece;

typedef struct inspiration
{
	int quality;
	char* grouping;
}Inspiration;

typedef struct node
{
	Inspiration data;
	struct node* pNext;
	struct node* pPrev;
}Node;

computeSale(double multiplier);
Node* createNode(Inspiration newData);
void insertInList(Node** pList, Inspiration newData);
void transferData(Node** pList, Node* pMem);
void deleteList(Node** pList);
void printNode(Node* pCur);
double lookForGrouping(Node* pList);
double groupingValue(char* grouping, int maxCount, int size);
double qualityCalculate(Node* pList);
computeSale(double multiplier);
void printMenu();
void enviormentPicker();




















#endif

