#include "jmenu.hpp"

int32_t Item1_Event(void)
{
    mvprintw(1,1,"this is item1");
    refresh();
    return 0;
}

int32_t Item2_Event(void)
{
    mvprintw(1,1,"this is item2");
    refresh();
    return 0;
}
int32_t Item3_Event(void)
{
    mvprintw(1,1,"this is item3");
    refresh();
    return 0;
}
int32_t Item4_Event(void)
{
    mvprintw(1,1,"this is item4");
    return 0;
}
int32_t Item5_Event(void)
{
    mvprintw(1,1,"this is item5");
    return 0;
}
int32_t Item6_Event(void)
{
    mvprintw(1,1,"this is item6");
    return 0;
}

int main()
{
    JInit();

    //create objects
    JMenu baseMenu(10,5,10,40,"main");

    JItem item1("item1");

    JItem item2("item22");

    JItem item3("item333");

    JItem item4("item4444");

    JItem item5("item55555");

    JItem item6("item666666");

    //add event
    item1.Set_Event(Item1_Event,NULL);
    item2.Set_Event(Item2_Event,NULL);
    item3.Set_Event(Item3_Event,NULL);
    item4.Set_Event(Item4_Event,NULL);
    item5.Set_Event(Item5_Event,NULL);
    item6.Set_Event(Item6_Event,NULL);

    //set relationships

    JItem baseMenuList[] = {item1,item2,item3,item4,item5,item6,(JItem)NULL};

    baseMenu.Add_Items(baseMenuList,ARRAY_SIZE(baseMenuList));

    baseMenu.Display();

}