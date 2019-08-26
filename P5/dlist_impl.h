#ifndef PROJECT_5_RELATED_FILES_DLIST_IMPL_H
#define PROJECT_5_RELATED_FILES_DLIST_IMPL_H

#include "dlist.h"
#include <iostream>
template <class T>
bool Dlist<T>:: isEmpty() const
{
    return (!first);
}

template <class T>
void Dlist<T>:: insertFront(T *op)
{
    node *First=new node;
    First->op=op;
    First->next=nullptr;
    First->prev= nullptr;
    if (isEmpty()) {
        first = last = First;
    }
    else {
        First->next=first;
        first->prev=First;
        first=First;
    }
}

template <class T>
void Dlist<T>::insertBack(T *op)
{
    node *Last=new node;
    Last->op=op;
    Last->prev= nullptr;
    Last->next= nullptr;
    if (isEmpty()) {
        first = last = Last;
    }
    else {
        Last->prev=last;
        last->next=Last;
        last=Last;
    }
}
template <class T>
T * Dlist<T>::removeFront()
{
    if(isEmpty())
    {
        emptyList e;
        throw e;
    }
    T* result=first->op;
    node *victim=first;
    if(first->next)
    {
	  first->next->prev=nullptr;
        first=first->next;
    }
    else
    {
        last=first=first->next;
    }
    delete victim;
    return result;
}

template <class T>
T * Dlist<T>::removeBack(){
    if(isEmpty())
    {
        emptyList e;
        throw e;
    }
    T* result=last->op;
    node *victim=last;
    if(last->prev)
    {
	  last->prev->next=nullptr;
        last=last->prev;
    }
    else
    {
        first=last=last->prev;
    }
    delete victim;
    return result;
}

template <class T>
void Dlist<T>:: removeAll()
{
    while(!isEmpty()) {
      T* op=removeFront();
      delete op;
    }
}
template <class T>
void Dlist<T>::copyAll(const Dlist<T> &l)
{
    if(l.isEmpty())
        return;
    node *Current=l.first;
    while(Current)
    {
        T* opp=new T(*Current->op);
        insertBack(opp);
        Current=Current->next;
    }
}

template <class T>
Dlist<T>::Dlist():first(0),last(0)
{
}

template <class T>
Dlist<T>::Dlist(const Dlist<T> &l):first(0),last(0)
{
    copyAll(l);
}

template <class T>
Dlist<T>& Dlist<T>::operator=(const Dlist<T> &l)
{
    if(this!=&l) {
        removeAll();
        copyAll(l);
    }
    return *this;
}

template <class T>
Dlist<T>::~Dlist()
{
    removeAll();
}
#endif
