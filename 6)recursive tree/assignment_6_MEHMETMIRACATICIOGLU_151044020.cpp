#include <stdio.h>

void printTree(char * currChar, int * parants);

int main(){
	int parants = 0;
	char inputStr[100];
	FILE * input = fopen("input.txt", "rt");
	fscanf(input, "%s", inputStr);
	printTree(inputStr, &parants);
	return 0;
}

void printTree(char * currChar, int * parants){
	int i = 0, newParants;
	if(*currChar != '\0'){
		if(*currChar == '(')
			(*parants)++;
		else if(*currChar == ')')
			(*parants)--;
		else if(*currChar != ','){
			for(i=0; i<*parants; i++)
				printf("-");
			printf("%c\n", *currChar);
		}
		newParants = *parants;
		printTree(currChar+1, &newParants);
	}
}
