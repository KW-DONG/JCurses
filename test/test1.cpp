#include "jmenu.hpp"

JMenu baseMenu(10,5,10,40,"main");

JMenu menu1(10,5,10,40,"menu1");

JMenu menu2(10,5,10,40,"menu2");

JItem<JMenu> item1("item1");

JItem<JMenu> item2("item2");

JItem<JMenu> item11("item11");

JItem<JMenu> item12("item12");

JItem<JMenu> item21("item21");

JItem<JMenu> item22("item22");

int32_t Item1_Event(JMenu* ptr)
{
    return Change_Page(ptr,&menu1);
}

int32_t Item2_Event(JMenu* ptr)
{
    return Change_Page(ptr,&menu2);
}

int32_t Item11_Event(JMenu* ptr)
{
    mvprintw(0,0,"item11");
    refresh();
    return 0;
}

int32_t Item12_Event(JMenu* ptr)
{
    mvprintw(0,0,"item12");
    refresh();
    return 0;
}

int32_t Item21_Event(JMenu* ptr)
{
    mvprintw(0,0,"item21");
    refresh();
    return 0;
}

int32_t Item22_Event(JMenu* ptr)
{
    mvprintw(0,0,"item22");
    refresh();
    return 0;
}

int main()
{
    JInit();

    //add event
    item1.Set_Event(Item1_Event,NULL);
    item2.Set_Event(Item2_Event,NULL);
    item11.Set_Event(Item11_Event,NULL);
    item12.Set_Event(Item12_Event,NULL);
    item21.Set_Event(Item21_Event,NULL);
    item22.Set_Event(Item22_Event,NULL);

    JItem<JMenu> baseMenuList[] = {item1,item2,(JItem<JMenu>)NULL};

    JItem<JMenu> menu1List[] = {item11,item12,(JItem<JMenu>)NULL};

    JItem<JMenu> menu2List[] = {item21,item22,(JItem<JMenu>)NULL};

    baseMenu.Add_Items(baseMenuList,ARRAY_SIZE(baseMenuList));

    menu1.Add_Items(menu1List,ARRAY_SIZE(menu1List));

    menu1.Add_Last(&baseMenu);

    menu2.Add_Items(menu2List,ARRAY_SIZE(menu2List));

    menu2.Add_Last(&baseMenu);

    baseMenu.Display();

}