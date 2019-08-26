#include "dlist.h"
#include <iostream>
#include <cstdlib>
using namespace std;

static void Add(Dlist<int> &stack)
{

    if(stack.isEmpty()) {
        cout << "Not enough operands\n";
        return;
    }
    int* first=stack.removeFront();
    try
    {
        int* second=stack.removeFront();
        int* ans=new int(*first+*second);
        stack.insertFront(ans);
        delete first;
        delete second;
    }
    catch(emptyList e)
    {
        cout << "Not enough operands\n";
        stack.insertFront(first);
    }
}
static void Minus(Dlist<int> &stack)
{
    if(stack.isEmpty())
    {
        cout << "Not enough operands\n";
        return;
    }
    int* first=stack.removeFront();
    try{
        int* second=stack.removeFront();
        int* ans=new int(*second-*first);
        stack.insertFront(ans);
        delete first;
        delete second;
    }
    catch(emptyList e)
    {
        cout << "Not enough operands\n";
        stack.insertFront(first);
    }
}
static void Multiply(Dlist<int> &stack)
{
    if(stack.isEmpty())
    {
        cout << "Not enough operands\n";
        return;
    }
    int* first=stack.removeFront();
    try{
        int* second=stack.removeFront();
        int* ans=new int((*second)*(*first));
        stack.insertFront(ans);
        delete first;
        delete second;
    }
    catch(emptyList e)
    {
        cout << "Not enough operands\n";
        stack.insertFront(first);
    }
}
static void Divide(Dlist<int> &stack)
{
    if(stack.isEmpty())
    {
        cout << "Not enough operands\n";
        return;
    }
    int* first=stack.removeFront();
    try{
        int* second=stack.removeFront();
        if(*first==0)
        {
            stack.insertFront(second);
            stack.insertFront(first);
            cout<<"Divide by zero\n";
            return;
        }
        int* ans=new int((*second)/(*first));
        stack.insertFront(ans);
        delete first;
        delete second;
    }
    catch(emptyList e)
    {
        cout << "Not enough operands\n";
        stack.insertFront(first);
    }
}

static void Negate(Dlist<int> &stack)
{
    if(stack.isEmpty())
    {
        cout << "Not enough operands\n";
        return;
    }
    int* first=stack.removeFront();
    int* ans=new int(-*first);
    delete first;
        stack.insertFront(ans);
}
static void Duplicate(Dlist<int> &stack)
{
    if(stack.isEmpty())
    {
        cout << "Not enough operands\n";
        return;
    }
    int* first=stack.removeFront();
    int* ans=new int(*first);
    stack.insertFront(first);
    stack.insertFront(ans);
}
static void Reverse(Dlist<int> &stack)
{

    if(stack.isEmpty()) {
        cout << "Not enough operands\n";
        return;
    }
    int* first=stack.removeFront();
    try
    {
        int* second=stack.removeFront();
        stack.insertFront(first);
        stack.insertFront(second);
    }
    catch(emptyList e)
    {
        cout << "Not enough operands\n";
        stack.insertFront(first);
    }
}
static void PrintTop(Dlist<int> &stack)
{
    if(stack.isEmpty())
    {
        cout << "Not enough operands\n";
        return;
    }
    int* first=stack.removeFront();
    cout<<*first<<endl;
    stack.insertFront(first);
}
static void Clear(Dlist<int> &stack)
{
    while(!stack.isEmpty()) {
        int* op=stack.removeFront();
        delete op;
    }
}
static void PrintAll(Dlist<int> stack)
{
    while(!stack.isEmpty()) {
            int *op = stack.removeFront();
            cout<<*op<<" ";
            delete op;
    }
    cout<<endl;
}
static bool isInteger(string s)
{
	if(s=="0"||s=="1"||s=="2"||s=="3"||s=="4"||s=="5"||s=="6"||s=="7"||s=="8"||s=="9")
		return true;
	else
		return false;
}

static bool isInt(string s)
{
	int m=s.size();
	if(!(s.substr(0,1)=="-")&&!isInteger(s.substr(0,1)))
		return false;
	for(int i=1;i<m;i++)
	{
		if(!isInteger(s.substr(i,1)))
			return false;	
	}
	return true;
}
int main()
{
    Dlist<int> stack;
    string s;
    while(cin)
    {
        cin>>s;
        if(s=="+")
            Add(stack);
        else if(s=="-")
            Minus(stack);
        else if(s=="*")
            Multiply(stack);
        else if(s=="/")
            Divide(stack);
        else if(s=="n")
            Negate(stack);
        else if(s=="d")
            Duplicate(stack);
        else if(s=="r")
            Reverse(stack);
        else if(s=="p")
            PrintTop(stack);
        else if(s=="c")
            Clear(stack);
        else if(s=="a")
            PrintAll(stack);
        else if(s=="q")
            break;
        else if(isInt(s))
        {
	    int i;
	    sscanf(s.c_str(),"%d",&i);
            int *op=new int(i);
            stack.insertFront(op);
        }
        else
            cout<<"Bad input\n";
        s.clear();
    }
	return 0;
}

