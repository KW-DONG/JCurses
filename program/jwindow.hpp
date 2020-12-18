#ifndef __JWINDOW_HPP
#define __JWINDOW_HPP
#include <ncurses.h>

/**
 *                 w
 *      +---------------------+
 *      |        Title        |
 *      +---------------------+
 *      |                     |
 *      |                     |
 *      |                     |
 *      |                     |
 *      +---------------------+
 * @brief Window base class includes size and location
 */
class JWindow
{
public:
    JWindow(int32_t startX, int32_t startY, int32_t height, int32_t width, const char* title):
    x(startX),y(startY),h(height),w(width),mTitle(title)
    {
        mBaseWindow = newwin(h,w,y,x);
    }
    ~JWindow()
    {
        wborder(mBaseWindow, ' ', ' ', ' ',' ',' ',' ',' ',' ');
        wrefresh(mBaseWindow);
        delwin(mBaseWindow);
        endwin();
    }

    virtual void Display(){}

    virtual void Close(){}

    int32_t Get_X(void) {return x;}

    int32_t Get_Y(void) {return y;}

    int32_t Get_W(void) {return w;}

    int32_t Get_H(void) {return h;}

    WINDOW* Get_Base_Window(void)   {return mBaseWindow;}

    void Print(const char* content)
    {
        mvprintw(LINES - 2,0,content);
    }

protected:

    void Show(void);            /*show title and box*/

    void Terminal_Print(const char* text);

private:
    
    WINDOW* mBaseWindow;        /*the main window*/

    const int32_t h;            /*current window height*/
    
    const int32_t w;            /*current window width*/
    
    const int32_t x;            /*current window start position*/
    
    const int32_t y;            /*current window start position*/
    
    const char* mTitle;         /*current menu title and item title*/

};

typedef struct 
{
    int32_t num;
    const char* message;
}event_feedback_t;

/**
 * @brief widget base class
 * 
 */

class JWidget
{
public:
    JWidget(const char* title):mTitle(title),mWidth(sizeof(title)){};
    ~JWidget(){}

    const char* Get_Title(void)
    {
        return mTitle;
    }
    const int32_t Get_Width(void)
    {
        return mWidth;
    }

protected:
    const char* Get_Feedback(int32_t feedback, event_feedback_t* messageList);

private:
    const char* mTitle;
    const int32_t mWidth;
};

/**
 * @brief JCurses initialization function
 * @note call it as initialization
 */
void JInit(void);

#endif