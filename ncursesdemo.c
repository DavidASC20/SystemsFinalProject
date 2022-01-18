#include <ncurses.h>

int main() {
  initscr(); // creates stdscr
  //cbreak() for testing (allows for user to ctrlx out of the program)
  raw(); // does not allow ctrlx
  int derp = 4;
  attron(A_STANDOUT | A_UNDERLINE);
  printw("This is a bog standard string output %d", derp);
  attroff(A_STANDOUT | A_UNDERLINE);
  addch('a');
  move(12,13);
  mvprintw(15,20, "Movement");
  mvaddch(12, 50, getch());
  getch();
  endwin();
  return 0;

}
