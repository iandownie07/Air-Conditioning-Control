/*
   File test_queue.cpp

   Test program for the class Queue

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

#include "queue.cpp"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
  Queue fila1;
  string input_value;
  cout << "Digite valores inteiros seguidos por Enter" << endl;
  cout << "Digite o valor 0 (zero) para encerrar a entrada de dados." << endl;

  cin >> input_value;
  while(input_value != "0")
  {
    fila1.insert(new string(input_value));
    cin >> input_value;
  }

  string pint;
  cout << endl << "-------------" << endl;
  cout << endl << "tamanho = " << fila1.getLength() << endl;

  // Remove the values from the queue and print them:
  cout << endl << endl;
  while(fila1.isEmpty() == 0) {
    pint = *(string*)fila1.remove();
    cout << pint << endl;
      cout << fila1.isEmpty() << endl;
  }

}
