# include <iostream>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <time.h>

using namespace std;

char box[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

int player_human, player_computer;  // stores player numbers
char mark_human, mark_computer;   // stores marks for players

void printGrid();    // function to print grid row wise
void printRow(int start);   //  function to print a single row
bool drawMark(int choice, char mark);  // function to draw mark on the grid
int checkWin();   // wholesome function to check game status
int isTriplet(int start, int increment);   // function to find triplets in grid
int findBestMove();   // function to assess best move for computer
void Print(char arr[], int len);  // function to print array for debugging purposes


int main (){

    cout << "Choose your mark" << "\n" << "Player 1 : Cross (X) - Player 2 : Circle(O)" << endl;
    cin >> player_human;

    if ((player_human != 1) && (player_human != 2)){   // easy error handling to avoid invalid inputs
        cout << "Invalid input !" << endl;
        main();
    }

    mark_human = (player_human == 1) ? 'X': 'O';   // one line conditional to set mark for player

    player_computer = (player_human == 1) ? 2: 1;    // computer becomes player 2 if user inputs 1 and vice-versa otheriwse
    mark_computer = (player_computer == 1) ? 'X': 'O';

    printGrid();   // print grid to familiarize user with cell numbering

    cout << " \nInput cell number from 1 to 9 to mark your choice \n";

    int player_move, computer_move;   // variables to track choices

    while (checkWin() == -1){  // while game is still not over
        cin >> player_move;

        if(player_move > 9 || player_move < 1){   // error handling to avoid impossible inputs
            cout << "Invalid move, please input number between 1 and 9" << endl;
            continue;
        }

        if (!drawMark(player_move, mark_human)){
            cout << "Invalid move, cell already marked" << endl;
            continue;
        }

        computer_move = findBestMove();

        if (drawMark(computer_move, mark_computer)){
            cout << " Computer selected :   " << computer_move << endl;
        }

        printGrid();
    }

    if (checkWin() == 0){
        cout << " Game draw ! " << endl;
    }
    else if (checkWin() == 1){
        cout << " Player 1 won ! " << endl;
    }
    else if (checkWin() == 2){
        cout << " Player 2 won ! " << endl;
    }

    int dump;

    cout << "Do you want to play again ? \nPress 1 for YES and 0 for NO" << endl;
    cin >> dump;

    if (dump == 1){
        for (int i = 0; i < 9; i++){
            box[i] = i + 49;   // resets the box array, note that adding 49 is for adjusting ASCII codes
        }
        main();
    }
    else if (dump == 0){
        cout << "THANK YOU FOR PLAYING ! \nPress any key to exit" << endl;
    }
    return 1;
}


void printGrid(){
    // prints row-wise to avoid repetitions
    printRow(0);
    printRow(3);
    printRow(6);
}

void printRow(int start){
    cout << " " <<  box[start] << " |";
    cout << " " <<  box[start + 1] << " |";
    cout <<  " " << box[start + 2] <<endl;
}

bool drawMark(int choice, char mark){
    if (checkWin() == -1){ // if match is still not over
       if (isdigit(box[choice - 1])){  // if the cell is indeed empty
            box[choice - 1] = mark;
            return true;
        }
    }
    else{return false;}
}

int checkWin(){
    /*
        -1 is for game still running
        0 is for game been draw
        1 is for game won by player 1
        2 is for game won by player 2
    */

    int won = isTriplet(0, 1) + isTriplet(3, 1) + isTriplet(6, 1) + isTriplet(0, 3) + isTriplet(1, 3) + isTriplet(2, 3) + isTriplet(0, 4) + isTriplet(2, 2);

    // addition ensures that won is 0 precisely when no triplet is found and the player number otherwise
    if (won){
        return won;
    }
    else{   // checks if cells are still empty
        for (int i = 0; i < 9; i++){
            if (isalpha(box[i])){
                continue;   // skip for marked cells
            }
            return -1;
        }
    }
    return 0;  // draw if no condition is met and the grid is full
}
int isTriplet(int start, int increment){
    if ((box[start] == box[start + increment]) &&  (box[start + increment] == box[start + increment + increment])){   // checks if a triplet in box[] is formed
        return (box[start] == 'X') ? 1: 2;                                   // returns 1 when the triplet is of 'X' and 2 when of 'O'
    }
    return 0;     // else returns 0
}

int findBestMove(){
    // if middle spot is empty mark that
    if (box[4] == '5'){
        return 5;
    }
    for (int i = 0; i < 9; i++){  // check is marking an empty cell can result in win
        if(!isalpha(box[i])){
            box[i] = mark_computer;  // fills the cell with mark
            if (checkWin() == player_computer){   // checks if computer is winning
                box[i] = i + 49;    // resets and return index
                return i + 1;
            }
            box[i] = i + 49;   // reset at the end of check
        }
    }
    for (int i = 0; i < 9; i++){   // check if player marking an empty cell can result in lose
        if(!isalpha(box[i])){
            box[i] = mark_human;
            if (checkWin() == player_human){
                box[i] = i + 49;
                return i + 1;
            }
            box[i] = i + 49;
        }
    }
    if (box[0] == '1'){  // if first cell is empty
        return 1;
    }
    else {
        for (int i = 2; i < 9; i = i + 2){   // prevents formation of 'V' move
            if(!isalpha(box[i])){
                return i + 1;
            }
        }
    }
    for (int i = 0; i < 9; i = i + 1){   // returns the first empty cell in case no condition is met
        if(!isalpha(box[i])){
            return i + 1;
        }
    }
}
void Print(char arr[], int len){
    // prints character array in one line
    cout << "[ ";
    for(int i = 0; i < len; i++){
        cout << arr[i] << ", ";
    }
    cout << "\b\b ]\n";
    return;
}
