#pragma once
#ifndef INSPIRATION_H
#define INSPIRATION_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


//computeSale(double multiplier);
typedef struct artPiece 
{
	int value;
} ArtPiece;

typedef struct area 
{
	char envrionment; //forest
	//char O;  //ourskirts
	//char D;  //downtown
	//char C; //club
} Area;


typedef struct attributes 
{
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
	char grouping[50];
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
Node* gatherInspiration(Node** pList, char ss);
int computeQuality();
void transferData(Node** pList1, Node** pList2, Node* pMem);
void deleteList(Node** pList);
void printNode(Node* pCur);
double lookForGrouping(Node* pList);
double groupingValue(char* grouping, int maxCount, int size);
double qualityCalculate(Node* pList);
int computeSale(double multiplier);
void printMenu();
void enviormentPicker(Node** pList);
void paint(Node** pList1, Node** pList2);
int game(int targetQuota);


#endif
