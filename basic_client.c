#include "pipe_networking.h"

int sock;
int ind;
int board[7][8];
int territory[2][7][8];
int boardstate;
int color;
int result;
int startpos[2][2] = {{6, 0}, {0, 7}};
int xoff = 0, yoff = 20;
int xsize = 3, ysize = 5;
int curoption;

void initcurses();
void exitcurses();
int getcolor();
void displayboard();
void displaysquare(int i, int j);
void displaypointers();
void displayoptions();
void printmessage();

int main() {

  printf("Enter ip: ");
  char ip[1000];
  fgets(ip, sizeof(ip), stdin);
  if (strchr(ip, '\n')) {
    *strchr(ip, '\n') = 0;
  }
  printf("Connecting to server...\n");
  sock = client_handshake(ip);
  printf("Connected to server, waiting for game to start...\n");


  read(sock, &ind, sizeof(int));
  read(sock, board, 7*8*sizeof(int));
  read(sock, territory, 2*7*8*sizeof(int));
  initcurses();
  displayboard();

  while(1) {      //while boardstate == 0 , see what server is doing and mimic on the other end
    if (ind==0) {
      color = getcolor();
      writeint(sock, color);
    } else {
      move(22, 30);
      printw("Waiting for opponent...");
      refresh();
    }
    read(sock, &boardstate, sizeof(int));
    read(sock, board, 7*8*sizeof(int));
    read(sock, territory, 2*7*8*sizeof(int));
    if (boardstate==1) break;
    displayboard();
    if (ind==1) {
      color = getcolor();
      writeint(sock, color);
    } else {
      move(22, 30);
      printw("Waiting for opponent...");
      refresh();
    }
    read(sock, &boardstate, sizeof(int));
    read(sock, board, 7*8*sizeof(int));
    read(sock, territory, 2*7*8*sizeof(int));
    if (boardstate==1) break;
    displayboard();
  }
  read(sock, &result, sizeof(int));
  exitcurses();
  if (result==1) {
    printf("You Won!!!\n");
  } else if (result==-1) {
    printf("You Lost.\n");
  } else if (result==0) {
    printf("You Drew.\n");
  }
  return 0;
}

void initcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);

  start_color();
  init_pair(1, COLOR_WHITE, COLOR_GREEN);
  init_pair(2, COLOR_WHITE, COLOR_RED);
  init_pair(3, COLOR_WHITE, COLOR_YELLOW);
  init_pair(4, COLOR_WHITE, COLOR_BLUE);
  init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(6, COLOR_WHITE, COLOR_CYAN);
}

void exitcurses() {
  curs_set(1);
  endwin();
  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
}

int getcolor() {
  int ch;
  displayboard();
  while (1) {
    displayoptions();
    int ch = getch();
    if ((ch==KEY_LEFT || ch=='a') && curoption>0) {
      curoption--;
    } else if ((ch==KEY_RIGHT || ch=='d') && curoption<5) {
      curoption++;
    } else if (ch=='\n') {
      if (curoption != board[6][0] && curoption != board[0][7]) {
        return curoption;
      } else {
        printmessage();
      }
    }
  }
}

void displayboard() {
  clear();
  for (int i = 0; i < 7; i++) for (int j = 0; j < 8; j++) displaysquare(i, j);
  displaypointers();
  refresh();
}

void displaysquare(int i, int j) {
  attron(COLOR_PAIR(board[i][j]+1));
  for (int k = 0; k < xsize; k++) {
    mvhline(xsize*i+xoff+k, ysize*j+yoff, ' ', ysize);
  }
  attroff(COLOR_PAIR(board[i][j]+1));
}

void displaypointers() {
  for (int i = 0; i < 2; i++) {
    int x = startpos[i][0], y = startpos[i][1];
    attron(COLOR_PAIR(board[x][y]+1));
    move(xsize*x + xoff + 1, ysize*y + yoff + 1);
    if (i==ind) addstr("YOU");
    else addstr("OPP");
    attroff(COLOR_PAIR(board[x][y]+1));
  }
}

void displayoptions() {
    for (int i = 0; i < 6; i++) {
        attron(COLOR_PAIR(i+1));
        mvhline(xsize*7 + xoff + 1, 6*i + yoff+4, ' ', 2);
        attroff(COLOR_PAIR(i+1));
        mvhline(xsize*7 + xoff + 1, 6*i + yoff + 6, ' ', 4);
    }
    move(xsize*7 + xoff + 1, 6*curoption + yoff + 6);
    addstr("<==");
    refresh();
}

void printmessage() {
  move(23, 0);
  addstr("Pick a color neither you nor your opponent occupies");
  refresh();
}
