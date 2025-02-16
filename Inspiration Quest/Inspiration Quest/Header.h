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

Node* createNode(Inspiration newData);
void insertInList(Node** pList, Inspiration newData);
void transferData(Node** pList, Node* pMem);
void deleteList(Node** pList);
double lookForGrouping(Node* pList);
double groupingValue(char* grouping, int maxCount, int size);
double qualityCalculate(Node* pList);
computeSale(double multiplier);

#endif


















#endif

