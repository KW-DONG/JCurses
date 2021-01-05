#include "jmenu.hpp"
#include <array>

int32_t Item11_Event(JMenu* ptr)
{
    mvprintw(0,0,"item11");
    return 0;
}

int32_t Item12_Event(JMenu* ptr)
{
    mvprintw(0,0,"item12");
    return 0;
}

int32_t Item21_Event(JMenu* ptr)
{
    mvprintw(0,0,"item21");
    return 0;
}

int32_t Item22_Event(JMenu* ptr)
{
    mvprintw(0,0,"item22");
    return 0;
}

int main()
{
    JBaseMenu baseMenu(10,5,10,40,"main");

    JMenu menu1(10,5,10,40,"menu1");

    JMenu menu2(10,5,10,40,"menu2");

    JItem<JMenu> item1("item1");

    JItem<JMenu> item2("item2");

    JItem<JMenu> item3("item3");

    JItem<JMenu> item4("item4");

    JItem<JMenu> item11("item11");

    JItem<JMenu> item12("item12");

    JItem<JMenu> item21("item21");

    JItem<JMenu> item22("item22");
    
    JInit();

    //add event
    item1.Set_Next_Menu(&menu1);
    item2.Set_Next_Menu(&menu2);
    item11.Set_Event(Item11_Event,NULL);
    item12.Set_Event(Item12_Event,NULL);
    item21.Set_Event(Item21_Event,NULL);
    item22.Set_Event(Item22_Event,NULL);

    std::array<JItem<JMenu>*,3> baseList = {&item1,&item2,&item3};

    JItem<JMenu>* baseMenuList[] = {&item1,&item2,&item3};

    JItem<JMenu>* menu1List[] = {&item11,&item12};

    JItem<JMenu>* menu2List[] = {&item21,&item22};

    //baseMenu.Set_Items(baseMenuList,ARRAY_SIZE(baseMenuList));

    baseMenu.Set_Items(baseList.data(),baseList.size());

    menu1.Set_Items(menu1List,ARRAY_SIZE(menu1List));

    menu2.Set_Items(menu2List,ARRAY_SIZE(menu2List));

    baseMenu.Display();

    refresh();

    endwin();

    return 0;

}