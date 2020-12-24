#include "jform.hpp"
#include "stdlib.h"

void JForm::Create_Form(void)
{
    int rows, cols;

    mFields = new FIELD* [mFieldNum+1];

    char* value;

    for (int i = 0; i < mFieldNum; ++i)
    {
        mFields[i] = new_field(1,10,5+i,1,0,0);
        
        field_opts_off(mFields[i], O_AUTOSKIP);

        set_field_just(mFields[i],JUSTIFY_CENTER);

        mvprintw(Get_Y()+4+i,Get_X()+1,mFieldList[i].Get_Title());     /*print field title*/

        set_field_type(mFields[i],TYPE_NUMERIC);                /*numerical inputs only*/

        mFieldList[i].Pull(value);

        set_field_buffer(mFields[i],0,value);

    }
    
    mFields[mFieldNum] = NULL;

    mForm = new_form(mFields);

    scale_form(mForm, &rows, &cols);

    mFormWindow = derwin(Get_Base_Window(),Get_H()-4,Get_W()-2,3,(Get_W()-2/2));

    keypad(mFormWindow,TRUE);

    set_form_win(mForm, mFormWindow);

    set_form_sub(mForm, derwin(mFormWindow, rows, cols,2,2));

    post_form(mForm);

}

void JForm::Close_Form(void)
{
    selected = 0;

    unpost_form(mForm);

    for (int32_t i = 0; i < mFieldNum; i++)
    free_field(mFields[i]);

    delete[] mFields;

    mFields = NULL;

    free_form(mForm);
    
    endwin();
}

void JForm::Display(void)
{
    Create_Form();
    int c = 0;
    while (c != KEY_LEFT)
    {
        c = wgetch(mFormWindow);
        switch (c)
        {
            case KEY_DOWN:
                form_driver(mForm,REQ_NEXT_FIELD);
                form_driver(mForm,REQ_END_FIELD);
                break;
            case KEY_UP:
                form_driver(mForm,REQ_PREV_FIELD);
                form_driver(mForm,REQ_END_FIELD);
                break;
            case KEY_NPAGE:
                form_driver(mForm, REQ_SCR_FPAGE);
                break;
            case KEY_PPAGE:
                form_driver(mForm, REQ_SCR_BPAGE);
                break;
            case KEY_BACKSPACE:
                form_driver(mForm,REQ_DEL_PREV);
                break;
            default:
                form_driver(mForm,c);
                break;
        }
        wrefresh(mFormWindow);
    }
    Update();
    Close_Form();
}

void JForm::Update(void)
{
    int i;

    char* p;

    for (i = 0; i < mFieldNum; i++)
    {
        mFieldList[i].Push(field_buffer(mFields[i],0));

        mFieldList[i].Pull(p);

        set_field_buffer(mFields[i],0,p);
    }
}


