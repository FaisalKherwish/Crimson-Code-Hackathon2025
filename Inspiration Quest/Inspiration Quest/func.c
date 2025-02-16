#include "Header.h"

Node* gatherInspiration(Node** pList, char ss) 
{
	int random = rand() % 9 + 1; // Random number between 1 and 9
	Inspiration newInspiration = { .attributes = {.community = 0, .dailyLife = 0,.entertainment = 0,.ethos = 0,.nature = 0,.quality = 0,.tech = 0},.grouping = NULL,.quality = 0}; // Initialize all attributes to 0

	// Determine the type of inspiration based on the environment and random event
	if (ss == 'C') { // Club environment
		if (random > 3) {
			newInspiration.attributes.entertainment = 1;
			strcpy(newInspiration.grouping,"Entertainment");
		}
		else if (random == 2) {
			newInspiration.attributes.tech = 1; // Tech inspiration
			strcpy(newInspiration.grouping,"Technology");
		}
		else if (random == 1) {
			newInspiration.attributes.ethos = 1; // Ethos inspiration
			strcpy(newInspiration.grouping,"Ethos");
		}
	}
	else if (ss == 'F') { // Forest environment
		if (random > 5) {
			newInspiration.attributes.nature = 1;
			strcpy(newInspiration.grouping,"Nature");
		}
		else if (random == 3) {
			newInspiration.attributes.ethos = 1; // Ethos inspiration
			strcpy(newInspiration.grouping,"Ethos");
		}
	}
	else if (ss == 'O') { // Outskirts environment
		if (random > 4) {
			newInspiration.attributes.dailyLife = 1; // Daily life inspiration
			strcpy(newInspiration.grouping,"Daily Life");
		}
		else if (random == 2) {
			newInspiration.attributes.community = 1; // Community inspiration
			strcpy(newInspiration.grouping,"Community");
		}
	}
	else if (ss == 'D') { // Downtown environment
		if (random > 3) {
			newInspiration.attributes.entertainment = 1; // Entertainment inspiration
			strcpy(newInspiration.grouping,"Entertainment");
		}
		else if (random == 2) {
			newInspiration.attributes.tech = 1; // Tech inspiration
			strcpy(newInspiration.grouping,"Technology");
		}
	}

	newInspiration.quality = computeQuality();

	// Create a new node with the generated inspiration
	Node* newNode = createNode(newInspiration);

	if (newNode == NULL) {
		printf("Failed to create a new node.\n");
		return NULL;
	}
	// Insert the new node into the backpack (assuming backPack is a linked list)
	insertInList(pList, newInspiration);

	return newNode;
}

int computeQuality()
{
	int random = rand();
	random = random % 5 + 1;
	return random;
}

int computeSale(double multiplier)
{
	int random = rand();
	double sale;
	random = random % 10 + 1;
	random = random + 15;
	sale = random * multiplier;
	return sale;
}

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

void transferData(Node** pList1, Node** pList2, Node* pMem)
{
	Node* pCur = *pList1, * pCur2 = *pList2;

	if (pMem != NULL)
	{
		pCur->pPrev->pNext = pCur->pNext;
		pCur->pNext->pPrev = pCur->pPrev;

		if (pCur2 == NULL)
		{
			*pList2 = pMem;
		}
		else
		{
			pMem->pNext = pCur;
			pCur->pPrev = pMem;
			*pList2 = pMem;
		}
	}
}

void deleteList(Node** pList)
{
	Node* pCur = *pList;
	Node* pNext = NULL;
	while (pCur != NULL) {
		pNext = pCur->pNext;
		free(pCur);
		pCur = pNext;
	}
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

		if (count > maxCount)
		{
			maxCount = count;
			strcpy(mostFrequentGroup, pCur->data.grouping);
		}

		pCur = pCur->pNext;
	}

	return groupingValue(mostFrequentGroup, maxCount, size) + qualityCalculate(pList) + 1;
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

void printMenu()
{
	printf("Welcom To an Inspiration Quest\n\n");
	printf("Within this game, you will embark on a interactive adventure in which you traverse numerous enviorments\n");
	printf("in hopes to find inspiration and eventually create an artpiece that the user will sell for gold\n");
	printf("to hopefully reach the quota for the day!\n");
	system("pause");
	system("cls");
}

