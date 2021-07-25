#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 123000

int convertToBigram(char firstP, char secondP);
void fileToBigramArr(char filename[40], int bigramArr[SIZE]);
double compareBigrammArrs(int bigramArr[SIZE], int bigramArrX[SIZE]);

int main(){
	int i, bigramArr[SIZE], bigramArrX[SIZE];
	
	for(i=0; i<SIZE; i++)
		bigramArr[i] = 0, bigramArrX[i] = 0;

	fileToBigramArr("language_x.txt", bigramArrX);

	fileToBigramArr("language_1.txt", bigramArr);
	printf("%f\n", compareBigrammArrs(bigramArr, bigramArrX));

	for(i=0; i<SIZE; i++)
		bigramArr[i] = 0;
	fileToBigramArr("language_2.txt", bigramArr);
	printf("%f\n", compareBigrammArrs(bigramArr, bigramArrX));
	
	for(i=0; i<SIZE; i++)
		bigramArr[i] = 0;
	fileToBigramArr("language_3.txt", bigramArr);
	printf("%f\n", compareBigrammArrs(bigramArr, bigramArrX));
	
	for(i=0; i<SIZE; i++)
		bigramArr[i] = 0;
	fileToBigramArr("language_4.txt", bigramArr);
	printf("%f\n", compareBigrammArrs(bigramArr, bigramArrX));

	for(i=0; i<SIZE; i++)
		bigramArr[i] = 0;
	fileToBigramArr("language_5.txt", bigramArr);
	printf("%f\n", compareBigrammArrs(bigramArr, bigramArrX));

	return 0;
}

int convertToBigram(char firstP, char secondP){
	int result = 0, firstPart, secondPart;
	firstPart = (int)firstP, secondPart = (int)secondP;
	if(secondPart >= 100) firstPart *= 1000;
	else firstPart *= 100;
	result += firstPart + secondPart;
	return result;
}

void fileToBigramArr(char filename[40], int bigramArr[SIZE]){
	FILE * inputFile = fopen(filename, "rt");
	char tempString[50], allStr[2], emptStr[2] = " ";
	int i, wCnt = 0;
	allStr[0] = '\0';
	while(fscanf(inputFile, "%s", tempString) != EOF){
		if(wCnt != 0)
			strcpy(allStr, " ");
		strcat(allStr, tempString);
		strcat(allStr, emptStr);
		for(i=0; i<strlen(allStr)-1; i++)
			bigramArr[convertToBigram(allStr[i], allStr[i+1])]++;
		wCnt++;
	}
	bigramArr[convertToBigram(allStr[strlen(allStr)-2], allStr[strlen(allStr)-1])]--;
	fclose(inputFile);

}

double compareBigrammArrs(int bigramArr[SIZE], int bigramArrX[SIZE]){
	int i, sumArr = 0, sumArrX = 0;
	double *freqArr, *freqArrX, dissimilarity = 0;

	freqArr = malloc(SIZE * sizeof(double));
	freqArrX = malloc(SIZE * sizeof(double));

	for(i=0; i<SIZE; i++)
		freqArr[i] = 0.0, freqArrX[i] = 0.0;

	for(i=0; i<SIZE; i++){
		sumArr += bigramArr[i];
		sumArrX += bigramArrX[i];
	}

	for(i=0; i<SIZE; i++){
		freqArr[i] = (double)bigramArr[i] / (double)sumArr;
		freqArrX[i] = (double)bigramArrX[i] / (double)sumArrX; 
	}

	for(i=0; i<SIZE; i++)
		dissimilarity += fabs(freqArr[i] - freqArrX[i]);

	return dissimilarity;
}
