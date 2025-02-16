#include "Header.h

Node* createNode(Inspiration newData)
{
	Node* pMem = malloc(sizeof(Node));

	if (pMem != NULL)
	{
		pMem->data = newData;
		pMem->pNext = NULL;
		pMem->pPrev = NULL;
	}

	return pMem;
}

void insertInList(Node** pList, Inspiration newData)
{
	Node* pCur = *pList, * pMem = createNode(newData);

	if (pMem != NULL)
	{
		if (pCur == NULL)
		{
			*pList = pMem;
		}
		else
		{
			pMem->pNext = pCur;
			pCur->pPrev = pMem;
			*pList = pMem;
		}
	}
}

void transferData(Node** pList, Node* pMem)
{
	Node* pCur = *pList;

	if (pMem != NULL)
	{
		if (pCur == NULL)
		{
			*pList = pMem;
		}
		else
		{
			pMem->pNext = pCur;
			pCur->pPrev = pMem;
			*pList = pMem;
		}
	}
}

void deleteList(Node** pList)
{
	Node* pCur = *pList, *pPrev = NULL;

	while (pCur->pNext != NULL)
	{
		pCur = pCur->pNext;
		pPrev = pCur;
	}

	while (pCur != pList)
	{
		free(pCur);
		pCur = pPrev;
		pPrev = pPrev->pPrev;
	}

	free(pCur);
	*pList = NULL;
}

void printNode(Node* pCur)
{
	printf("Quality: %lf\n", pCur->data.quality);
	printf("Type: %s", pCur->data.grouping);
}

double lookForGrouping(Node* pList)
{
	Node* pCur = pList;

	int size = 0;


	while (pCur != NULL)
	{
		size++;
	}

	int count = 0, maxCount = 0;
	char* mostFrequentGroup = "";

	for (int i = 0; i < size; i++) 
	{
		count = 0;

		for (int j = 0; j < size; j++) 
		{
			if (pCur->pNext != NULL && strcmp(pCur->data.grouping, pCur->pNext->data.grouping) == 0)
			{
				count++;
			}
		}

		if (count > maxCount) {
			maxCount = count;
			strcpy(mostFrequentGroup, pCur->data.grouping);
		}

		pCur = pCur->pNext;
	}
	
	return groupingValue(mostFrequentGroup, maxCount, size) + qualityCalculate(pList);
	
}

double groupingValue(char* grouping, int maxCount, int size)
{
	double group = 0.0, countValue = 0.0, sizeValue = 0.0;

	if (strcmp(grouping, "Community") == 0) group = 0.25;
	if (strcmp(grouping, "Daily Life") == 0) group = 0.2;
	if (strcmp(grouping, "Nature") == 0) group = 0.4;
	if (strcmp(grouping, "Technology") == 0) group = 0.3;
	if (strcmp(grouping, "Entertainment") == 0) group = 0.3;
	if (strcmp(grouping, "Ethos") == 0) group = 0.6;

	if (maxCount == 2) countValue = 0.3;
	else if (maxCount == 3) countValue = 0.6;

	if (sizeValue == 1) sizeValue = 0.1;
	else if (sizeValue == 2) sizeValue = 0.2;
	else sizeValue = 0.3;

	return sizeValue + group + countValue;	
}

double qualityCalculate(Node* pList)
{
	Node* pCur = pList;
	double qualityValue = 0.0;

	while (pCur != NULL)
	{
		qualityValue += pCur->data.quality;
		pCur = pCur->pNext;
	}

	return qualityValue;
}
