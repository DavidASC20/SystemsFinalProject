#include <ncurses.h>

int main() {

  initscr(); // creates stdscr
  refresh();
  noecho();

  getch();
  endwin();
  return 0;

}
