#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUT_SIZE 80
#define RWORDS 9

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
char tempC;
const char const * tabP[RWORDS] = {
	"IF",
	"THEN",
	"ELSE",
	"GOTO",
	"LET",
	"END",
	"PRINT",
	"READ",
	"OF"
};

void act(void);
void TabVar_ls(void);
void machine(void);
void tabP_ls(void);

int main(void)
{
	while (fgets(input, INPUT_SIZE, stdin)) {
		machine();
	}
	printf("\n");
	TabVar_ls();
	printf("\n");
	tabP_ls();
	return 0;
}

void machine()
{
	char c;
	cursor = 0;
	action = 0;
	goto e0;

e0:
	act();
	c = input[cursor];
	if (c == '\0') {
		return;
	} else if (isalpha(c)) {
		cursor++; // consome input
		action = 1;
		goto e1;
	} else if (isspace(c) && c != '\n') {
		cursor++;
		action = 0;
		goto e0;
	} else if (isdigit(c)) {
		cursor++;
		action = 4;
		goto e2;
	} else if (c == '%') {
		cursor++;
		action = 0;
		goto e6;
	} else if (c == ':') {
		cursor++;
		action = 0;
		goto e3;
	} else if (ispunct(c)) {
		cursor++;
		action = 9;
		goto e5;
	} else if (c == '\n') {
		printf("\n");
		return;
	} else {
		goto rejeita;
	}

aceita:
	printf("\nInput aceito\n");
	TabVar_ls();
	exit(EXIT_SUCCESS);

rejeita:
	printf("\nInput rejeitado\n");
	exit(EXIT_FAILURE);

e1:
	act();
	c = input[cursor];
	if (isalnum(c)) {
		cursor++;
		action = 2;
		goto e1;
	} else {
		action = 3;
		goto e0;
	}

e2:
	act();
	c = input[cursor];
	if (isdigit(c)) {
		cursor++;
		action = 5;
		goto e2;
	} else {
		action = 6;
		goto e0;
	}

e3:
	act();
	c = input[cursor];
	if (c == '=') {
		cursor++;
		action = 8;
		goto e0;
	} else {
		action = 7;
		goto e0;
	}

e5:
	act();
	action = 10;
	goto e0;

e6:
	act();
	while (input[cursor] != '\n' && input[cursor] != '\0')
		cursor++;
	action = 0;
	goto e0;
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

void tabP_ls()
{
	for (int i = 0; i < RWORDS; i++)
		printf("P(%d) = %s\n", i, tabP[i]);
}

int rword_entry(char *string)
{
	for (int i = 0; i < RWORDS; i++)
		if (strcmp(tabP[i], string) == 0)
			return i;
	return -1;
}

void act()
{
	int entry;
	char c;
	char *strend;

	if (cursor > 0) {
		c = input[cursor - 1];
	}

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
		entry = rword_entry(tempS);
		if (entry != -1) {
			printf("P(%d)", entry);
		} else {
			entry = TabVar_entry(tempS);
			if (entry == -1)
				entry = TabVar_add_entry(tempS);
			printf("V(%d)", entry);
		}
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
	case 7:
		printf(":");
		break;
	case 8:
		printf(":=");
		break;
	case 9:
		tempC = c;
		break;
	case 10:
		printf("%c", c);
		break;
	}
}
