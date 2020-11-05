#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main(void){
	char mesg[]="Just a string";
	int row,col;
	int a,b;

	initscr();
	getmaxyx(stdscr,row,col);
	srand(time(NULL));
	a = rand() % row;
	b = rand() % col;

	mvprintw(a,(b-strlen(mesg)),"%s",mesg);



	mvprintw(row-2,0,"This screen has %d rows and %d columns\n",row,col);
	printw("Try resizing your window(if possible) and then run this program again");
	refresh();
	getch();
	endwin();


	return 0;
}
