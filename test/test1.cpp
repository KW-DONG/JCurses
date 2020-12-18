#include "jmenu.hpp"

//global
//create objects
JMenu baseMenu(10,5,10,40,"main");

JMenu menu1(10,5,10,40,"menu1");
    
JMenu menu2(10,5,10,40,"menu2");

JItem item1("item1");

JItem item2("item2");

JItem item11("item11");

JItem item12("item12");

JItem item21("item21");

JItem item22("item22");

int32_t Item1_Event(JMenu* thisMenu)
{
    Switch_Menu(thisMenu,&menu1);
    return 0;
}

int32_t Item2_Event(JMenu* thisMenu)
{
    Switch_Menu(thisMenu,&menu2);
    return 0;
}

int main()
{
    JInit();

    //add event
    item1.Set_Event(Item1_Event,NULL);
    
    item2.Set_Event(Item2_Event,NULL);

    //set relationships
    menu1.Set_Last(&baseMenu);

    menu2.Set_Last(&baseMenu);

    JItem baseMenuList[] = {item1,item2,(JItem)NULL};

    JItem menu1List[] = {item11,item12,(JItem)NULL};

    JItem menu2List[] = {item21,item22,(JItem)NULL};

    baseMenu.Set_Items(baseMenuList,ARRAY_SIZE(baseMenuList));

    menu1.Set_Items(menu1List,ARRAY_SIZE(menu1List));

    menu2.Set_Items(menu2List,ARRAY_SIZE(menu2List));

    baseMenu.Display();

}






