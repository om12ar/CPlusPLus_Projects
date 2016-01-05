#include <iostream>
#include <fstream>
using namespace std;

struct node
{
    string info ;
    node* lNode ;
    node* rNode ;
};

class hashTable
{
private:
    int tableSize ;
    int numberOfWords ;
    node** arr ;
public:
    hashTable(int sz)
    {
        tableSize = sz ;
        numberOfWords = 0 ;
        arr = new node*[sz] ;
        for(int i=0;i<sz;i++)
            arr[i] = NULL ;
    }
    int hashFunction(string str)
    {
        int sum = 0 ;
        for (int i=0;i<str.size();i++)
            sum = sum + static_cast<int>(str[i]) ;
        return (sum%tableSize) ;
    }
    int size()
    {
        return numberOfWords ;
    }
    void add(string str)
    {
        int indexInTable = hashFunction(str) ;
        //cout << "Index in table --> " << indexInTable << endl ;
        node* current ; //pointer to traverse the tree
        node* trailCurrent ; //pointer behind current
        node* newNode ; //pointer to create the node
        newNode = new node ;
        newNode->info = str ;
        newNode->lNode = NULL ;
        newNode->rNode = NULL ;
        if(arr[indexInTable]==NULL)
        {
            arr[indexInTable] = newNode ;
            numberOfWords++ ;
            //cout << "Here" << endl ;
        }else
        {
            current = arr[indexInTable] ;
            while(current!=NULL)
            {
                trailCurrent = current ;
                if(current->info==str)
                {
                    cout << "The insert item is already in the list-" ;
                    cout << "duplicates are not allowed." << str << endl ;
                    return ;
                }else if(current->info > str)
                    current = current->lNode ;
                else
                    current = current->rNode ;
            }//end while
            if(trailCurrent->info > str)
                trailCurrent->lNode = newNode ;
            else
                trailCurrent->rNode = newNode ;
            numberOfWords++ ;
        }
    }
    bool contain(string str)
    {
        int indexInTable = hashFunction(str) ;
        node* current ;
        bool found = false ;
        if(arr[indexInTable]==NULL)
         cout << "Cannot search an empty tree." << endl ;
        else
        {
            current = arr[indexInTable] ;
            while(current!=NULL&&!found)
            {
                if(current->info==str)
                    found = true ;
                else if(current->info > str)
                    current = current->lNode ;
                else
                    current = current->rNode ;
            }//end while
        }//end else
        return found ;
    }
    void remove(string str)
    {
        int indexInTable = hashFunction(str) ;
        node* current ; //pointer to traverse the tree
        node* trailCurrent ; //pointer behind current
        bool found = false ;
        if(arr[indexInTable]==NULL)
            cout << "Cannot delete from an empty tree." << endl ;
        else
        {
            current = arr[indexInTable] ;
            trailCurrent = arr[indexInTable] ;
            while(current!=NULL&&!found)
            {
                if(current->info==str)
                    found = true ;
                else
                {
                    trailCurrent = current ;
                    if(current->info > str)
                        current = current->lNode ;
                    else
                        current = current->rNode ;
                }
            }//end while
            if(current==NULL)
                cout << "The string to be deleted is not in the tree." << endl ;
            else if(found)
            {
                numberOfWords-- ;
                if(current==arr[indexInTable])
                    deleteFromTree(arr[indexInTable]) ;
                else if(trailCurrent->info > str)
                    deleteFromTree(trailCurrent->lNode) ;
                else
                    deleteFromTree(trailCurrent->rNode) ;
            }//end if
        }
    }
    void deleteFromTree(node* &p)
    {
        node* current ;//pointer to traverse the tree
        node* trailCurrent ; //pointer behind current
        node* temp ; //pointer to delete the node
        if(p==NULL)
            cout << "Error: The node to be deleted is NULL." << endl ;
        else if(p->lNode==NULL&&p->rNode==NULL)
        {
            temp = p ;
            p = NULL ;
            delete temp ;
        }
        else if(p->lNode==NULL)
        {
            temp = p ;
            p = temp->rNode ;
            delete temp ;
        }
        else if(p->rNode==NULL)
        {
            temp = p ;
            p = temp->lNode ;
            delete temp ;
        }
        else
        {
            current = p->lNode ;
            trailCurrent = NULL ;
            while(current->rNode!=NULL)
            {
                trailCurrent = current ;
                current = current->rNode ;
            }//end while
            p->info = current->info ;
            if(trailCurrent==NULL) //current did not move; current == p->llink; adjust p
                p->lNode = current->lNode ;
            else
                trailCurrent->rNode = current->lNode ;
            delete current;
        }//end else
    }
};

void convertToLowerCase(string &str)
{
    for(int i=0;i<str.size();i++)
        str[i] = tolower(str[i]) ;
}

int main()
{
    hashTable h1(100) ;
    fstream readWords ;
    readWords.open("EnglishWords.csv",ios::in) ;
    string s ;
    while(!readWords.eof())
    {
        readWords >> s ;
        if(readWords.fail())
            break ;
        convertToLowerCase(s) ;
        h1.add(s) ;
        //cout << s << endl ;
    }

    while(1)
    {
        cout << "Do you want to search for a word?\nY:YES=====N:NO\n" ;
        char ch ;
        cin >> ch ;
        if(ch=='Y'||ch=='y')
        {
            cout << "Enter the word to search for:\t" ;
            string str ;
            cin >> str ;
            convertToLowerCase(str) ;
            if(h1.contain(str))
                cout << "OK" << endl ;
            else
                cout << "Not found" << endl ;
        }else
            break ;
    }
    return 0;
}
