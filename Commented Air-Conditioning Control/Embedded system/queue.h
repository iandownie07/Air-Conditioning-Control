/*
   File queue.h

   Header file for class Queue

   Class Queue is definition for a queue inmplemented on a linked list,
   with the following operations:

   1. Insert element (tail).
   2. Remove element (head).
   3. Determine whether the queue is empty.
   4. Show the head and the tail.
   5. Show the length.

   Eduardo Augusto Bezerra <eduardob@acm.org>
   Faculdade de Informatica, PUC-RS
   Laboratorio de Programacao II

   April 2003.

*/

class Queue {

  struct Link {
    void* data;
    Link* prev; // each struct link contains pointers to
    Link* next;
    Link(void* dat, Link* prv, Link* nxt); // inside the class Queue we have
    ~Link();                         // a structure Link that contains func Link
  } *head, *tail;                   // when we create an element, there's a
  int length;                      // pointer to the data and the neighbouring
public:                           // elements
  Queue();
  ~Queue();
  void insert(void* dat);
  void* remove();
  void* getHead();
  void* getTail();
  int getLength();
  bool isEmpty();
};
