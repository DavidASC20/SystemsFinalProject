#include "pipe_networking.h"

int main() {

  int sd;

  int clients[2];

  sd = server_setup();

  while(1){
    clients[0] = server_connect(sd);
    clients[1] = server_connect(sd);

    char line[1000];
    int f = fork();
    if(f) {
      close(clients[0]);
      close(clients[1]);
    }
    else {
      // create randomized board
      srand(time(NULL));
      int board[7][8];
      for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 8; j++) {
          board[i][j] = rand() % 6;
        }
      }

      for(int i = 0; i < 2; i++) {
        writeint(clients[i], i);  // send clients index
        write(clients[i], board, 7*8*sizeof(int));
      }
    //  board[6][0] and board[0][7]

      // 2nd phase - playing game
      int turn = 0;
      int color;
      int cont;
      int territory[2][7][8];
      for(int p = 0; p < 2; p++) {
        for(int i = 0; i < 7; i++) {
          for(int j = 0; j < 8; j++) {
            territory[p][i][j] = 0;
          }
        }
      }
      territory[0][6][0] = 1;
      territory[1][0][7] = 1;
      while(1) {
        read(clients[turn], &color, sizeof(int));

        for(int i = 0; i < 7; i++) {
          for(int j = 0; j < 8; j++) {
            if(territory[turn][i][j]) board[i][j] = color;
          }
        }
        cont = 1;
        while(cont) {
          cont = 0;
          for(int i = 0; i < 7; i++) {
            for(int j = 0; j < 8; j++) {
              if(!territory[turn][i][j] && color == board[i][j]) {
                if(i > 0 && territory[turn][i-1][j]) territory[turn][i][j] = 1;
                if(i < 6 && territory[turn][i+1][j]) territory[turn][i][j] = 1;
                if(j > 0 && territory[turn][i][j-1]) territory[turn][i][j] = 1;
                if(j < 7 && territory[turn][i][j+1]) territory[turn][i][j] = 1;

                if(territory[turn][i][j]) cont = 1;
            }
          }
        }

      }
      // 3rd phase - send who won, etc.

      exit(0);
    }
  }
}