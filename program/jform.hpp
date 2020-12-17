#ifndef __JFORM_HPP
#define __JFORM_HPP
#include "jmenu.hpp"
#include "jwindow.hpp"
#include <form.h>

typedef int32_t (*Field_Pull_Callback)(char*);

typedef int32_t (*Field_Push_Callback)(const char*);

class JField : public JWidget
{
public:
    JField(const char* title):
    JWidget(title),mPull(NULL),mPush(NULL),pushMessageList(NULL),pullMessageList(NULL){}

    ~JField(){}

    void Set_Push(Field_Push_Callback pushCallback, event_feedback_t* messageList)
    {
        mPush = pushCallback;
    }

    void Set_Pull(Field_Pull_Callback pullCallback, event_feedback_t* messageList)
    {
        mPull = pullCallback;
    }

    const char* Pull(char* var)
    {
        return Get_Feedback(mPull(var),pullMessageList);
    }

    const char* Push(const char* var)
    {
        return Get_Feedback(mPush(var),pushMessageList);
    }

private:

    int32_t (*mPush)(const char*);

    int32_t (*mPull)(char*);

    event_feedback_t* pushMessageList;

    event_feedback_t* pullMessageList;

};

/**
 * +-----------------------+
 * |         Title         |
 * +-----------------------+
 * |+----------++---------+|
 * ||          ||         ||
 * ||  Labels  ||   Form  ||
 * ||          ||  Fields ||
 * ||          ||         ||
 * |+----------++---------+|
 * +-----------------------+
 * 
 */

class JForm : public JWindow
{
public:

    JForm(int32_t startX, int32_t startY, uint32_t height, uint32_t width, const char* title):
    JWindow(startX,startY,height,width,title){}

    ~JForm(){}

    void Display(void) override;

    void Close(void) override;

    virtual void Add_Fields(JField* fieldList)
    {
        mFieldList = fieldList;
        mFieldNum = sizeof(fieldList);
    }

    void Add_Last(JMenu* lastMenu)
    {
        mLastMenu = lastMenu;
    }

    void Update(void);          /*Save and update parameters*/

protected:

    void Create_Form(void);

private:

    WINDOW* mFormWindow;        /*the window that associate the form*/

    FORM* mForm;                /*the form list*/

    FIELD** mFields;

    JField* mFieldList;
    
    JMenu* mLastMenu;

    int32_t mFieldNum;

    int32_t selected;
};




#endif