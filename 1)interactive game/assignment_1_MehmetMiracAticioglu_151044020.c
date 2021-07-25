#include <stdio.h>

/*maksimum bulma*/
float findMax(float a, float b){
    if(a > b)
        return a;
    else return b;
}

/*minimum bulma*/
float findMin(float a, float b){
    if(a < b)
        return a;
    else return b;
}

int main(){
    int lives = 10, gameLoop = 1;
    float   detectorX, detectorY, detectorBotLeftX, detectorBotLeftY, detectorTopRightX, detectorTopRightY,
            detectorWidth, detectorHeight,
            markedX, markedY, markedBotLeftX, markedBotLeftY, markedTopRightX, markedTopRightY,
            markedWidth, markedHeight,
            intersectBotLeftX, intersectBotLeftY, intersectTopRightX, intersectTopRightY,
            boardX, boardY,
            inputX, inputY;

    /*ilk degerlerin belirlenmesi*/
    boardX = 200, boardY = 300, markedX = 50, markedWidth = 15, markedY = 50, markedHeight = 20, detectorWidth = 20, detectorHeight = 20;

    printf("Board = [%.0f x %.0f], marked region = [%.0f x %.0f], Detector = [%.0f x %.0f]\n", boardX, boardY, markedWidth, markedHeight, detectorWidth, detectorHeight);

    /*oyun dongusu*/
    while(gameLoop == 1){
        printf("Enter the x coordinate of the move\n");
        scanf("%f", &inputX);
        printf("Enter the y coordinate of the move\n");
        scanf("%f", &inputY);

        /*eget input gecerliyse*/
        if(inputX >= 0 &&  inputX <= boardX && inputY >= 0 && inputY <= boardY){
            lives--;

            /*verilen orta noktayi sol ust koseye cevirme (diger islemler sol ust kose baz alinarak yapildigi icin)*/
            detectorX = inputX-detectorWidth/2, detectorY = inputY+detectorHeight/2;

            /*dikdortgenlerde sol alt ve sag ust kosenin koordinatlarinin bulunmasi*/
            markedBotLeftX = markedX, markedBotLeftY = markedY - markedHeight,
            markedTopRightX = markedX + markedWidth, markedTopRightY = markedY,
            detectorBotLeftX = detectorX, detectorBotLeftY = detectorY - detectorHeight,
            detectorTopRightX = detectorX + detectorWidth, detectorTopRightY = detectorY;

            /*bulunan koordinatlar sayesinde kesisimin bulunmasi*/
            intersectBotLeftX = findMax(markedBotLeftX, detectorBotLeftX);
            intersectBotLeftY = findMax(markedBotLeftY, detectorBotLeftY);
            intersectTopRightX = findMin(markedTopRightX, detectorTopRightX);
            intersectTopRightY = findMin(markedTopRightY, detectorTopRightY);

            /*eger kesisim sonucu bir dikdortgen olusuyorsa (yani dikdortgenler kesisiyorsa)*/
            if(intersectBotLeftX < intersectTopRightX && intersectBotLeftY < intersectTopRightY){

                /*eger tum alani kapsayan vurus yapildiysa*/
                if(intersectBotLeftX == markedBotLeftX && intersectBotLeftY == markedBotLeftY && intersectTopRightX == markedTopRightX && intersectTopRightY == markedTopRightY){
                    printf("You win!\n");
                    gameLoop = 0;
                } else /*eger kismi vurus yapildiysa*/{
                    markedX = intersectBotLeftX, markedY = intersectTopRightY,
                    markedWidth = intersectTopRightX - intersectBotLeftX,
                    markedHeight = intersectTopRightY - intersectBotLeftY,
                    detectorWidth /= 2, detectorHeight /= 2;
                    printf("Partial hit! marked region was shrinked to [%.0f x %.0f], detector was shrinked to [%.0f x %.0f], attempts remaining: %d\n", markedWidth, markedHeight, detectorWidth, detectorHeight, lives);
                }
            } else {
                printf("You've missed the target, attempts remaining: %d\n", lives);
            }
        } else {
            printf("Error, move is not valid, try again\n");
        }

        if(lives == 0)
            gameLoop = 0;
    }
    return 0;
}
