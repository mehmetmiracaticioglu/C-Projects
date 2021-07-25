#include <stdio.h>
#include <math.h>

int main(){
	double tempNumber, allChunks[500][500], averages[1000], 
			tempAverage = 0, tempAverageSort;

	int chunkSizes[1000], chunkCount = 0, tempChunkSize = 0,
		currentZeroCount = 0, i, j, k, mindex;

	FILE * inputFile, * outputFile;

	inputFile = fopen("input.txt", "rt");
	outputFile = fopen("output.txt", "wt");

	while(fscanf(inputFile, "%lf", &tempNumber) != EOF){
		if(tempNumber == 0.0)
			currentZeroCount++;
		else currentZeroCount = 0;

		if(currentZeroCount == 3){
			/*yeni grup basladiginda onceki grubun boyutunu diziye ekleme ve degerleri sifirlama*/
			chunkSizes[chunkCount] = tempChunkSize - 2;
			chunkCount++, tempChunkSize = 0;
		} else {
			allChunks[chunkCount][tempChunkSize] = tempNumber;
			tempChunkSize++;
		}
	}

	/*son grubu da ekleme*/
	chunkSizes[chunkCount] = tempChunkSize;
	chunkCount++;

	/*ortalamalari array'e yazma*/
	for(i=0; i<chunkCount; i++){
		for(j=0; j<chunkSizes[i]; j++)
			tempAverage+=allChunks[i][j];
		averages[i] = tempAverage/chunkSizes[i];
		tempAverage = 0;
	}

	/*ortalamalari selection sortla siralama*/
	for(i=0; i<chunkCount-1; i++){
        mindex = i;
        for (j=i+1; j<chunkCount; j++)
          if (averages[j] < averages[mindex])
            mindex = j;
        tempAverageSort = averages[mindex];
        averages[mindex] = averages[i];
        averages[i] = tempAverageSort;
    }

    /*siralanmis ortalamalarla gruplarin ortalamalarini siralayip uygun sirada dosyaya yazma*/
    for(i=0; i<chunkCount; i++){
    	for(j=0; j<chunkCount; j++){
    		tempAverage = 0;
    		for(k=0; k<chunkSizes[j]; k++)
    			tempAverage+=allChunks[j][k];
    		/*double sayilari karsilastirma*/
    		if(fabs(tempAverage/chunkSizes[j]-averages[i]) <= 0.0000001){
    			for(k=0; k<chunkSizes[j]; k++)
    				fprintf(outputFile, "%lf ", allChunks[j][k]);
    			fprintf(outputFile, "\n");
    		}
    	}
    }

	fclose(inputFile);
	fclose(outputFile);
	return 0;	
}
