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

    JItem(const char*title):JWidget(title),itemEvent(NULL),mMessageList(NULL),mNextMenu(NULL){}

    ~JItem(){}

    void Set_Event(Item_Sel_Callback func, event_feedback_t* messageList)
    {
        itemEvent = func;

        mMessageList = messageList;
    }

    void Set_Next_Menu(T* next)
    {
        mNextMenu = next;
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

    T* Get_Next_Menu()
    {
        return mNextMenu;
    }

    Item_Sel_Callback Get_Event(void)
    {
        return itemEvent;
    }

private:
    T* mNextMenu;

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
    JWindow(startX,startY,height,width,title),mItemList(NULL),mItemNum(0){}

    ~JMenu(){}

    void Create_Menu(void);

    void Close_Menu(void);

    virtual void Set_Items(JItem<JMenu>** itemList, int32_t num)
    {
        mItemList = itemList;
        mItemNum = num;
    }

    void Add_Item(JItem<JMenu>* lastItem)
    {

    }

    void Set_Last_Menu(JMenu* menu)
    {
        mLastMenu = menu;
    }

    JMenu* Get_Last_Menu(void)
    {
        return mLastMenu;
    }

    JItem<JMenu>** Get_Item_List(void)
    {
        return mItemList;
    }

    WINDOW* Get_Menu_Win(void)
    {
        return mMenuWindow;
    }

    MENU* Get_Menu_List(void)
    {
        return mMenu;
    }

    ITEM** Get_Items(void)
    {
        return mItems;
    }

    int32_t Get_Item_Num(void)
    {
        return mItemNum;
    }

protected:

    WINDOW*     mMenuWindow;        /*the window that associate the menu*/

    MENU*       mMenu;              /*the menu list*/

    ITEM**      mItems;             /*item list used to allocate memory*/

    JItem<JMenu>**      mItemList;
    
    int32_t    mItemNum;

    JMenu* mLastMenu;

};

class JBaseMenu : public JMenu
{
public:
    JBaseMenu(int32_t startX, int32_t startY, uint32_t height, uint32_t width, const char* title):
    JMenu(startX,startY,height,width,title),mCurrentMenu(this),refreshBit(TRUE)
    {}
    
    ~JBaseMenu(){}

    void Display(void);

protected:
    void Switch_Forward(JMenu* newMenu)
    {
        mCurrentMenu->Close_Menu();
        newMenu->Set_Last_Menu(mCurrentMenu);
        mCurrentMenu = newMenu;
        refreshBit = true;
    }

    void Switch_Backward(void)
    {
        mCurrentMenu->Close_Menu();
        mCurrentMenu = mCurrentMenu->Get_Last_Menu();
        refreshBit = true;
    }

    void Refresh_Menu(void)
    {
        mCurrentMenu->Show();
        mCurrentMenu->Create_Menu();
    }

    void Base_Print(const char* content)
    {
        mvprintw(LINES-2,0,content);
        clearFlag = true;
    }

    void Clear_Output(void)
    {
        JPrint("                                       ");
        Base_Print("                                      ");
        refresh();
    }

private:
    JMenu* mCurrentMenu;

    bool refreshBit;

    bool clearFlag;

};

#endif

