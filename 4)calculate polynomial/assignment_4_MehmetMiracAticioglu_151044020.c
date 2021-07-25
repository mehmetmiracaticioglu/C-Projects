#include <stdio.h>
#include <string.h>
#include <math.h>

int main(){
	int valuesSize = 0, tempCount = 1, tempLen, tempExpo, isConstant, terms = 0, expos[100], i, j, k;
	double values[100], coeffs[100], constant = 0, tempCoeff, tempEval = 0;
	char tempString[1005], rawPolynomial[1005], coeffStr[10], expoStr[10], tempChar;
	FILE * inp, * inp2, * outp;
	inp = fopen("values.txt", "rt");
	inp2 = fopen("polynomial.txt", "rt");
	
	while(fscanf(inp, "%lf", &values[valuesSize]) != EOF)
		valuesSize++;

	fscanf(inp2, "%s", tempString);

	if(tempString[0]!='+' && tempString[0]!='-'){
		rawPolynomial[0] = '+';
		rawPolynomial[1] = '\0';
		strcat(rawPolynomial, tempString);
	} else {
		strcpy(rawPolynomial, tempString);
	}

	tempString[0] = rawPolynomial[0];
	i = strlen(rawPolynomial);
	rawPolynomial[i] = '+';
	rawPolynomial[i+1] = '\0';

	for(i=1; i<strlen(rawPolynomial); i++){
		if(rawPolynomial[i] == '+' || rawPolynomial[i] == '-'){
			terms++;
			tempString[tempCount++] = '\0';
			tempCount = 1;

			isConstant = 0;
			for(j=0; j<strlen(tempString); j++){
				tempCoeff = 1, tempExpo = 1;
				if(tempString[j] == 'x'){
					if(j!=0 && j!=1){
						tempLen = 0;
						for(k=0; k<j; k++)
							coeffStr[tempLen++] = tempString[k];
						coeffStr[tempLen] = '\0';
						sscanf(coeffStr, "%lf", &tempCoeff);
					} else if(j==1){
						if(tempString[j-1] == '-')
							tempCoeff = -1;
						else tempCoeff = 1;
					}
					if(j!=strlen(tempString)-1){
						tempLen = 0;
						for(k=j+1; k<strlen(tempString); k++)
							expoStr[tempLen++] = tempString[k];
						expoStr[tempLen] = '\0';
						sscanf(expoStr, "%c%d", &tempChar,&tempExpo);
					}
					coeffs[terms-1] = tempCoeff, expos[terms-1] = tempExpo;
				} else {
					isConstant++;
				}
			}
			if(isConstant == strlen(tempString)){
				sscanf(tempString, "%lf", &constant);
			}
			tempString[0] = rawPolynomial[i];
		} else {
			tempString[tempCount++] = rawPolynomial[i];
		}	
	}
	
	tempString[tempCount] = '\0';
	outp = fopen("evaluations.txt", "wt");
	for(i=0; i<valuesSize; i++){
		tempEval = 0;
		for(j=0; j<terms; j++)
			tempEval += pow(values[i],expos[j]) * coeffs[j];
		fprintf(outp, "%0.2f\n", tempEval);
	}
	fclose(inp);
	fclose(inp2);
	fclose(outp);
	return 0;
}