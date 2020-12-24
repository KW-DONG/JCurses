#include "jform.hpp"

int main()
{
    JBaseMenu baseMenu(10,5,10,40,"main");
    JMenu menu1(10,5,10,40,"menu1");
    JForm form1(10,5,10,40,"form1");
    JForm form2(10,5,10,40,"form2");

    JItem<JMenu> item1("item1");
    JItem<JMenu> item2("item2");
    JItem<JMenu> item11("item11");
    JItem<JMenu> item12("item12");

    JItem<JMenu> baseMenu[] = {item1,item2,(JItem<JMenu>)NULL};
    JItem<JMenu> menu1List[] = {item11,item12,(JItem<JMenu>)NULL};

    JField field1("field1");
    JField field2("field2");

    JInit();




}