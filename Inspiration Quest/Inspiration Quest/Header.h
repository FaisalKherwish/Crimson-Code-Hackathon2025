#ifndef INSPIRATION_H
#define INSPIRATION_H
#include <stdio.h>
#include <ctype.h>
#include <string.h>


//computeSale(double multiplier);
typedef struct artPiece {
	int value;
} ArtPiece;
typedef struct node
{
	ArtPiece data;
	struct node* pNext;
} Node;

typedef struct area {
	char envrionment; //forest
	//char O;  //ourskirts
	//char D;  //downtown
	//char C; //club
} Area;


typedef struct attributes {
	int community;
	int dailyLife;
	int nature;
	int tech;
	int entertainment;
	int ethos;
	int quality;
} Attributes;


typedef struct inspiration
{
	int quality;
	char* grouping;
	Attributes attributes;
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
void printNode(Node* pCur);
double lookForGrouping(Node* pList);
double groupingValue(char* grouping, int maxCount, int size);
double qualityCalculate(Node* pList);
computeSale(double multiplier);
void printMenu();
void enviormentPicker();


#endif
