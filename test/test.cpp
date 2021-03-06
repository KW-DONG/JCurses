#include "jform.hpp"
#include "snake.hpp"
#include <string>

int32_t Field1_Push(std::string&);
int32_t Field1_Pull(std::string&);

int32_t Field2_Push(std::string&);
int32_t Field2_Pull(std::string&);

int32_t Field3_Push(std::string&);
int32_t Field3_Pull(std::string&);

int32_t Item2_Event(JMenu* ptr);
int32_t Item12_Event(JMenu* ptr);

std::string data1("123456");
std::string data2("654321");

int main()
{
    JBaseMenu baseMenu(30,2,20,40,"main");
    JMenu menu1(30,2,20,40,"menu1");
    JMenu menu13(30,2,40,40,"menu13");
    JForm form1(30,2,20,40,"form1");
    JSnake snake(30,2,20,40,"snake");

    JItem<JMenu> item1("form menu");
    JItem<JMenu> item2("print field2");
    JItem<JMenu> item3("snake");
    JItem<JMenu> item4("nothing");
    JItem<JMenu> item5("nothing2");
    JItem<JMenu> item11("show form");
    JItem<JMenu> item12("print field1");
    JItem<JMenu> item13("something");
    JItem<JMenu> item131("aaa");
    JItem<JMenu> item132("bbb");
    JItem<JMenu> item133("ccc");
    JItem<JMenu> item134("ddd");
    JField field1("field1:");
    JField field2("field2:");
    JField field3("field3:");

    item1.Set_Next_Menu(&menu1);
    item2.Set_Event(Item2_Event,NULL);
    item11.Set_Next_App(&form1);
    item12.Set_Event(Item12_Event,NULL);
    item3.Set_Next_App(&snake);
    item13.Set_Next_Menu(&menu13);

    field1.Set_Pull(Field1_Pull,NULL);
    field1.Set_Push(Field1_Push,NULL);
    field2.Set_Pull(Field2_Pull,NULL);
    field2.Set_Push(Field2_Push,NULL);
    field3.Set_Pull(Field3_Pull,NULL);
    field3.Set_Push(Field3_Push,NULL);

    JItem<JMenu>* baseMenuList[] = {&item1,&item2,&item3,&item4,&item5};
    JItem<JMenu>* menu1List[] = {&item11,&item12,&item13};
    JItem<JMenu>* menu13List[] = {&item131,&item132,&item133,&item134};
    JField* form1List[] = {&field1,&field2,&field3};
    
    baseMenu.Set_Items(baseMenuList,ARRAY_SIZE(baseMenuList));
    menu1.Set_Items(menu1List,ARRAY_SIZE(menu1List));
    menu13.Set_Items(menu13List,ARRAY_SIZE(menu13List));
    form1.Set_Fields(form1List,ARRAY_SIZE(form1List));
    
    JInit();
    baseMenu.Display();
    refresh();
    endwin();
    return 0;
}

int32_t Field1_Push(std::string& text)
{
    data1.assign(text.c_str());
}

int32_t Field1_Pull(std::string& text)
{
    text.assign(data1.c_str());
}

int32_t Field2_Push(std::string&  text)
{    
    data2.assign(text.c_str());
}

int32_t Field2_Pull(std::string&  text)
{
    text.assign(data2.c_str());
}

int32_t Field3_Push(std::string&  text)
{    
    data2.assign(text.c_str());
}

int32_t Field3_Pull(std::string&  text)
{
    text.assign(data2.c_str());
}

int32_t Item2_Event(JMenu* ptr)
{
    JPrint(data2.c_str());
}

int32_t Item12_Event(JMenu* ptr)
{
    JPrint(data1.c_str());
}