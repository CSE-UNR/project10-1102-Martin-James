//Project9
//James Martin
//


#include <stdio.h>


#define BOARDHEIGHT 14
#define BOARDLENGTH 6
#define WORDLENGTH 5
#define MAXLENGTH 32
#define HIDDENWORD "mystery.txt"


//Function Type/Name: Void getMysteryWord
//Input: a character array to hold the string for the mystery word. 
//an int to define the max length. A _Bool that controls the game flow
//Output: Void function type. Using pass by address updates the mystery 
//word array. Updates Bool value accordingly. 
//Function Behavior: Retrieves the word from the file, if the text file 
//is not there displays the appropriate message and tells the game to 
//finish with the Bool function.	
void getMysteryWord(char mysWor[], int mysLength, _Bool *finish);


//Function Type/Name: Void buildGameBoard
//Input: The int values for height (rows) and length (col) of the 
//2D array that is the game board.
//Output: Void type with no return. Pass by address to build a gameboard
// with null characters in the last comlumn and starts with empty spaces
//for all other elements.
//Function Behavior: Starts a new gameboard at the begining of the game 
//with null characters in the last column.	
void buildGameBoard(int height, int length,char wordBoard[][length]);


//Function Type/Name: Void type function. userInput
//Input: An array for the to hold the value of the user guess. An int 
//value assigned to the length of the user guess. A Bool variable to 
//determine if the guess is valid or if a new input is needed. An int 
//type variable for the guess attempt currently being requested.
//Output: Void function type. Uses pass by address to get values of 
//the user input.
//Function Behavior: Gives the appropriate message request determined by number
//of attempts for user guess or by the tryAgain boolean. 	
void userInput(char guessWord[],int guessLength, _Bool tryAgain, int guessNum);


//Function Type/Name: _Bool type function. checkLength
//Input: The current guess word from the user in an array. The int to define 
//the user guess array. The allowed size determined by a Macro
//Output: A Bool variable defining valid length.
//Function Behavior: Using the count variable, the function iterates through the
//user input and determines how long the input is. If it is not the correct 
//length a print statement lets the user know. A boolean is returned to the main 
//controling flow if a new guess is needed or not.
_Bool checkLength(char userGuess[], int guessSize, int allowedSize);


//Function Type/Name: _Bool type function. checkChars
//Input: An array holding the user guess, an int value to define the array.
//Output: A boolean value for valid or invalid characters
//Function Behavior: A for loop to iterate through the userGuess array 
//and determine if the elements contain the correct characters. 	
_Bool checkChars(char userGuess[],int size);


//Function Type/Name: Void function type. lowerCase
//Input: An array containing the user guess and an int to define the user guess.
//Output:Pass by address to update the userguess if any of the characters are 
//uppercase to lowercase
//Function Behavior: Compares the values of the user guess to uppercase values.
//If uppercase values are found converts them to lower case letters.	
void lowerCase(char guessWord[], int guessLength);


//Function Type/Name: Void function type. compareWords
//Input: Two int values to define the gameboard height and length. The 2D array 
//for the gameboard. The array containing the user guess with its int type for 
//defining length. The hidden word to be guessed in an array and its int value 
//for defining length. The current guess attempt. Pointer to a boolean value for 
//if the puzzle has been solved.
//Output: Pass by address the updated game board with correct values. Bool 
//variable that determines if solved or not. 
//Function Behavior: The mystery word is assigned to a new 1D array. The new array 
//is compared to the user guess word. If the letters match the comparisonarray 
//element is replaced with a blank to avoid duplication. The values of the nested 
//for loop are incremented to start the comparison over. Pass by adress to the 
//game board with the user guess in the correct row along with assigning it an 
//uppercase value if needed. The carrot is also assigned to the correct element.
//Both of these steps are completed by using nested for loops to compare the guess 
//word with the mystery word. When characters match a count variable increments by 
//1. If the count variable matches the length of the hidden word the boolean 
//variable is now true and the puzzle is solved.
void compareWords(int rowIndex, int colIndex, char wordBoard[][colIndex], char guessWord[], int guessLength, char hiddenWord[], int hiddenLength, int guessNum, _Bool *solver);


//Function Type/Name: Void function type. finalMesssage
//Input: An array for the last user guess. An int defining the user guess array. 
//An int for the last attempt number.
//Output: Print to screen the appropriate message to the user.
//Function Behavior: If the number of attempts is 7 tells the player they lost. 
//Otherwise displays the correct message determined by current attempt. Selection 
//is made with a switch statement. 	
void finalMessage(char guessWord[], int guessLength, int guessNum);


//Function Type/Name: Void function type. displayBoard
//Input: The two int values defining the rows and cols in the game board. An array 
//for the 2D gameboard. The current guess the user just made.
//Output:Prints to screen the the game board.
//Function Behavior: Using a for loop to determine the number of rows from the 
//game board needed and prints to screen these rows.	
void displayBoard(int rowIndex, int colIndex, char wordBoard[][colIndex], int guessNum);


//Function Type/Name: Void functin type. banner
//Input: the length of the banner from the macro
//Output: No return value. Prints to screen the banner when called
//Function Behavior: Using a for loop to print the banner at the defined length
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
			validLength = checkLength(playerGuess, MAXLENGTH, WORDLENGTH);
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

_Bool checkLength(char userGuess[], int guessSize, int allowedSize){
int count = 0;
_Bool validL = 1;
	
	for(int i = 0; userGuess[i] != '\0'; i++){
		count++;
	}
	if (count != allowedSize){
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

