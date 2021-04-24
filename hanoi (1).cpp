#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

int NUMDISKS = 20;

int ** init_board(){
  int **board, i;
  board = new int*[NUMDISKS];

  for (i = 0; i < NUMDISKS; i++){
    board[i] = new int[3];
  }

  for (i = 0; i < NUMDISKS; i++){
    board[i][0] = i + 1;
  }

  return board;
}

void myPrint(int d)
{
  int diskSize = d;
  int fullSize = NUMDISKS * 2;

  int buffer = (fullSize - diskSize*2) / 2;

  for (int i = 0; i < buffer; ++i)
    printf(" ");
  printf("\E[37;45m");
  for (int i = 0; i < diskSize; ++i)
    printf("_");
  printf("|");
  for (int i = 0; i < diskSize; ++i)
    printf("_");
  printf("\E[0m");
  for (int i = 0; i < buffer; ++i)
    printf(" ");

}

void print_board(int ** b){
  int i = 0;
  int j = 0;
  system ("sleep .1");
  system ("clear");
  for (i = 0; i < NUMDISKS; i ++){
    for (j = 0; j < 3; j++){
      myPrint(b[i][j]);
      // if (b[i][j] != 0){
      //   printf("|%d|", b[i][j]);
      // }
      // else{
      //   printf("   ");
      // }
    } 
    printf("\n");
  }
  printf("\n\n");
}

void move(int disks, int ** board, int from_col, int to_col){
  int i = 0, j = 0;

  for (i = 0; i < NUMDISKS; i++){
    if (board[i][from_col] != 0){
      break;
    }
  }
  for (j = 0; j < NUMDISKS; j++){
    if (board[j][to_col] != 0){
      break;
    }
  }
  j--;

  board[j][to_col] = board[i][from_col];
  board[i][from_col] = 0;
}

void towers(int disks, int **b, int from_col, int to_col, int spare){
  if(disks >= 1){
    towers(disks - 1, b, from_col, spare, to_col);
    move(disks -1, b, from_col, to_col);
    print_board(b);
    towers(disks - 1, b, spare, to_col, from_col);
  }

}

int main(int argc, char** argv){
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  NUMDISKS = ((w.ws_col / 3) / 2) -3;

  // printf("%d\n", w.ws_row);
  // exit(0);

  int ** board = init_board();
  print_board(board);


  towers(NUMDISKS, board, 0, 2, 1);

  return 0;
}
