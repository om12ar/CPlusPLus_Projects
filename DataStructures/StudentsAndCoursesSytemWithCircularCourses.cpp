#include <iostream>

using namespace std;

struct studentNode
{
    string Sname ;
    int ID ;
    float grade ;
    studentNode* next ;
};

struct courseNode
{
    string Cname ;
    courseNode* next ;
    studentNode* studentsListHead ;
};

class CourseList
{
public:
    courseNode* head ;
    CourseList()
    {
        head = NULL ;
    }
    void insertCourse(string courseName)
    {
        if(head==NULL)
        {
            courseNode* temp = new courseNode ;
            temp->Cname = courseName ;
            temp->studentsListHead = NULL ;
            temp->next = NULL ;
            head = temp ;
        }else
        {
            courseNode* curr = head ;
            while(curr->next!=NULL)
                curr = curr->next ;
            courseNode* temp = new courseNode ;
            temp->Cname = courseName ;
            temp->studentsListHead = NULL ;
            temp->next = NULL ;
            curr->next = temp ;
        }
    }
    void insertStudent()
    {
        if(head==NULL)
        {
            cout << "There are no courses to insert students in" << endl ;
            return ;
        }
        string sName ;
        int id ;
        float g ;
        cout << "Enter student's name:\t" ;
            cin >> sName ;
        cout << "Enter student's ID:\t" ;
            cin >> id ;
        courseNode* curr = head ;
        while(curr!=NULL)
        {
            cout << "would you like to insert the student's grade in " << curr->Cname << " course?\nY:YES---N:NO" << endl ;
            char ch ;
            cin >> ch ;
            if(ch=='y'||ch=='Y')
            {
                cout << "Enter student's grade:\t" ;
                cin >> g ;
                if(curr->studentsListHead==NULL)
                {
                    studentNode* temp = new studentNode ;
                    temp->Sname = sName ;
                    temp->ID = id ;
                    temp->grade = g ;
                    temp->next = NULL ;
                    curr->studentsListHead = temp ;
                }else
                {
                    studentNode* currs = curr->studentsListHead ;
                    while(currs->next!=NULL)
                        currs = currs->next ;
                    studentNode* temp = new studentNode ;
                    temp->Sname = sName ;
                    temp->ID = id ;
                    temp->grade = g ;
                    temp->next = NULL ;
                    currs->next = temp ;
                }
            }
            curr = curr->next ;
        }
    }
    void printAllData()
    {
        cout << "\n\n" ;
        courseNode* curr = head ;
        while(curr!=NULL)
        {
            cout << "-Course: " << curr->Cname << endl ;
            if(curr->studentsListHead!=NULL)
            {
                studentNode* currs = curr->studentsListHead ;
                while(currs!=NULL)
                {
                    cout << currs->Sname << " " << currs->ID << " " << currs->grade << " " << endl ;
                    currs = currs->next ;
                }
            }
            cout << "-------------------------------------------" << endl ;
            curr = curr->next ;
        }
    }
};

int main()
{
    CourseList myList ;
    myList.insertCourse("Data structures") ;
    myList.insertCourse("Signals") ;
    myList.insertCourse("Database") ;

    myList.insertStudent() ;
    myList.insertStudent() ;

    myList.printAllData() ;

    return 0;
}
