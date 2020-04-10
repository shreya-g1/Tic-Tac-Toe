//ttt.cpp
//Shreya Gowda, CISP 360
//7/21/18

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>

#define NUM_ROWS 3    //the number of rows in grid
#define NUM_COLS 3    //the number of columns in grid
#define NUM_SQUARES 9    //number of squares in grid
#define NUM_PLAYERS 2   //number of players
#define HUMAN 0    //number to represent human
#define COMPUTER 1    //number to represent computer
#define DRAW 2    //number to represent that no one won
#define HUMAN_SIGN "X"    //mark made on board by player
#define COMPUTER_SIGN "O"    //mark made by computer

using namespace std;


//Function prototypes
void instructions();
void play(int* humanScore, int* computerScore);
void printGrid(string arr[NUM_ROWS][NUM_COLS]);
int getRandNum(int maxNum);
void humanTurn(string* humanMoves, string arr[NUM_ROWS][NUM_COLS], const int MIN_RANGE_NUM[NUM_ROWS]);
void computerTurn(string* computerMoves, string arr[NUM_ROWS][NUM_COLS], const int MIN_RANGE_NUM[NUM_ROWS]);
bool checkValid(const int MIN_RANGE_NUM[NUM_ROWS], string arr[NUM_ROWS][NUM_COLS], int num);
int checkWin(string arr[NUM_ROWS][NUM_COLS], string sign);

int main(){
  const int EXPLAIN_GAME=1;    //menu option one
  const int PLAY=2;    //menu option two
  const int QUIT=3;    //menu option three
  int opt=0;    //option chosen
  int humanScore=0;    //human's total score at end of program
  int computerScore=0;    //computer's total score at end of program
  int* ptr_humanScore=&humanScore;    //pointer to humanScore variable
  int* ptr_computerScore=&computerScore;    //pointer to computerScore variable
  char playAgain='Y';    //option to play tic-tac-toe again

  //Program greeting
  cout<<"Tic-Tac-Toe Game Program"<<endl;
  cout<<"This is a simple game of tic-tac-toe against you and the computer."<<endl;
  cout<<"*Note: At the end, it may take longer for computer to make move. Just wait.*"<<endl;

  // Specification B1 - Start Menu
  cout<<endl<<"Menu"<<endl;
  cout<<"1 - Explain Game"<<endl;
  cout<<"2 - Play"<<endl;
  cout<<"3 - Quit"<<endl<<endl;
  cout<<"Enter here:";
  cin>>opt;

  //Specification B2 - Valid Menu Choices
  while(opt!=EXPLAIN_GAME&&opt!=PLAY&&opt!=QUIT){
    cout<<endl<<"Invalid input. Retype: ";
    cin>>opt;
  }

  //Menu option "Explain Game" chosen
  if(opt==EXPLAIN_GAME){
    system("clear");
    cout<<"Tic-Tac-Toe Game Program";
    instructions();
    cout<<endl<<"Menu"<<endl;
    cout<<"2 - Play"<<endl;
    cout<<"3 - Quit"<<endl<<endl;
    cout<<"Enter here:";
    cin>>opt;

    while(opt!=PLAY&&opt!=QUIT){
      cout<<endl<<"Invalid input. Retype: ";
      cin>>opt;
    }

    cout<<endl;
  }

  //Menu option "Quit" chosen
  if(opt==QUIT){
    cout<<endl<<"Thanks for checking out tic-tac-toe. Come again next time!"<<endl;
    cout<<endl<<"Points"<<endl;
    cout<<"Human: "<<(humanScore)<<" vs. "<<"Computer: "<<(computerScore)<<endl<<endl;
    return 0;
  }

  // Specification A1 - Main Game Loop
  do{
    system("clear");
    cout<<"Tic-Tac-Toe Game Program"<<endl;
    play(ptr_humanScore, ptr_computerScore);

    // Specification A2 - Simple Prompt
    cout<<endl<<"Want to play again? (Y/N)";
    cin>>playAgain;

    while((toupper(playAgain)!='N')&&(toupper(playAgain)!='Y')){
      cout<<"Invalid input:";
      cin>>playAgain;
      cout<<playAgain;
    }
  }while(toupper(playAgain)=='Y');

  // Specification A3 - Keep Score
  cout<<endl<<"Thanks for checking out tic-tac-toe. Come again next time!"<<endl;
  cout<<endl<<"Points"<<endl;
  cout<<"Human: "<<(humanScore)<<" vs. "<<"Computer: "<<(computerScore)<<endl<<endl;
}

