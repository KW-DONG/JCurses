#ifndef __JMENU_HPP
#define __JMENU_HPP
#include <menu.h>
#include "jwindow.hpp"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define MIDDLE_WIN_X(x,w) (x+w/2)

//T = JMenu
template <class T>
class JItem : public JWidget
{
public:
    typedef int32_t (*Item_Sel_Callback)(T* menuPtr);

    JItem(const char*title):JWidget(title),itemEvent(NULL),mMessageList(NULL){}

    ~JItem(){}

    void Set_Event(Item_Sel_Callback func, event_feedback_t* messageList)
    {
        itemEvent = func;

        mMessageList = messageList;
    }

    const char* Selected(T* menuPtr)
    {
        if (mMessageList!=NULL)
        {
           return Get_Feedback(itemEvent(menuPtr),mMessageList); 
        }
        else
        {
            itemEvent(menuPtr);
            return "Selected";
        }
    }

    Item_Sel_Callback Get_Event(void)
    {
        return itemEvent;
    }

private:
    int32_t (*itemEvent)(T* menuPtr);      /*write an event here*/

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

    virtual void Add_Items(JItem<JMenu>* itemList, int32_t num)
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

    JItem<JMenu>*      mItemList;
    
    int32_t    mItemNum;

    JMenu*      mLastMenu;
};

int32_t Change_Page(JMenu* currentMenu, JMenu* nextMenu);

#endif

