#include <ncurses.h>

int main() {
  /*
  initscr(); // creates stdscr
  cbreak(); // for testing (allows for user to ctrlx out of the program)
  raw(); // does not allow ctrlx
  refresh(); // allows for the screen to be refreshed (for realtime updates?)

  noecho(); // keeps the program from printing input twice

  attron(stuff); // changes the ways the word is being displayed (attribute on)
  attroff(stuff); // turns attribute off

  printw(); // printf() equivalent

  getch(); // waits for user input, returns what the user input value is
  addch('a'); // adds whatever letter you want
  printw(const char *); // prints string to the screen

  move(y, x); // changes position of cursor to wherever you decide
  mvprintw(y, x, printstuff); // moves cursor and prints after in one command

  WINDOW * win = newwin(height, width, starty, startx); // makes window
  wmove(window, y, x); // moves window

  */
  initscr(); // creates stdscr
  refresh();
  noecho();

  /* //Run this section to see how to print stuff and how to do basic interactions
  int x, y;
  x = y = 10;

  move(y, x);
  printw("Hello World!");

  // type a character on the terminal
  refresh();
  int c = getch();
  mvprintw(0, 0, "%d", c);
  */

  int height, width, startY, startX;

  height = 10;
  width = 20;
  startY = startX = 10;




  // run this to make a window
  WINDOW * win = newwin(height, width, startY, startX);
  refresh();

  box(win, 0, 0);
  wrefresh(win);

  int c = getch();

  mvprintw(0, 0,"%d", c);


  /*
  attron(A_STANDOUT | A_UNDERLINE);
  printw(" %d", c);
  attroff(A_STANDOUT | A_UNDERLINE);
  addch('a');
  */

  getch();
  endwin();
  return 0;

}