// Specification B3 - Pretty Display  
// Specification C2 - Simple Display
void printGrid(string arr[NUM_ROWS][NUM_COLS]){
  int count1=0;
  for(int a=0; a<NUM_ROWS; a++){
    int count2=0;
    for(int b=0; b<NUM_COLS; b++){
      cout<<arr[a][b];
      if(count2<2){
        cout<<" | ";
      }
      count2++;
    }
    if(count1<2){
      cout<<endl<<"---------"<<endl;
    }
    count1++;
  }
  cout<<endl<<endl;
}

//generates random number from 0 (inclusive) to maximum number (exclusive)
int getRandNum(int maxNum){
  int randNum=0;  //holds random number

  srand(time(0));
  randNum= rand()%maxNum;
  return randNum;
}

//Display the Game Instructions
void instructions(){
  cout<<endl<<"Instructions"<<endl;
  cout<<"You will be playing a classic game of TIC-TAC-TOE against an opponent (the computer). But what is tic-tac-toe?"<<endl;
  cout<<"The game is played on a 3x3 grid."<<endl; 
  cout<<"You and your opponent will take turns putting a mark in an empty square in the grid."<<endl;
  cout<<"Your mark will be represented with an 'X', while your opponent's mark will be an 'O'."<<endl;
  cout<<"You win by being the first one to get 3 marks in a line (vertically, horizontally, or diagonally)."<<endl;
  cout<<"If no one is able to achieve this, the game ends in a tie."<<endl<<endl;
}

//Gameplay function 
void play(int* humanScore, int* computerScore){
  const int MIN_RANGE_NUM[NUM_ROWS]={0,3,6};    //the least number in each row in a grid
  int starter=0;    //person who starts in game
  int winner=DRAW;    //person who won game
  int count=0;    //stops the game when nine moves have been made
  string tic_tac_toe[NUM_ROWS][NUM_COLS]={"0","1","2","3","4","5","6", "7", "8"};    //Create an empty Tic_Tac_Toe board
  string totalMoves="";    //all the moves made by both players in order
  string* ptr_totalMoves=&totalMoves;    //pointer to totalMoves variable
  
  printGrid(tic_tac_toe);

  // Specification C1 - Random Start
  starter=getRandNum(NUM_PLAYERS);

  // Specification C4 - Decide Winner
  if(starter==HUMAN){
    cout<<"The human starts first."<<endl;
    do{
      humanTurn(ptr_totalMoves, tic_tac_toe, MIN_RANGE_NUM);
      printGrid(tic_tac_toe);
      if(checkWin(tic_tac_toe,HUMAN_SIGN)!=DRAW){
        winner=HUMAN;
        break;
      }
      count++;
      if(count>(NUM_SQUARES-1)){
        break;
      }
      computerTurn(ptr_totalMoves, tic_tac_toe, MIN_RANGE_NUM);
      printGrid(tic_tac_toe);
      if(checkWin(tic_tac_toe,COMPUTER_SIGN)!=DRAW){
        winner=COMPUTER;
        break;
      }
      count++;
    }while(winner==DRAW&&count<=(NUM_SQUARES-1));
  }
  else{
    cout<<"The computer starts first."<<endl;
    do{
      computerTurn(ptr_totalMoves, tic_tac_toe, MIN_RANGE_NUM);
      printGrid(tic_tac_toe);
      if(checkWin(tic_tac_toe,COMPUTER_SIGN)!=DRAW){
        winner=COMPUTER;
        break;
      }
      count++;
      if(count>(NUM_SQUARES-1)){
        break;
      }
      humanTurn(ptr_totalMoves, tic_tac_toe, MIN_RANGE_NUM);
      printGrid(tic_tac_toe);
      if(checkWin(tic_tac_toe,HUMAN_SIGN)!=DRAW){
        winner=HUMAN;
        break;
      }
      count++;
    }while(winner==DRAW&&count<=(NUM_SQUARES-1));
  }

  //Congratulate the winner or declare a tie
  if(winner==HUMAN){
    (*humanScore)++;
    cout<<"Congrats human, you won!";
  }
  else if(winner==COMPUTER){
    (*computerScore)++;
    cout<<"The computer won. Better luck next time.";
  }
  else{
    cout<<"It is a tie.";
  }

  // Specification A4 - Play by play

  int person=starter;    //alternates to see who made which move
  cout<<endl;
  cout<<endl<<"Play by Play";
  cout<<endl;
  for(unsigned int i=0; i<totalMoves.length(); i++){
    if(person==HUMAN){
      cout<<"Human's move: ";
      person=COMPUTER;
    }
    else{
      cout<<"Computer's Move:";
      person=HUMAN;
    }
    cout<<" "<<totalMoves[i]<<endl;
  }
  cout<<endl;
}

