//Project9
//James Martin
//


#include <stdio.h>


#define BOARDHEIGHT 14
#define BOARDLENGTH 6
#define WORDLENGTH 5
#define MAXLENGTH 32
#define HIDDENWORD "mystery.txt"



void getMysteryWord(char mysWor[], int mysLength, _Bool *finish);
void buildGameBoard(int height, int length,char wordBoard[][length]);
void userInput(char guessWord[],int guessLength, _Bool tryAgain, int guessNum);
_Bool checkLength(char userGuess[], int guessSize);
_Bool checkChars(char userGuess[],int size);
void lowerCase(char guessWord[], int guessLength);
void compareWords(int rowIndex, int colIndex, char wordBoard[][colIndex], char guessWord[], int guessLength, char hiddenWord[], int hiddenLength, int guessNum, _Bool *solver);
void finalMessage(char guessWord[], int guessLength, int guessNum);
void displayBoard(int rowIndex, int colIndex, char wordBoard[][colIndex], int guessNum);
void banner(int width);






int main(){


_Bool solved = 0, validInput = 0, validLength, validChar, guessAgain = 0;
int attempt = 0;
char gameBoard[BOARDHEIGHT][BOARDLENGTH], playerGuess[MAXLENGTH], mysteryWord[MAXLENGTH];

	getMysteryWord(mysteryWord, MAXLENGTH, &solved);
	
	buildGameBoard(BOARDHEIGHT, BOARDLENGTH, gameBoard);
	
	while((solved == 0) && (attempt < 7)){
	
		attempt++;	
	
		do{
			
			
			userInput(playerGuess, MAXLENGTH, guessAgain, attempt);
			lowerCase(playerGuess, MAXLENGTH);
			validLength = checkLength(playerGuess, MAXLENGTH);
			validChar = checkChars(playerGuess, MAXLENGTH);
			if ((validLength == 0) || (validChar == 0)){
				validInput = 0;
				guessAgain = 1;
			}
			else {
				validInput = 1;
				guessAgain = 0;
			}
			
		}while(validInput == 0);
		
		compareWords(BOARDHEIGHT, BOARDLENGTH, gameBoard, playerGuess, WORDLENGTH, mysteryWord, WORDLENGTH, attempt, &solved);
		
		banner(MAXLENGTH);
		
		if (solved == 0){
			displayBoard(BOARDHEIGHT, BOARDLENGTH, gameBoard, attempt);		
		}
		
		
	}
	
	finalMessage(playerGuess, WORDLENGTH, attempt);

	return 0;
}	
		




void buildGameBoard(int height, int length,char wordBoard[][length]){

	for(int rowIndex = 0; rowIndex < height; rowIndex++){
		for(int colIndex = 0; colIndex < length; colIndex++){
			if (colIndex == (length - 1)){
				wordBoard[rowIndex][colIndex] = '\0';
			}
			else {
				wordBoard[rowIndex][colIndex] = ' ';
			}
		}
	}
}




void userInput(char guessWord[],int guessLength, _Bool tryAgain, int guessNum){

	if (tryAgain == 1){
		printf("Please try again: ");
	}
	else if ((tryAgain == 0) && (guessNum != 6)){
		printf("GUESS %d! Enter your guess: ", guessNum);
	}
	else {
		printf("FINAL GUESS : ");
	}
	scanf("%s", guessWord);
}


void lowerCase(char guessWord[], int guessLength){
	int lower = 32;
	
	//loop to lowercase and capital letters
	for(int i = 0; guessWord[i] != '\0'; i++){
		if ((guessWord[i] >= 'A') && (guessWord[i] <= 'Z')){
			guessWord[i] = guessWord[i] + lower;
		}
	}
}

_Bool checkLength(char userGuess[], int guessSize){
int count = 0, goodLength = 5;
_Bool validL = 1;
	
	for(int i = 0; userGuess[i] != '\0'; i++){
		count++;
	}
	if (count != goodLength){
		validL = 0;
		printf("Your guess must be 5 letters long. ");	
	}
	else{
		validL = 1;
	}
	
	return validL;
	
}




_Bool checkChars(char userGuess[],int size){	

	_Bool validC = 1;
	
	for(int i = 0; userGuess[i] != '\0'; i++){
		if ((userGuess[i] < 'a') || (userGuess[i] > 'z')){
			validC = 0;
		}
	}
	
	if (validC == 0){
		printf("Your guess must contain only letters.\n");
	}
	return validC;
}






void compareWords(int rowIndex, int colIndex, char wordBoard[][colIndex], char guessWord[], int guessLength, char hiddenWord[], int hiddenLength, int guessNum, _Bool* solver){

	int upperCase = -32, solveCounter = 0,dispRow = guessNum*2, carrotRow = dispRow + 1;
	char comparisonWord[hiddenLength], blank = ' ', carrot = '^';

	for (int i = 0; i < hiddenLength; i++){
		comparisonWord[i] = hiddenWord[i];
		wordBoard[dispRow][i] = guessWord[i];
		}
	
	for(int i = 0; i < guessLength; i++){
		for(int j = 0; j < hiddenLength; j++){
			if(guessWord[i] == comparisonWord[j]){
				if (i == j){
					wordBoard[dispRow][i] = guessWord[i] + upperCase;
					comparisonWord[j] = blank;
					solveCounter++;
					i++;
					j = 0;
				}
				else {
					wordBoard[carrotRow][i] = carrot;
					comparisonWord[j] = blank;
					i++;
					j = 0;
				}
			}
		}
	}

	if (solveCounter == 5){
		*solver = 1;
	}
}






void finalMessage(char guessWord[], int guessLength, int guessNum){
	
	int upper = -32, adjLength = 9,numAdj = 3, adjRow = (guessNum/2);
	char dispAdjective[numAdj][adjLength];
	
	for(int i = 0; i < guessLength; i++){
		guessWord[i] = guessWord[i] + upper;
	}
	
	if (guessNum < 7){
			printf("\t\t%s\n", guessWord);
			
			if (guessNum == 1){
				printf("\tYou won in 1 guess!\n");
				printf("\t\tGOATED\n");
			}
			else{
				printf("\tYou won in %d guesses!\n", guessNum);
			}
			switch (guessNum){
			
				case 2:
				case 3:
					printf("\t\tAMAZING\n");
					break;
				case 4:
				case 5:
					printf("\t\tNICE\n");
					break;
				}
	}
	else {
		printf("You lost, better luck next time!\n");
	}
}

void displayBoard(int rowIndex, int colIndex, char wordBoard[][colIndex], int guessNum){
	int maxRow = ((guessNum*2) + 2);
	
	for(int row = 2; row < maxRow; row++){
		printf("%s\n", wordBoard[row]);
	}
}



void banner(int width){
	
	for(int i = 0; i < width; i++){
		printf("=");
	}
	printf("\n");
}

void getMysteryWord(char mysWor[], int mysLength, _Bool *finish){


	FILE *wordFp;

	wordFp = fopen(HIDDENWORD, "r");
	if (wordFp == NULL) {
		printf("Sorry, could not get today's word. Try again tomorrow.\n");
		*finish = 1;
	}
	else {
		fscanf(wordFp, "%s", mysWor);
		
		fclose(wordFp);
		}
}

