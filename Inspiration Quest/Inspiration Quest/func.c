#include "Header.h"

Node* gatherInspiration(Attributes backPack[], Area ss) {
	srand(time(NULL)); // Seed the random number generator
	int random = rand() % 9 + 1; // Random number between 1 and 9
	Inspiration newInspiration = { 0 }; // Initialize all attributes to 0

	// Determine the type of inspiration based on the environment and random event
	if (ss.envrionment == 'C') { // Club environment
		if (random > 3) {
			newInspiration.attributes.entertainment = 1;
		}
		else if (random == 2) {
			newInspiration.attributes.tech = 1; // Tech inspiration
		}
		else if (random == 1) {
			newInspiration.attributes.ethos = 1; // Ethos inspiration
		}
	}
	else if (ss.envrionment == 'F') { // Forest environment
		if (random > 5) {
			newInspiration.attributes.nature = 1;
		}
		else if (random == 3) {
			newInspiration.attributes.ethos = 1; // Ethos inspiration
		}
	}
	else if (ss.envrionment == 'O') { // Outskirts environment
		if (random > 4) {
			newInspiration.attributes.dailyLife = 1; // Daily life inspiration
		}
		else if (random == 2) {
			newInspiration.attributes.community = 1; // Community inspiration
		}
	}
	else if (ss.envrionment == 'D') { // Downtown environment
		if (random > 3) {
			newInspiration.attributes.entertainment = 1; // Entertainment inspiration
		}
		else if (random == 2) {
			newInspiration.attributes.tech = 1; // Tech inspiration
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
	insertInList((Node**)&backPack, newInspiration);

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
	Node* pCur = *pList, * pPrev = NULL;

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


void enviormentPicker()
{
	srand(time(NULL));
	int val = rand() % 4 + 1;
	int playerChoice = 0;

	printf("Your Selected Enviorment for Today is...");
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
			printf("While you follow a trail through a nice lush forset, ");
			printf("you spot a family of bunnies gathering plants and berries to eat and the baby bunny appears to be injured."); //+Nature Inspo
			printf("\n\nDo you help it? (Type the represented integer)\n");
			printf("1.Yes\n"); //Yes they get ethos inspo
			printf("2.N0\n"); // They don't get it
			break;
		case 2:
			printf("You see a nice bush of exotic flowers and decide to take a nice sniff");
			printf("\nAs you exhale, your face seems to be very satisfied\n"); // +nature inspo
			break;
		case 3:
			printf("You see two big ferocious brown bears fighting for a cave to call home.\n");
			printf("This ferocious ignited a spark within your heart"); // Plus inspo
			break;
		case 4:
			printf("About an hour into the hike, you stumble upon a nice lake encapsulated in a field of serenity.\n");
			printf("You feel extremely peacful and your heart is content\n");//Plus ethos
			break;
		case 5:
			printf("You hear a beautiful chirping sound only to look up and see\n");
			printf("two birds singing to one another.\n"); //Plus Inspo
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
			printf("As you pass through a farm, you see a sheep that has toppeled over and can't get up\n");
			printf("because it's too heavy.\n");
			printf("Do you help it?\n");
			printf("1.Yes\n"); //THey get the inspiration for community
			printf("2.No\n"); // They get nothing
			break;
		case 2:
			printf("As you take a tour of a farm, you smell a very foul stench...only to realize it's cow poop.\nYou feel sorry for the farmers that have to smell it every day\n");//+Daily Life
			break;
		case 3:
			printf("On a tour of a farm, the farmer asks if you want to milk a cow.");
			printf("You ablige and proceed to milk a cow.\n");
			printf("You feel invigorated\n"); //+DL
			break;
		case 4:
			printf("When on a tour of a farm, the farmer lets you know\n");
			printf("that one of his duties is to neuter the animals.\n");
			printf("You feel blessed that you never wanted to work on a farm.\n"); //+DL
			break;

		case 5:
			printf("On the tour of a farm, A PIG ESCAPES FROM ITS PEN\n");
			printf("And the farmer gives you the task to chase it and bring it back because he's too old\n");
			printf("You run arorund for what feels like forever (like 5 minutes)\n"); //+entertainment inspo
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
			printf("As you walk down a block, you peer into an alley way and see 3 homeless people fighting over a hunnybun.\n");
			printf("You feel blessed that you escaped poverty and homelessness\n");//+entertainment inspo
			break;
		case 2:
			printf("You enter into a gas station too grab a quick snack ");
			printf("only to have walked into a misfortunate scenario of the store owner getting robbed.\n");
			printf("In the moment you feel scared but after its over you feel relieved...\n");//+DL
			break;
		case 3:
			printf("You take the subway to get to a different part of a the city your are in, ");
			printf("only too see a group of people jumping over the turnstile to avoid paying for a metro pass.\n");
			printf("You think to yourself,'What terrible design'\n"); //+Tech inspo
			break;
		case 4:
			printf("You walk through a nice park that you saw while walking around the city.\n");
			printf("You see multiple drunk men doing absurd things that can't be named...\n");//+ent
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
			printf("So, you dance until the sun comes up\n");//+Ent
			break;
		case 2:
			printf("At the club, you can feel the music shaking the ground.\n");
			printf("And no it's not the 5 tequila shots you just had (You Think)\n");//+Tech
			break;
		case 3:
			printf("You see a pretty lady at the bar and buy her a drink from a different table.\n");
			printf("Her boyfriend takes the drinks and mouths 'Cheers' to you.\n");
			printf("You wanna go home but don't wanna look like a softie.\n"); //+Ethos
			break;
		case 4:
			printf("It's late at night and a slow song comes on for whatever reason,\n");
			printf("Then you realize today is Valentine's Day!\n");
			printf("You and the rest of the single people in the club shine your flashlights in unison to give a nice ambiance to the dancers.\n"); //+Tech
			break;

		}
		system("pause");
		system("cls");

		break;
	}
}

void game() {
	Node* backPack = NULL;  // The player's backpack for storing inspiration.
	Area currentArea = { 'F' }; // Start in the Forest environment, for example.
	int quota = 100; // Target quota for the player's art sale.
	double totalEarnings = 0.0;
	int day = 1;

	// Game introduction
	printMenu();

	while (totalEarnings < quota) {
		printf("Day %d\n", day);
		printf("Target Quota: %d\n", quota);
		printf("Current Earnings: %.2lf\n", totalEarnings);

		// Pick the environment for the day
		enviormentPicker();

		// Gather inspiration based on environment
		Node* inspiration = gatherInspiration(backPack, currentArea);
		


		// End of day
		printf("\n--- End of Day %d ---\n", day);
		day++;
		system("pause");
		system("cls");
	}

	// Player wins if they have enough earnings
	printf("Congratulations! You've reached your quota of %.2lf and won the game!\n", quota);
	deleteList(&backPack);
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
