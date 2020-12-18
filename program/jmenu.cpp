#include "jmenu.hpp"
#include <stdlib.h>
//#include <cstring>

void JMenu::Create_Menu(void)
{
    //mItems = (ITEM **)calloc(mItemNum,sizeof(ITEM *));
    
    mItems = (ITEM**)new ITEM* [mItemNum];
    
    for(int i = 0; i < mItemNum; ++i)
    {
        mItems[i] = new_item(mItemList[i].Get_Title()," ");

        //set_item_userptr(mItems[i],(void*)(mItemList[i].Selected()));
    }

    //mItems[mItemNum] = new_item((char*)NULL,(char*)NULL);

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

    int32_t i = 0;

    this->Create_Menu();

    Show();

    wrefresh(Get_Base_Window());

    refresh();

    box(mMenuWindow,0,0);

    post_menu(mMenu);

    wrefresh(mMenuWindow);

    while((c = wgetch(Get_Base_Window())) != KEY_F(1))
    {
        switch (c)
        {
        case KEY_DOWN:

            menu_driver(mMenu, REQ_DOWN_ITEM);
            if (i<mItemNum) i++;
            break;
        
        case KEY_UP:
            if (i>0)    i--;
            menu_driver(mMenu, REQ_UP_ITEM);
            break;

        case KEY_NPAGE:
            menu_driver(mMenu, REQ_SCR_DPAGE);
            break;

        case KEY_PPAGE:
            menu_driver(mMenu, REQ_SCR_UPAGE);
            break;
        
        case KEY_LEFT:
            if (this->mLastMenu != NULL)
            {
                this->mLastMenu->Display();
                this->Close();
            }
            break;
        
        case KEY_RIGHT:
            {
                ITEM *cur;

                //int8_t (*p)(void);
                cur = current_item(mMenu);       /*get curren selection*/
                if (mItemList[cur->index].Get_Event()!= NULL)
                Print(mItemList[cur->index].Selected());
                
                //p = (int8_t(*)(void))item_userptr(cur);
                pos_menu_cursor(mMenu);
                break;
            }
            break;
        }
        wrefresh(mMenuWindow);
        wrefresh(Get_Base_Window());
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
    //free(mItems);
    mItems = NULL;
}


