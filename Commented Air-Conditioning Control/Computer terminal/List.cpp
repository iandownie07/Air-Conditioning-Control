//#include "Event.h"


#include "List.h"

#include <iostream>

using namespace std;
 int listcount = 0;
int length = 0;
List::List() {
   head = 0;
   
}

List::~List() {
  Node* cursor = head;
  while(head) {
    cursor = cursor->getNext();
    delete head;
    head = cursor;
  }
  head = 0; // Officially empty
}

void List::insertBeforeFirst(Event* dat) {
  head = new Node(dat, head);
    listcount++;
        //cout << "listcount in insert is " << listcount << endl;
}

void List::insertAfterLast(Event* dat) {
  Node* p = head;
  Node* q = head;

  if (head == 0)
     head = new Node(dat,head);
  else {
     while (q != 0) {
        p = q;
        q = p->getNext();
     }
     p->setNext(new Node(dat,0));
  }
}

Event* List::readFirst() {
   return head->getData(); 
}

Event* List::removeFirst() {
  Event* retval = 0;
  if (head != 0){
     cout << "Removendo: " << head << endl;
     cout << "e fica:" << head->getData() << endl;
     retval = head->getData();
     Node* oldHead = head;
     head = head->getNext();
     delete oldHead;
  }
  return retval;
}

/* The next method works for a list of integers
   (void* data is a pointer to an int)

   Just remove the comments, if this is the case,
   and add the method definition in the class header
*/
/*
void List::insertionSort(int value) {
  Link* p = head;
  Link* q = head;

  if (head == 0)
  {
     head = new Link(new int(value),head);
	 int* i;
	 i = (int*)head->getData();
  }
  else
  {
	  int* pint;
	  int auxint;
	  pint = (int*)q->getData();
	  auxint = *pint;
	  while ((q != 0) && (auxint < value))
	  {
		  p = q;
		  q = p->getNext();
		  if (q != 0)
		  {
			pint = (int*)q->getData();
			auxint = *pint;
		  }
	  }
	  if (p == q)
		  head = new Node(new int(value),head);
	  else
			p->setNext(new Node(new int(value),q)_;
  }
}
*/

void* List::removeNode(Event* dat) {
  Node* p = head;
  Node* q = head;
  void* result;

  if (head == 0)
     result = 0;
  else {
	  while ((q != 0) && (q->getData() != dat)){  // Error!! the addresses will always be different!
		  p = q;
		  q = p->getNext();
	  }
	  if (q != 0) {
		  if (q == head){	// it is the first node
			  result = q->getData();
			  head = q->getNext();
			  delete q;
		  }
		  else{				// the node is in the middle
			  result = q->getData();
			  p->setNext(q->getNext());
			  delete q;
		  }
	  }
	  else
		  result = 0;		// node not found!
  }

  return result;
}


 
void List::listar()
{
    Node* temp = head; // returns everytime and gets head
    Event* pevent;
    
    if(head == 0)
        cout << "List is empty" << endl;
    else
    {
       
        while(temp != 0)
        {
            pevent = temp->getData();
            //cout << "pevent is" << pevent << endl;
            pevent -> printEvent();
            temp = temp->getNext();
            //cout << "temp is " << temp << endl;
        }
        delete temp;
        delete pevent;
    }
    

}

void List::listWithRange(int* yr1, int* mn1, int* dy1, int* yr2,int* mn2, int* dy2)
{
    Node* temp = head; // returns everytime and gets head
    Event* pevent;
    int length = listcount;
    if(head == 0)
        cout << "List is empty" << endl;
    else
    {
        // For each pointer, pass the date range to the function "selectByDateRange". 
        while(temp != 0)
        {
            pevent = temp->getData();
            //cout << "temp is " << temp << endl;
            //cout << "pevent is" << pevent << endl;
            length--;
            pevent -> selectByDateRange(yr1, mn1, dy1, yr2, mn2, dy2);
            temp = temp->getNext();
            //cout << "temp is " << temp << endl;
        }
        delete temp;
        //delete pevent;
    }
}

void List::demandByTimeOfDay()
{
    Node* temp = head;
    Event* pevent;
    int length = listcount;
    if(head == 0)
        cout << "List is empty" << endl;
    else
    {
        
        while(temp != 0)
        {
            pevent = temp->getData();
            //cout << "temp is " << temp << endl;
            //cout << "pevent is" << pevent << endl;
            length--;
            pevent -> selectByTimeOfDay(length);
            temp = temp->getNext();
            //cout << "temp is " << temp << endl;
        }
        delete temp;
        //delete pevent;
    }
}

void List::totalAirConUse(int* yr1, int* mn1, int* dy1, int* yr2,int* mn2, int* dy2)
{
    Node* temp = head;
    Event* pevent;
    int length = listcount;
    if(head == 0)
        cout << "List is empty" << endl;
    else
    {
        
        while(temp != 0)
        {
            // Pass all the pointers to the method "calculateTotalAirConUse" along with the date range and the current length of the linked list. The length is used to decide when we have seen all events.
            pevent = temp->getData();
            //cout << "temp is " << temp << endl;
            //cout << "pevent is" << pevent << endl;
            //cout << "length in list is " << length << endl;
            length--;
            pevent -> calculateTotalAirConUse(pevent, yr1, mn1, dy1, yr2, mn2, dy2, length);
            temp = temp->getNext();
            //cout << "temp is " << temp << endl;
        }
            delete temp;
        //delete pevent;
    }
}


