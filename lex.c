#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUT_SIZE 80

typedef struct {
	int size;
	char entries[INPUT_SIZE][INPUT_SIZE];
} TabVar;

TabVar tabVar = {0};
char input[INPUT_SIZE];
char tempS[INPUT_SIZE] = "";
int cursor = 0;
int action = 0;
int tempN;

void act(void);
void TabVar_ls(void);

int main(void)
{
	printf("Input: ");
	fgets(input, INPUT_SIZE, stdin);
	goto e0;

aceita:
	printf("\nInput aceito\n");
	TabVar_ls();
	exit(EXIT_SUCCESS);

rejeita:
	printf("\nInput rejeitado\n");
	exit(EXIT_FAILURE);

e0:
	act();
	if (isalpha(input[cursor])) {
		cursor++; //consome input
		action = 1;
		goto e1;
	} else if (isspace(input[cursor]) && input[cursor] != '\n') {
		cursor++;
		action = 0;
		goto e0;
	} else if (isdigit(input[cursor])) {
		cursor++;
		action = 4;
		goto e2;
	} else if (input[cursor] == '\n') {
		goto aceita;
	} else {
		goto rejeita;
	}

e1:
	act();
	if (isalnum(input[cursor])) {
		cursor++;
		action = 2;
		goto e1;
	} else {
		action = 3;
		goto e0;
	}

e2:
	act();
	if (isdigit(input[cursor])) {
		cursor++;
		action = 5;
		goto e2;
	} else {
		action = 6;
		goto e0;
	}

}

int TabVar_entry(char *string)
{
	for (int i = 0; i < tabVar.size; i++)
		if (strcmp(tabVar.entries[i], string) == 0)
			return i;

	return -1;
}

int TabVar_add_entry(char *string)
{
	strcpy(tabVar.entries[tabVar.size], string);
	return tabVar.size++;
}

void TabVar_ls()
{
	for (int i = 0; i < tabVar.size; i++)
		printf("V(%d) = %s\n", i, tabVar.entries[i]);
}

void act()
{
	int entry;
	char c = input[cursor - 1];
	char *strend;

	switch (action) {
	case 1:
		tempS[0] = c;
		tempS[1] = '\0';
		break;
	case 2:
		strend = strchr(tempS, '\0');
		*strend = c;
		*(strend + 1) = '\0';
		break;
	case 3:
		entry = TabVar_entry(tempS);
		if (entry == -1)
			entry = TabVar_add_entry(tempS);
		printf("V(%d)", entry);
		break;
	case 4:
		tempN = (c - '0');
		break;
	case 5:
		tempN = tempN * 10 + (c - '0');
		break;
	case 6:
		printf("N(%d)", tempN);
		break;
	}
}

