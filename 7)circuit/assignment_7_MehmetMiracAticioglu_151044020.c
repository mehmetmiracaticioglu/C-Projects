#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
	list of operations:
	and: 1
	or: 2
	not: 3
	flipflop(xor): 4
*/

typedef struct gate_t{
	int value, operation;
	char name[15], parent1[15], parent2[15];
} Gate;

typedef struct {
  Gate * array;
  size_t used;
  size_t size;
} Array;

void initArray(Array * a, size_t initialSize);

void insertArray(Array * a, Gate element);

void freeArray(Array * a);

int param_count(char * str);

int main(){
	FILE * input_txt, * circuit_txt;
	char temp_str[20], temp_word[20],
		operation_str[20], vari_str[20],
		param1_str[20], param2_str[20];
	int letter_count, i, j, k, isAlreadyIn = 0,
		input_count = 0, input_lines = 0,
		first_param, second_param;
	Gate temp_gate;
	Array gates;
	initArray(&gates, 1);
	input_txt = fopen("input.txt", "rt");
	circuit_txt = fopen("circuit.txt", "rt");
	while(fgets(temp_str, 100, circuit_txt)){
		letter_count = 0;
		if(temp_str[strlen(temp_str)-1] == '\n')
			temp_str[strlen(temp_str)-1] = '\0';
		for(i=0; i<param_count(temp_str)+1; i++){
			sscanf(temp_str+letter_count, "%s", temp_word);
			letter_count+=strlen(temp_word)+1;
			if(i!=0){
				isAlreadyIn = 0;
				strcpy(temp_gate.name, temp_word);
				strcpy(temp_gate.parent1, "none");
				strcpy(temp_gate.parent2, "none");
				temp_gate.value = -1, temp_gate.operation = 0;
				for(j=0; j<gates.used; j++)
					if(strcmp(temp_word, gates.array[j].name)==0)
						isAlreadyIn = 1;
				if(!isAlreadyIn)
					insertArray(&gates, temp_gate);
			}
		}
		sscanf(temp_str, "%s %s", operation_str, vari_str);
		for(i=0; i<gates.used; i++){
			if(strcmp(vari_str, gates.array[i].name) == 0){
				if(strcmp("AND", operation_str) == 0){
					sscanf(temp_str+strlen(operation_str)+strlen(vari_str)+2, "%s %s", param1_str, param2_str);
					gates.array[i].operation = 1;
					strcpy(gates.array[i].parent1, param1_str);
					strcpy(gates.array[i].parent2, param2_str);
				} else if(strcmp("OR", operation_str) == 0) {
					sscanf(temp_str+strlen(operation_str)+strlen(vari_str)+2, "%s %s", param1_str, param2_str);
					gates.array[i].operation = 2;
					strcpy(gates.array[i].parent1, param1_str);
					strcpy(gates.array[i].parent2, param2_str);
				} else if(strcmp("NOT", operation_str) == 0){
					sscanf(temp_str+strlen(operation_str)+strlen(vari_str)+2, "%s", param1_str);
					gates.array[i].operation = 3;
					strcpy(gates.array[i].parent1, param1_str);
				} else if(strcmp("FLIPFLOP", operation_str) == 0){
					sscanf(temp_str+strlen(operation_str)+strlen(vari_str)+2, "%s", param1_str);
					gates.array[i].operation = 4;
					gates.array[i].value = 0;
					strcpy(gates.array[i].parent1, param1_str);
				}
			}
		}
	}
	
	
	for(i=0; i<gates.used; i++)
		if(strcmp(gates.array[i].parent1, "none") == 0 && strcmp(gates.array[i].parent2, "none") == 0)
			input_count++;

	while(fgets(temp_str, 100, input_txt))
		input_lines++;
	rewind(input_txt);

	for(i=0; i<input_lines; i++){
		for(j=0; j<gates.used; j++)
			if(gates.array[j].operation != 4)
				gates.array[j].value = -1;
		for(j=0; j<input_count; j++)
			fscanf(input_txt, "%d", &gates.array[j].value);

		for(j=0; j<gates.used; j++){
			if(gates.array[j].operation == 1 || gates.array[j].operation == 2){
				for(k=0; k<gates.used; k++)
					if(strcmp(gates.array[k].name, gates.array[j].parent1) == 0)
						first_param = gates.array[k].value;
				for(k=0; k<gates.used; k++)
					if(strcmp(gates.array[k].name, gates.array[j].parent2) == 0)
						second_param = gates.array[k].value;
				if(gates.array[j].operation == 1)
					gates.array[j].value = first_param && second_param;
				else gates.array[j].value = first_param || second_param;
			} else if(gates.array[j].operation == 3 || gates.array[j].operation == 4){
				for(k=0; k<gates.used; k++)
					if(strcmp(gates.array[k].name, gates.array[j].parent1) == 0)
						first_param = gates.array[k].value;
				if(gates.array[j].operation == 4)
					gates.array[j].value = gates.array[j].value ^ first_param;
				else gates.array[j].value = !first_param;
			}
		}
		/*	DEBUG
		printf("isim\tata1\tata2\tislem\tdeger\n");
		printf("--------------------------------------\n");
		for(j=0; j<gates.used; j++)
			printf("%s\t%s\t%s\t%d\t%d\n", gates.array[j].name, gates.array[j].parent1, gates.array[j].parent2, gates.array[j].operation, gates.array[j].value);*/
		printf("%d\n", gates.array[gates.used-1].value);
	}

	freeArray(&gates);
	fclose(circuit_txt);
	fclose(input_txt);
	return 0;
}

void initArray(Array * a, size_t initialSize){
  a->array = (Gate *)malloc(initialSize * sizeof(Gate));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array * a, Gate element){
  if(a->used == a->size) {
    a->size *= 2;
    a->array = (Gate *)realloc(a->array, a->size * sizeof(Gate));
  }
  a->array[a->used++] = element;
}

void freeArray(Array * a){
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

int param_count(char * str){
	int i, result = 0;
	for(i=0; i<strlen(str); i++)
		if(str[i] == ' ')
			result++;
	return result;
}