void enviormentPicker(Node** pList)
{
	int val = rand() % 4 + 1;
	int playerChoice = 0, option = 0;

	printf("Your Selected Environment for Today is...");
	system("pause");
	system("cls");


	switch (val)
	{
	case 1:

		printf("the Forest!");
		system("pause");
		system("cls");

		playerChoice = rand() % 5 + 1;

		switch (playerChoice)
		{
		case 1:
			printf("While you follow a trail through a nice lush forest,\n");
			printf("you spot a family of bunnies gathering plants and berries. The baby bunny appears to be injured.\n"); //+Nature Inspo
			printf("What do you do? (Type the represented integer)\n");
			printf("1.Help it\n");
			printf("2.Leave it\n");
			scanf(" %d", &option);
			gatherInspiration(pList, 'F');
			break;
		case 2:
			printf("You see a nice bush of exotic flowers and decide to take a nice sniff\n");
			printf("As you exhale, your face seems to be very satisfied\n"); 
			gatherInspiration(pList, 'F');
			break;
		case 3:
			printf("You see two big ferocious brown bears fighting for a cave to call home.\n");
			printf("This ferocious ignited a spark within your heart\n"); 
			gatherInspiration(pList, 'F');
			break;
		case 4:
			printf("About an hour into the hike, you stumble upon a nice lake encapsulated in a field of serenity.\n");
			printf("You feel extremely peacful and your heart is content\n");
			gatherInspiration(pList, 'F');
			break;
		case 5:
			printf("You hear a beautiful chirping sound only to look up and see\n");
			printf("two birds singing to one another.\n"); 
			gatherInspiration(pList, 'F');
			break;
		}

		system("pause");
		system("cls");

		break;
	case 2:

		printf("the Outskirts!\n");
		system("pause");
		system("cls");
		playerChoice = rand() % 5 + 1;

		switch (playerChoice)
		{

		case 1:
			printf("As you pass through a farm, you see a sheep that has toppled over and can't get up because it's too heavy.\n");
			printf("Do you help it?\n");
			printf("1.Yes\n"); 
			printf("2.No\n"); 
			scanf(" %d", &option);
			gatherInspiration(pList, 'O');
			break;
		case 2:
			printf("As you take a tour of a farm, you smell a very foul stench...only to realize it's cow poop.\nYou feel sorry for the farmers that have to smell it every day\n");//+Daily Life
			gatherInspiration(pList, 'O');
			break;
		case 3:
			printf("On a tour of a farm, the farmer asks if you want to milk a cow.\n");
			printf("You oblige and proceed to milk a cow.\n");
			printf("You feel invigorated\n"); 
			gatherInspiration(pList, 'O');
			break;
		case 4:
			printf("When on a tour of a farm, the farmer lets you know\n");
			printf("that one of his duties is to neuter the animals.\n");
			printf("You feel blessed that you never wanted to work on a farm.\n"); 
			gatherInspiration(pList, 'O');
			break;

		case 5:
			printf("On the tour of a farm, A PIG ESCAPES FROM ITS PEN\n");
			printf("And the farmer gives you the task to chase it and bring it back because he's too old\n");
			printf("You run around for what feels like forever (like 5 minutes)\n"); 
			gatherInspiration(pList, 'O');
			break;
		}

		system("pause");
		system("cls");
		break;
	case 3:
		printf("the Downtown Area!\n");
		system("pause");
		system("cls");
		playerChoice = rand() % 4 + 1;

		switch (playerChoice)
		{

		case 1:
			printf("As you walk down a block, you peer into an alley way and see 3 homeless people fighting over a honeybun.\n");
			printf("You feel blessed that you escaped poverty and homelessness\n");
			gatherInspiration(pList, 'D');
			break;
		case 2:
			printf("You enter into a gas station too grab a quick snack \n");
			printf("only to have walked into a misfortunate scenario of the store owner getting robbed.\n");
			printf("In the moment you feel scared but after its over you feel relieved...\n");
			gatherInspiration(pList, 'D');
			break;
		case 3:
			printf("You take the subway to get to a different part of a the city your are in, \n");
			printf("only too see a group of people jumping over the turnstile to avoid paying for a metro pass.\n");
			printf("You think to yourself,'What terrible design'\n"); 
			gatherInspiration(pList, 'D');
			break;
		case 4:
			printf("You walk through a nice park that you saw while walking around the city.\n");
			printf("You see multiple drunk men doing absurd things that can't be named...\n");
			gatherInspiration(pList, 'D');
			break;
		}
		system("pause");
		system("cls");
		break;
	case 4:

		printf("the Club!");
		system("pause");
		system("cls");


		playerChoice = rand() % 4 + 1;

		switch (playerChoice)
		{

		case 1:
			printf("You arrive at a well known club in the city you reside in.\n");
			printf("The vibes are perfect and all you wanna do is dance.\n");
			printf("So, you dance until the sun comes up\n");
			gatherInspiration(pList, 'C');
			break;
		case 2:
			printf("At the club, you can feel the music shaking the ground.\n");
			printf("And no it's not the 5 tequila shots you just had (You Think)\n");
			gatherInspiration(pList, 'C');
			break;
		case 3:
			printf("You see a pretty lady at the bar and buy her a drink from a different table.\n");
			printf("Her boyfriend takes the drinks and mouths 'Cheers' to you.\n");
			printf("You wanna go home but don't wanna look like a softie.\n");
			gatherInspiration(pList, 'C');
			break;
		case 4:
			printf("It's late at night and a slow song comes on for whatever reason,\n");
			printf("Then you realize today is Valentine's Day!\n");
			printf("You and the rest of the single people in the club shine your flashlights in unison to give a nice ambiance to the dancers.\n");
			gatherInspiration(pList, 'C');
			break;

		}
		system("pause");
		system("cls");
		break;
	}
}

