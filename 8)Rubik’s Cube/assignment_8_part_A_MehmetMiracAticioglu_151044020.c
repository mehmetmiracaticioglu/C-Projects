#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
	int face, rowNumber, colNumber, value;
} CubePiece;

typedef struct {
  CubePiece * array;
  size_t used;
  size_t size;
} Array;

void initArray(Array * a, size_t initialSize);

int findIndexOf(int val, int * arr, int size);

void freeArray(Array * a);

void rotatePoint(CubePiece * piece, int cubeSize, int amount);

void flipPoint(CubePiece * piece, int cubeSize);

int main(){
	int rowNghbrs[7][5] = {{0, 1, 2, 3}, {1, 2, 3, 0}, {2, 3, 0, 1}, {3, 0, 1, 2}, {4, 1, 5, 3}, {5, 1, 4, 3}};
	int colNghbrs[7][5] = {{0, 4, 2, 5}, {1, 4, 3, 5}, {2, 4, 0, 5}, {3, 4, 1, 5}, {4, 2, 5, 0}, {5, 0, 4, 2}};
	int i, j, k, val, cubeSize;
	int rowOrColId, faceNumber, rotateDir;
	int tempList[5];
	char rotateStr[7], rowOrCol[7], direction[7];
	Array cube;
	
	FILE * commands = fopen( "commands.txt", "rt" );
	fscanf( commands, "%d", &cubeSize );

	/* creating the inital cube */
	initArray( &cube, cubeSize*cubeSize*6 );
	for( i=0; i<6; i++ ){
		for( j=0; j<cubeSize; j++ ){
			for( k=0; k<cubeSize; k++ ){
				cube.array[i * cubeSize * cubeSize + j * cubeSize + k].face = i;
				cube.array[i * cubeSize * cubeSize + j * cubeSize + k].value = i;
				cube.array[i * cubeSize * cubeSize + j * cubeSize + k].rowNumber = j;
				cube.array[i * cubeSize * cubeSize + j * cubeSize + k].colNumber = k;
			}
		}
	}

	while( fscanf( commands, "%s", rotateStr ) != EOF ){
		rotateDir = 0;
		fscanf( commands, "%d %s %d %s", &faceNumber, rowOrCol, &rowOrColId, direction );
		
		if( strcmp("up", direction) == 0 || strcmp("right", direction) == 0 ){
			rotateDir = 1;
		} else if( strcmp("down", direction) == 0 || strcmp("left", direction) == 0 ){
			rotateDir = -1;
		}

		/* change reference system based on faceNumber variable */
		for( i=0; i<cubeSize*cubeSize*6; i++ ){
			if( cube.array[i].face == 0 ){
				switch(faceNumber){
					case 0: break;
					case 1: break;
					case 2: flipPoint(&cube.array[i], cubeSize); break;
					case 3: break;
					case 4: break;
					case 5: break;
				}
			}
			if( cube.array[i].face == 1 ){
				switch(faceNumber){
					case 0: break;
					case 1: break;
					case 2: break;
					case 3: flipPoint(&cube.array[i], cubeSize); break;
					case 4: rotatePoint(&cube.array[i], cubeSize, 3); break;
					case 5: rotatePoint(&cube.array[i], cubeSize, 1); break;
				}
			}
			if( cube.array[i].face == 2 ){
				switch(faceNumber){
					case 0: flipPoint(&cube.array[i], cubeSize); break;
					case 1: break;
					case 2: break;
					case 3: break;
					case 4: rotatePoint(&cube.array[i], cubeSize, 2); break;
					case 5: rotatePoint(&cube.array[i], cubeSize, 2); break;
				}
			}
			if( cube.array[i].face == 3 ){
				switch(faceNumber){
					case 0: break;
					case 1: flipPoint(&cube.array[i], cubeSize); break;
					case 2: break;
					case 3: break;
					case 4: rotatePoint(&cube.array[i], cubeSize, 1); break;
					case 5: rotatePoint(&cube.array[i], cubeSize, 3); break;
				}
			}
			if( cube.array[i].face == 4 ){
				switch(faceNumber){
					case 0: break;
					case 1: rotatePoint(&cube.array[i], cubeSize, 1); break;
					case 2: rotatePoint(&cube.array[i], cubeSize, 2); break;
					case 3: rotatePoint(&cube.array[i], cubeSize, 3); break;
					case 4: break;
					case 5: rotatePoint(&cube.array[i], cubeSize, 2); break;
				}
			}
			if( cube.array[i].face == 5 ){
				switch(faceNumber){
					case 0: break;
					case 1: rotatePoint(&cube.array[i], cubeSize, 3); break;
					case 2: rotatePoint(&cube.array[i], cubeSize, 2); break;
					case 3: rotatePoint(&cube.array[i], cubeSize, 1); break;
					case 4: rotatePoint(&cube.array[i], cubeSize, 2); break;
					case 5: break;
				}
			}
		}

		if( strcmp( "row", rowOrCol ) == 0 && faceNumber != 4 && faceNumber != 5 ){
			for( i=0; i<4; i++ )
				tempList[i] = rowNghbrs[faceNumber][i];
			for( i=0; i<cubeSize*cubeSize*6; i++ ){
				if( findIndexOf( cube.array[i].face, tempList, 4 ) != -1 && cube.array[i].rowNumber == rowOrColId ){
					val = findIndexOf( cube.array[i].face, tempList, 4 );
					if( rotateDir == -1 ){
						if( val != 0 )
							cube.array[i].face = tempList[val - 1];
						else cube.array[i].face = tempList[3];
					} else if( rotateDir == 1 ){
						if( val != 3 )
							cube.array[i].face = tempList[val + 1];
						else cube.array[i].face = tempList[0];
					}
				}
			}
		} else if ( strcmp( "column", rowOrCol ) == 0 && faceNumber != 4 && faceNumber != 5 ){
			for( i=0; i<4; i++ )
				tempList[i] = colNghbrs[faceNumber][i];
			for( i=0; i<cubeSize*cubeSize*6; i++ ){
				if( findIndexOf( cube.array[i].face, tempList, 4 ) != -1 && cube.array[i].colNumber == rowOrColId ){
					val = findIndexOf( cube.array[i].face, tempList, 4 );
					if( rotateDir == -1 ){
						if( val != 0 )
							cube.array[i].face = tempList[val - 1];
						else cube.array[i].face = tempList[3];
					} else if( rotateDir == 1 ){
						if( val != 3 )
							cube.array[i].face = tempList[val + 1];
						else cube.array[i].face = tempList[0];
					}
				}
			}
		}

		/* change reference system based on faceNumber variable */
		for( i=0; i<cubeSize*cubeSize*6; i++ ){
			if( cube.array[i].face == 0 ){
				switch(faceNumber){
					case 0: break;
					case 1: break;
					case 2: flipPoint(&cube.array[i], cubeSize); break;
					case 3: break;
					case 4: break;
					case 5: break;
				}
			}
			if( cube.array[i].face == 1 ){
				switch(faceNumber){
					case 0: break;
					case 1: break;
					case 2: break;
					case 3: flipPoint(&cube.array[i], cubeSize); break;
					case 4: rotatePoint(&cube.array[i], cubeSize, 1); break;
					case 5: rotatePoint(&cube.array[i], cubeSize, 3); break;
				}
			}
			if( cube.array[i].face == 2 ){
				switch(faceNumber){
					case 0: flipPoint(&cube.array[i], cubeSize); break;
					case 1: break;
					case 2: break;
					case 3: break;
					case 4: rotatePoint(&cube.array[i], cubeSize, 2); break;
					case 5: rotatePoint(&cube.array[i], cubeSize, 2); break;
				}
			}
			if( cube.array[i].face == 3 ){
				switch(faceNumber){
					case 0: break;
					case 1: flipPoint(&cube.array[i], cubeSize); break;
					case 2: break;
					case 3: break;
					case 4: rotatePoint(&cube.array[i], cubeSize, 3); break;
					case 5: rotatePoint(&cube.array[i], cubeSize, 1); break;
				}
			}
			if( cube.array[i].face == 4 ){
				switch(faceNumber){
					case 0: break;
					case 1: rotatePoint(&cube.array[i], cubeSize, 3); break;
					case 2: rotatePoint(&cube.array[i], cubeSize, 2); break;
					case 3: rotatePoint(&cube.array[i], cubeSize, 1); break;
					case 4: break;
					case 5: rotatePoint(&cube.array[i], cubeSize, 2); break;
				}
			}
			if( cube.array[i].face == 5 ){
				switch(faceNumber){
					case 0: break;
					case 1: rotatePoint(&cube.array[i], cubeSize, 1); break;
					case 2: rotatePoint(&cube.array[i], cubeSize, 2); break;
					case 3: rotatePoint(&cube.array[i], cubeSize, 3); break;
					case 4: rotatePoint(&cube.array[i], cubeSize, 2); break;
					case 5: break;
				}
			}
		}

	}

	int tempCol = 0, tempRow = 0, tempFace = 0;

	while(tempFace < 6){
		for( i=0; i<cubeSize*cubeSize*6; i++ ){
			if( cube.array[i].rowNumber == tempRow && cube.array[i].colNumber == tempCol && cube.array[i].face == tempFace )
				printf( "%d ", cube.array[i].value );
		}
		tempCol++;
		if( tempCol == cubeSize ){
			tempCol = 0;
			tempRow += 1;
			printf( "\n" );
		}
		if( tempRow == cubeSize ){
			tempFace++;
			tempCol = 0;
			tempRow = 0;
			printf( "\n" );
		}
	}

	freeArray( &cube );
	fclose( commands );
	return 0;
}

void initArray(Array * a, size_t initialSize){
  a->array = (CubePiece *)malloc( initialSize * sizeof( CubePiece ) );
  a->used = 0;
  a->size = initialSize;
}

void freeArray(Array * a){
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

int findIndexOf(int val, int * arr, int size){
	int i;
	for( i=0; i<size; i++ )
		if( arr[i] == val )
			return i;
	return -1;
}

void rotatePoint(CubePiece * piece, int cubeSize, int amount){
	int tempCol, tempRow, i;
	for(i=0; i<amount; i++){
		tempRow = piece->colNumber;
		tempCol = cubeSize - piece->rowNumber - 1;
		piece->rowNumber = tempRow;
		piece->colNumber = tempCol;
	}
}

void flipPoint(CubePiece * piece, int cubeSize){
	int center;
	if(cubeSize % 2 == 1){
		center = (cubeSize - 1) / 2;
		piece->colNumber -= (piece->colNumber - center) * 2;
	} else {
		piece->colNumber = (cubeSize-1) - piece->colNumber;
	}
}