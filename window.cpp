#include "window.h"
#include <ncurses.h>
#include <unistd.h>

Window::Window()
{
    initWindow();
}
Window::~Window()
{
    endwin();
}

void Window::initWindow()
{
    initscr();
    noecho();
    curs_set(FALSE);
    clear();
    refresh();
}

void Window::updateWindow(int q[6], int p){
    clear();
    for(int i = 0; i <= 5; i++){
        mvprintw(1,4*i,"%d|",q[i]);
    }
    mvprintw(3,4," %d|^^|",p);
    refresh();
}
