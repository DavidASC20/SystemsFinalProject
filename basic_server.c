#include "pipe_networking.h"


int sd;
int clients[2];

int board[7][8];
int turn = 0;
int color;
int cont;
int territory[2][7][8];
int count[2];

void execgame();
void extend(int t, int c);

int main() {

  sd = server_setup();

  while(1){
    clients[0] = server_connect(sd);
    clients[1] = server_connect(sd);

    int f = fork();
    if(f) {
      close(clients[0]);
      close(clients[1]);
    }
    else {
      execgame();
    }
  }
}

void execgame() {
  // create randomized board
  srand(time(NULL));
  for(int i = 0; i < 7; i++) {
    for(int j = 0; j < 8; j++) {
      board[i][j] = rand() % 6;
    }
  }
  while (board[6][0]==board[0][7]) board[0][7] = rand()%6;

  // 2nd phase - playing game
  for(int p = 0; p < 2; p++) {
    for(int i = 0; i < 7; i++) {
      for(int j = 0; j < 8; j++) {
        territory[p][i][j] = 0;
      }
    }
  }
  territory[0][6][0] = 1;
  territory[1][0][7] = 1;
  extend(0, board[6][0]);
  extend(1, board[0][7]);

  for(int i = 0; i < 2; i++) {
    writeint(clients[i], i);  // send clients index
    write(clients[i], board, 7*8*sizeof(int));
    write(clients[i], territory, 2*7*8*sizeof(int));
  }

  count[0] = 1;
  count[1] = 1;
  while(1) {
    read(clients[turn], &color, sizeof(int));

    for(int i = 0; i < 7; i++) {
      for(int j = 0; j < 8; j++) {
        if(territory[turn][i][j]) board[i][j] = color;
      }
    }
    extend(turn, color);

    if(count[0]>28 || count[1]>28){
      break;
    } else if(count[0] == 28 && count[1] == 28){
      break;
    }
    turn = 1 - turn;
    writeint(clients[0], 0);
    write(clients[0], board, 7*8*sizeof(int));
    write(clients[0], territory, 2*7*8*sizeof(int));
    writeint(clients[1], 0);
    write(clients[1], board, 7*8*sizeof(int));
    write(clients[1], territory, 2*7*8*sizeof(int));
  }
  // 3rd phase - send who won, etc.
  writeint(clients[0], 1);
  write(clients[0], board, 7*8*sizeof(int));
  write(clients[0], territory, 2*7*8*sizeof(int));
  writeint(clients[1], 1);
  write(clients[1], board, 7*8*sizeof(int));
  write(clients[1], territory, 2*7*8*sizeof(int));
  if(count[0] > 28){
    writeint(clients[0], 1);
    writeint(clients[1], -1);
  }else if(count[1] > 28){
    writeint(clients[0], -1);
    writeint(clients[1], 1);
  }else{
    writeint(clients[0], 0);
    writeint(clients[1], 0);
  }
  exit(0);
}

void extend(int t, int c) {
    cont = 1;
    while(cont) {
      cont = 0;
      for(int i = 0; i < 7; i++) for(int j = 0; j < 8; j++) {
        if(!territory[t][i][j] && c == board[i][j]) {
          if(i > 0 && territory[t][i-1][j]) territory[t][i][j] = 1;
          if(i < 6 && territory[t][i+1][j]) territory[t][i][j] = 1;
          if(j > 0 && territory[t][i][j-1]) territory[t][i][j] = 1;
          if(j < 7 && territory[t][i][j+1]) territory[t][i][j] = 1;

          if(territory[t][i][j]){
            cont = 1;
            count[t]++;
          }
        }
      }
    }
}
