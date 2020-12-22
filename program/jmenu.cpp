#include "jmenu.hpp"
#include <stdlib.h>
//#include <cstring>

void JMenu::Create_Menu(void)
{    
    mItems = (ITEM**)new ITEM* [mItemNum];
    
    for(int i = 0; i < mItemNum; ++i)
    {
        mItems[i] = new_item(mItemList[i].Get_Title()," ");
    }

    mMenu = new_menu((ITEM**)mItems);

    int32_t menuStartX = Get_W()/3;

    int32_t menuWinWidth = Get_W() - menuStartX - 3;

    mMenuWindow = derwin(Get_Base_Window(),Get_H()-3,menuWinWidth,2,menuStartX);

    set_menu_sub(mMenu, mMenuWindow);

    set_menu_format(mMenu,Get_H()-4,1);

    set_menu_mark(mMenu,"->");

}

void JMenu::Display(void)
{
    int c;

    Create_Menu();

    Show();

    post_menu(mMenu);

    //wrefresh(Get_Base_Window());

    wrefresh(mMenuWindow);

    while((c = wgetch(Get_Base_Window())) != KEY_F(1))
    {
        switch (c)
        {
        case KEY_DOWN:

            menu_driver(mMenu, REQ_DOWN_ITEM);
            break;
        
        case KEY_UP:
            menu_driver(mMenu, REQ_UP_ITEM);
            break;

        case KEY_NPAGE:
            menu_driver(mMenu, REQ_SCR_DPAGE);
            break;

        case KEY_PPAGE:
            menu_driver(mMenu, REQ_SCR_UPAGE);
            break;
        
        case KEY_LEFT:
            if (this->mLastMenu != NULL)    Change_Page(this,mLastMenu);
            break;
        
        case KEY_RIGHT:
            {
                ITEM *cur;

                cur = current_item(mMenu);
                if (mItemList[cur->index].Get_Event()!= NULL)
                Print(mItemList[cur->index].Selected(this));

                pos_menu_cursor(mMenu);
                break;
            }
            break;
        }
        wrefresh(mMenuWindow);
        wrefresh(Get_Base_Window());
    }
    
    //Close all menus
    JMenu* last;
    last = mLastMenu;
    while(last->mLastMenu!=NULL)
    {
        last->Close();
        last = last->mLastMenu;
    }
    Close();
}

void JMenu::Close(void)
{
    unpost_menu(mMenu);
    free_menu(mMenu);
    for (int32_t i = 0; i < mItemNum; ++i)
    {
       free_item(mItems[i]); 
    }
    delete[] mItems;

    mItems = NULL;
}

int32_t Change_Page(JMenu* currentMenu, JMenu* nextMenu)
{
    nextMenu->Display();
    currentMenu->Close();
    return 0;
}


