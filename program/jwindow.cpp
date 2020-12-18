#include "jwindow.hpp"
#include <stdlib.h>
#include <cstring>

void JInit()
{
    initscr();
    //start_color();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
}

void JWindow::Show(void)
{
    /*display title*/
    int length = strlen(mTitle);
    float temp = (w - length)/ 2;

    //mvprintw(y,x+(int)temp,"%s",mTitle);

    //mvwaddch(mBaseWindow, 2, 0, ACS_LTEE);

    //mvwhline(mBaseWindow, 2, 1, ACS_HLINE, w - 2);

    //mvwaddch(mBaseWindow, 2, w-1, ACS_RTEE);

    refresh();

    /*create window*/
    mBaseWindow = newwin(h,w,y,x);

    wborder(mBaseWindow, '|', '|', '-', '-', '+', '+', '+', '+');

    mvwprintw(mBaseWindow, 0, (int)temp, "[%s]", mTitle);

    //box(mBaseWindow, 0, 0);

    keypad(mBaseWindow, TRUE);

}

const char* JWidget::Get_Feedback(int32_t feedback, event_feedback_t* messageList)
{
    static const char noFeedback[] = "no feedback";

    int32_t messageNum = sizeof(messageList);

    for (int32_t i = 0; i < messageNum; i++)
    {
        if (feedback == i)
        {
            return messageList[i].message;
        }
    }
    return noFeedback;
}