#ifndef __JMENU_HPP
#define __JMENU_HPP
#include <menu.h>
#include "jwindow.hpp"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define MIDDLE_WIN_X(x,w) (x+w/2)

typedef int32_t (*Item_Sel_Callback)(void);

class JItem : public JWidget
{
public:
    JItem(const char*title):JWidget(title),itemEvent(NULL),mMessageList(NULL){}

    ~JItem(){}

    void Set_Event(Item_Sel_Callback func, event_feedback_t* messageList)
    {
        itemEvent = func;

        mMessageList = messageList;
    }

    const char* Selected(void)
    {
        if (mMessageList!=NULL)
        {
           return Get_Feedback(itemEvent(),mMessageList); 
        }
        else
        {
            itemEvent();
            return "Selected";
        }
    }

    Item_Sel_Callback Get_Event(void)
    {
        return itemEvent;
    }

private:
    int32_t (*itemEvent)(void);      /*write an event here*/

    event_feedback_t* mMessageList;
};

/**
 * +--------[Title]--------+
 * |    +----------+       |
 * |    |          |       |
 * |    |  Menus   |       |
 * |    |          |       |
 * |    |          |       |
 * |    +----------+       |
 * +-----------------------+
 */

class JMenu : public JWindow
{
public:

    JMenu(int32_t startX, int32_t startY, uint32_t height, uint32_t width, const char* title):
    JWindow(startX,startY,height,width,title),mItemList(NULL),mLastMenu(NULL),mItemNum(0){}

    ~JMenu(){}

    void Display(void) override;

    void Close(void) override;

    virtual void Add_Items(JItem* itemList, int32_t num)
    {
        mItemList = itemList;
        mItemNum = num;
    }

    void Add_Last(JMenu* lastMenu)
    {
        mLastMenu = lastMenu;
    }

protected:

    void Create_Menu(void);

private:
    
    WINDOW*     mMenuWindow;        /*the window that associate the menu*/

    MENU*       mMenu;              /*the menu list*/

    ITEM**      mItems;             /*item list used to allocate memory*/

    JItem*      mItemList;
    
    int32_t    mItemNum;

    JMenu*      mLastMenu;

};



#endif

