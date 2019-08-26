#include <iostream>
#include "dlist.h"
#include <string>
#include <cstdlib>
using namespace std;
typedef struct customer{
   int timestamp;
   string name;
   string status;
   int duration;
}customer;
typedef struct client{
    int servetime;
    Dlist<customer>* type;
    customer* server;
}client;
static customer* serve(Dlist<customer> &m, int tick)
{
    if(!m.isEmpty())
    {
        customer* n=m.removeFront();
        m.insertFront(n);
        if(n->timestamp<=tick)
            return n;
        else
            return nullptr;

    }
    else
        return nullptr;
}

int main()
{
    int N;
    int n=0;
    cin>>N;
    cin.get();
    string s;
    Dlist <customer> platinum;
     Dlist <customer> gold;
     Dlist <customer> silver;
     Dlist <customer> regular;
     customer* input=new customer[N];
     client c={0, nullptr, nullptr};
    while(n<N)
    {
        customer* m=new customer;
        char name[20];
        char status[20];
        getline(cin,s);
        sscanf(s.c_str(),"%d %s %s %d",&m->timestamp,name,status,&m->duration);
        m->name=name;
        m->status=status;
        input[n]=*m;
        n++;
        if(m->status=="platinum")
            platinum.insertBack(m);
        else if(m->status=="gold")
            gold.insertBack(m);
        else if(m->status=="silver")
            silver.insertBack(m);
        else if(m->status=="regular")
            regular.insertBack(m);
        else
            cout<<"bad input"<<endl;

    }
    int tick=0;
    while(!platinum.isEmpty()||!gold.isEmpty()||!silver.isEmpty()||!regular.isEmpty())
    {
        cout<<"Starting tick #"<<tick<<endl;
        for(int i=0; i<N;i++)
        {
            if(input[i].timestamp==tick)
            {
                cout<<"Call from "<<input[i].name<<" a "<<input[i].status<<" member"<<endl;
            }
        }
        if(!c.server)
        {
            if(serve(platinum,tick))
            {
                c.server=serve(platinum,tick);
                c.servetime=tick;
                c.type=&platinum;
                cout<<"Answering call from "<<c.server->name<<endl;
            }
            else if(serve(gold,tick))
            {
                c.server=serve(gold,tick);
                c.servetime=tick;
                c.type=&gold;
                cout<<"Answering call from "<<c.server->name<<endl;
            }
            else if(serve(silver,tick))
            {
                c.server=serve(silver,tick);
                c.servetime=tick;
                c.type=&silver;
                cout<<"Answering call from "<<c.server->name<<endl;
            }
            else if(serve(regular,tick)) {
                c.server = serve(regular, tick);
                c.servetime=tick;
                c.type=&regular;
                cout << "Answering call from " <<c.server->name<< endl;
            }
            else{}
        }
        if(c.server){
            if((tick-c.servetime+1)>=c.server->duration)
            {
                c.server= nullptr;
                customer* done=c.type->removeFront();
                delete done;
            }
        }
        tick++;
    }
    cout<<"Starting tick #"<<tick<<endl;
    delete[] input;
}
