#include "jform.hpp"

void JForm::Create_Form(void)
{
    char* value;

    mFields = new FIELD* [mFieldNum+1];

    mFormWindow = derwin(Get_Base_Window(),Get_H()-4,(Get_W()-2)/2-2,2,(Get_W()/2));

    mLabelWindow = derwin(Get_Base_Window(),Get_H()-4,(Get_W()-2)/2-2,2,1);

    box(mFormWindow,0,0);
    box(mLabelWindow,0,0);

    keypad(Get_Base_Window(),TRUE);

    for (int i = 0; i < mFieldNum; ++i)
    {
        mFields[i] = new_field(1,10,1+i,Get_X()+10,0,0);
        
        field_opts_off(mFields[i], O_AUTOSKIP);

        set_field_just(mFields[i],JUSTIFY_CENTER);

        set_field_back(mFields[i],A_UNDERLINE);

        set_field_type(mFields[i],TYPE_NUMERIC);                /*numerical inputs only*/

        mFieldList[i]->Pull(value);

        set_field_buffer(mFields[i],0,"12345");

        mvwprintw(mLabelWindow,1+i,5,mFieldList[i]->Get_Title());
    }

    mFields[mFieldNum] = NULL;

    mForm = new_form(mFields);

    set_form_win(mForm, Get_Base_Window());

    set_form_sub(mForm, mFormWindow);

    post_form(mForm);

}

void JForm::Close_Form(void)
{
    selected = 0;

    keypad(Get_Base_Window(),FALSE);

    keypad(mFormWindow,TRUE);

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
    Show();
    Create_Form();
    wrefresh(Get_Base_Window());
    int c = 0;
    while (c != KEY_LEFT)
    {
        c = wgetch(Get_Base_Window());

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
        mFieldList[i]->Push(field_buffer(mFields[i],0));

        mFieldList[i]->Pull(p);

        set_field_buffer(mFields[i],0,p);
    }
}


