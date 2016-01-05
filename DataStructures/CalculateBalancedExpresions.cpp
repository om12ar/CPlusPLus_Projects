#include <iostream>
#include <stdexcept>
#include <cmath>
#include <sstream>
using namespace std;

template <typename T>
struct node{
    T value;
    node* next;
};

template <typename T>
class Stack{
    private:
        node<T>* head;
        int size;
    public:
        Stack(){
            head = NULL;
            size = 0;
        }
        void push(T newVal){
            node<T>* tmp = new node<T>;
            tmp -> value = newVal;
            tmp -> next = head;
            head = tmp;
            size++;
        }
        bool is_empty()
        {
            return !size;
        }
        T top(){
            if(!size)
                throw "The stack is empty!\n";

            return head -> value;
        }
        void pop(){
            if(!size)
                throw "The stack is empty!\n";

            node<T> *tmp = head;
            head = head->next;
            delete tmp;
            size--;
        }
        void clearec(node<T>* h){
            if(h==NULL)return;
            clearec(h->next);
            delete h;
        }
        ~Stack(){
            clearec(head);
        }
};


bool is_balanced(string expression){
    Stack<char> ST;
    for(int i=0;i<expression.size();i++){
        if(expression[i] == '{' || expression[i] == '[' || expression[i] == '(')
            ST.push(expression[i]);
        else if(expression[i] == '}'){
            if(ST.is_empty() || ST.top() != '{')
                return 0;
            else
                ST.pop();
        }else if(expression[i] == ']'){
            if(ST.is_empty() || ST.top() != '[')
                return 0;
            else
                ST.pop();
        }else if(expression[i] == ')'){
            if(ST.is_empty() || ST.top() != '(')
                return 0;
            else
                ST.pop();
        }
    }
    return ST.is_empty();
}

string open_brackets ="{[(" , close_brackets = ")]}", ops = "+-*/^";


string get_num(string x, int &ind){
    string num ;
    for( ; ind < x.size() && (isdigit(x[ind]) || x[ind] == '.'); ind++){
        num += x[ind];
    }
    ind--;
    return num;
}

bool lessOrEq(char op1,char op2){
    int p1, p2;
    if(op1=='+' || op1 == '-')p1 = 0;
    else if(op1 == '*' || op1 == '/')p1 = 1;
    else p1 = 2;

    if(op2=='+' || op2 == '-')p2 = 0;
    else if(op2 == '*' || op2 == '/')p2 = 1;
    else p2 = 2;

    return p1<=p2;
}
string get_postfix(string expression){
    string postfixExp;
    Stack<char> operators;
    for(int i=0 ; i<expression.size(); i++){
        if(isdigit(expression[i])){
            postfixExp += " ";
            postfixExp += get_num(expression, i);
        }
        else if( (int)open_brackets.find(expression[i]) != -1 )
            operators.push( expression[i] );
        else if( (int)close_brackets.find( expression[i]) != -1 ){
            while( (int)open_brackets.find( operators.top()) == -1 ){
                postfixExp += " ";
                postfixExp += operators.top();
                operators.pop();
            }
            operators.pop();
        }else if((int)ops.find(expression[i]) != -1){
            while(!operators.is_empty() && (int)open_brackets.find(operators.top()) == -1
                  && lessOrEq(expression[i], operators.top())){
                postfixExp += " ";
                postfixExp += operators.top();
                operators.pop();
            }
            operators.push(expression[i]);

        }
    }
    while(!operators.is_empty()){
        postfixExp += " ";
        postfixExp += operators.top();
        operators.pop();
    }
    postfixExp.erase(0,1);
    return postfixExp;
}
double calc(string exp){
    string postfixExp = get_postfix(exp);
    stringstream ss(postfixExp);
    Stack<double> values;
    string tmp;
    while(ss>>tmp){

        if(isdigit(tmp[0])){
            // Not operator
            stringstream st(tmp);
            double tmpdbl;
            st>>tmpdbl;
            values.push(tmpdbl);

        }else{
            double val1, val2;
            val2 = values.top();
            values.pop();
            val1 = values.top();
            values.pop();
            if(tmp == "+")
                values.push(val1 + val2);
            else if(tmp == "-")
                values.push(val1 - val2);
            else if(tmp == "*")
                values.push(val1 * val2);
            else if(tmp == "/")
                values.push(val1 / val2);
            else if(tmp == "^")
                values.push(pow(val1,val2));
        }
    }
    return values.top();
}
string handleNegatives(string x){
    for(int i=0; i<x.size();i++)
        if(x[i] == ' ')x.erase(i,1);

    if(x[0] == '-')
        x.insert(0,"0");


    for(int i=1;i<x.size();i++){
        if(x[i] == '-' && ( (int)ops.find(x[i-1]) != -1 || (int)open_brackets.find(x[i-1])!= -1 )){
           x.replace(i,1,"(0-1)*");
        }

    }
    return x;
}
int main()
{

    while(1){
        cout<<"Enter an arithmetic expression   or N to exit:\n";
        string expression;
        getline(cin,expression);
        expression = handleNegatives(expression);

        if(expression == "N" || expression == "n")
            break;

        if(!is_balanced(expression))
            cout << "Error!\tThe expression is not balanced\n";
        else
            cout<<"= "<<calc(expression)<<endl;
    }
     return 0;
}
