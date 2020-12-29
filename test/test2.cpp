#include "jform.hpp"
#include <string>

int32_t Field1_Push(char*);
int32_t Field1_Pull(char*);

int32_t Field2_Push(char*);
int32_t Field2_Pull(char*);

int32_t Item2_Event(JMenu* ptr);
int32_t Item12_Event(JMenu* ptr);

char* data1 = NULL;
char* data2 = NULL;

int main()
{
    data1 = "1000";
    data2 = "2000";

    JBaseMenu baseMenu(10,5,20,100,"main");
    JMenu menu1(10,5,20,100,"menu1");
    JForm form1(10,5,20,100,"form1");

    JItem<JMenu> item1("item1");
    JItem<JMenu> item2("item2");
    JItem<JMenu> item11("item11");
    JItem<JMenu> item12("item12");
    JField field1("field1:");
    JField field2("field2:");

    item1.Set_Next_Menu(&menu1);
    item2.Set_Event(Item2_Event,NULL);
    item11.Set_Next_App(&form1);
    item12.Set_Event(Item12_Event,NULL);
    field1.Set_Pull(Field1_Pull,NULL);
    field1.Set_Push(Field1_Push,NULL);
    field2.Set_Pull(Field2_Pull,NULL);
    field2.Set_Push(Field2_Push,NULL);

    JItem<JMenu>* baseMenuList[] = {&item1,&item2};
    JItem<JMenu>* menu1List[] = {&item11,&item12};
    JField* form1List[] = {&field1,&field2};
    
    baseMenu.Set_Items(baseMenuList,ARRAY_SIZE(baseMenuList));
    menu1.Set_Items(menu1List,ARRAY_SIZE(menu1List));
    form1.Set_Fields(form1List,ARRAY_SIZE(form1List));
    
    JInit();
    baseMenu.Display();
    refresh();
    endwin();
    return 0;
}

int32_t Field1_Push(char* text)
{
    data1 = text;
}

int32_t Field1_Pull(char* text)
{
    text = data1;
}

int32_t Field2_Push(char* text)
{
    text = data2;
}

int32_t Field2_Pull(char* text)
{
    data2 = text;
}

int32_t Item2_Event(JMenu* ptr)
{
    JPrint(data2);
}

int32_t Item12_Event(JMenu* ptr)
{
    JPrint(data1);
}