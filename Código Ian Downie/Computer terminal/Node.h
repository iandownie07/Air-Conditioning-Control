/*
   File Node.h

   Class Node

   Class Node is definition for a generic node for a linked list

   Eduardo Augusto Bezerra <eduardo.bezerra@ufsc.br>
   Departamento de Engenharia Eletrica

   pevent da criacao: Abril de 2006.
   pevent da ultima alteracao: 8 de outubro de 2015.

*/

#ifndef Node_h
#define Node_h

#include "Event.h"

class Node
{

    //void* pevent;
    Event* pevent;
    Node* next;

  public:
    Node(Event* dat, Node* nxt){
       pevent = dat;
       next = nxt;
    }
    ~Node(){
       // delete next;
    }
    Node* getNext(){
       return next;
    }
    void setNext(Node* nxt){
       next = nxt;
    }
    Event* getData(){
       return pevent;
    }
    Event* setData(Event* dat){
       pevent = dat;
    }
};

#endif /* Node_h */