void paint(Node** pList1, Node** pList2)
{
	Node* pCur = *pList1;
	int option = 0, size = 0;

	while (pCur != NULL)
	{
		printf("Inspiration: %d", size + 1);
		printNode(pCur);
		pCur = pCur->pNext;
		size++;
	}

	do {
		printf("Select inspiration you wish to paint onto the canvas (1-%d)\n", size + 1);
		printf("Selection must be valid\n");
		scanf(" %d", &option);
	} while (option > 1 && option < size + 1);
	
	pCur = *pList1;

	for (int i = 0; i < option - 1; i++)
	{
		pCur = pCur->pNext;
	}

	transferData(pList1, pList2, pCur);

}

int game() 
{
	Node* backPack = NULL;  // The player's backpack for storing inspiration.
	Node* canvas = NULL; // painting list
	Area currentArea = { 'F' }; // Start in the Forest environment, for example.
	int quota = 100; // Target quota for the player's art sale.
	double totalEarnings = 0.0, profit = 0.0;
	int day = 5, option = 0, count = 0;

	// Game introduction
	printMenu();

	while (day > 0) 
	{
		// Pick the environment for the day
		do
		{
			printf("Day %d\n", day);
			printf("Target Quota: %d\n", quota);
			printf("Current Earnings: %.2lf\n", totalEarnings);
			printf("What do you do?\n");
			printf("(1) Head Out\n(2) Paint and Sell\n(3) Quit\n");
			scanf(" %d", &option);

			switch (option)
			{
			case 1: enviormentPicker(&backPack);
				day--;
				break;
			case 2: printf("You lift your brush and ready your canvas.\n");
				printf("(1)Recall your memories\n(2)Stop\n");
				scanf(" %d", &option);
				if (option == 1)
				{
					do
					{
						paint(&backPack, &canvas);
						count++;
						printf("Continue to recall?\n");
						printf("(1)Yes\n(2)Stop and Paint\n");
						scanf(" %d", &option);
						if (count == 3 && option == 1) printf("Your mind fogs, better paint before this inspiration is forgotten\n");
					} while (option < 3 && option > 0 && option != 2 && count <= 3);

					profit = computeSale((double)lookForGrouping(canvas));
					printf("Current Cash: %d", totalEarnings);
					totalEarnings += profit;
					if (totalEarnings > 30) printf("What a great painting! You set it up for sale\n");
					else if (totalEarnings > 20) printf("You are proud of what you've made You set it up for sale\n");
					else printf("It may not be your best work. You set it up for sale\n");
					system("pause");
					printf("Sold! You earned: %lf", profit);
					deleteList(&canvas);
				}
				break;
			case 3: return 0;
			}

		} while (option != 3);

		if (day == 1)
		{
			printf("Last day to gather money for rent.\nNo Pressure.");
		}
	}

	

	if (totalEarnings > quota)
	{
		printf("Congrats, you've paid your dues on time.\nPrepare for the next month\n");
		return 1;
	}
	else
	{
		printf("Life wasn't the best to you, but at least you did what you loved.\n GAME OVER\n");
		return 0;
	}

}
