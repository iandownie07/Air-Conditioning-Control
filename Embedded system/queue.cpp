/*
   File queue.cpp

   Implementation file for class Queue

   Class Queue is the definition for a queue inmplemented
   on a linked list, with the following operations:

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

#include "queue.h"
#include <iostream>

using namespace std;

Queue::Queue() {
   head = 0;
   tail = 0;
   length = 0;
}

Queue::~Queue() {
  Link* cursor = head;
  while(head) { // move through all entries until they're removed
    cursor = cursor->prev;
    delete head;
    head = cursor;
  }
  head = 0; // Officially empty
  tail = 0;
  length = 0;
}

Queue::Link::Link(void* dat, Link* prv, Link* nxt) {
  data = dat;
  prev = prv;
  next = nxt;
}

Queue::Link::~Link() {
//  delete prev;
}

void Queue::insert(void* dat) {
  if (head == 0){
     tail = new Link(dat, 0, 0);
     head = tail; // we only have 1 element
      
  } else {
     tail->next = new Link(dat, tail, 0); // we include a new element at the back
     tail = tail->next;
  }
  length++;
}

void* Queue::remove() {
   //int* pint;
   void* result; //A void pointer is a pointer that has no associated data type with it. A void pointer can hold address of any type and can be typcasted to any type.
   if(length == 0)
      result = 0; // there's nothing in queue
   else	{
      result = head->data; // the return value will be the data pointed to by
                          // by the head
      Link* oldHead = head; // the head now becomes oldHead
      head = head->next;    //and the new head points to next
      if (head != 0)       // if head isn't empty (next is end of queue)
         head->prev = 0;  // head no longer points to prev as it's at the front
         delete oldHead;
         length--;
      }
      if (length == 0)
         tail = 0;
      return result;
}

void* Queue::getHead() { 
   return head->data; 
}

void* Queue::getTail() { 
   return tail->data; 
}

int Queue::getLength() {
	return length;
}

bool Queue::isEmpty() {
	
	bool flag = false;

	if (length == 0)
		flag = true;

	return flag;
}