//Human's turn to make move
void humanTurn(string* humanMoves, string arr[NUM_ROWS][NUM_COLS], const int MIN_RANGE_NUM[NUM_ROWS]){
  int move=0;    //the move that the human made in this turn
  cout<<"What will your move be?";
  cin>>move;
  while(!checkValid(MIN_RANGE_NUM, arr, move)){
    cout<<"Invalid input try again:";
    cin>>move;
  }

  for(int i=0; i<3; i++){
  if(move>=MIN_RANGE_NUM[i]){
      arr[i][(move-MIN_RANGE_NUM[i])]=HUMAN_SIGN;
    }
  }

  *humanMoves+=to_string(move);

}

// Specification C3 - AI
void computerTurn(string* computerMoves, string arr[NUM_ROWS][NUM_COLS], const int MIN_RANGE_NUM[NUM_ROWS]){
  int move=0;    //the move that the computer made in this turn
  do{
    move=getRandNum(NUM_SQUARES);
  }
  while(!(checkValid(MIN_RANGE_NUM, arr, move)));

  cout<<"Computer's Move:"<<move<<endl;

  for(int i=0; i<3; i++){
  if(move>=MIN_RANGE_NUM[i]){
      arr[i][(move-MIN_RANGE_NUM[i])]=COMPUTER_SIGN;
    }
  }

  *computerMoves+=to_string(move);

}

// Specification B4 – Valid Move
bool checkValid(const int MIN_RANGE_NUM[NUM_ROWS], string arr[NUM_ROWS][NUM_COLS], int num){
  if(num<0||num>(NUM_SQUARES-1)){
    return false;
  }

  for(int i=0; i<3; i++){
  if(num>=MIN_RANGE_NUM[i]){
    if((arr[i][(num-MIN_RANGE_NUM[i])]==HUMAN_SIGN)||(arr[i][(num-MIN_RANGE_NUM[i])])==COMPUTER_SIGN){
      return false;
    }
  }
  }
  
  return true;
}

//Function which checks if anyone won
int checkWin(string arr[NUM_ROWS][NUM_COLS], string sign){
  //checks each row
  for(int i=0;i<NUM_ROWS;i++){
    int count1=0;
    for(int j=0;j<NUM_COLS;j++){
      if(arr[i][j]==sign){
        count1++;
      }
      if(count1==3){
        if(sign==HUMAN_SIGN){
        return HUMAN;
        }
        else{
          return COMPUTER;
        }
      }
    }
  }

  //checks each column
  for(int b=0;b<NUM_COLS;b++){
    int count2=0;
    for(int a=0;a<NUM_ROWS;a++){
      if(arr[a][b]==sign){
        count2++;
      }
      if(count2==3){
        if(sign==HUMAN_SIGN){
        return HUMAN;
        }
        else{
          return COMPUTER;
        }
      }
    }
  }

  //checks one diagonal
  int count3=0;
  for(int i=0; i<3; i++){
    if(arr[i][i]==sign){
      count3++;
    }
  }
  if(count3==3){
    if(sign==HUMAN_SIGN){
      return HUMAN;
    }
    else{
      return COMPUTER;
    }
  }

  //checks other diagonal
  int count4=0;
  int j=0;
  for(int i=2; i>=0; i--){
    if(arr[i][j]==sign){
      count4++;
    }
    j++;
  }
  if(count4==3){
    if(sign==HUMAN_SIGN){
      return HUMAN;
    }
    else{
      return COMPUTER;
    }
  }

  return DRAW;
}
