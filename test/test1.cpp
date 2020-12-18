#include "jmenu.hpp"

int main()
{
    JInit();

    //create objects
    JMenu baseMenu(10,5,10,40,"main");

    JItem item1("item1");

    JItem item2("item2");

    JItem item3("item3");

    JItem item4("item4");

    JItem item5("item5");

    JItem item6("item6");

    //add event


    //set relationships

    JItem baseMenuList[] = {item1,item2,item3,item4,item5,item6,(JItem)NULL};

    baseMenu.Add_Items(baseMenuList,ARRAY_SIZE(baseMenuList));

    baseMenu.Display();

}