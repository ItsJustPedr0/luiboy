#include "linkedList.hpp"

int Node::returnDigit()
{
  return this->digit;
}

LinkedList::~LinkedList()
{
  for (Node *p; !isEmpty();)
  {
    p = head->next;
    delete head;
    head = p;
  }
}

void LinkedList::addToHead(int x)
{
  head = new Node(x, head);
  if (tail == 0)
    tail = head;
}

void LinkedList::addToTail(int x)
{
  if (tail != 0)
  {
    tail->next=new Node(x);
    tail = tail->next;
  }
  else head = tail = new Node(x);
}

int LinkedList::deleteFromHead() {
  int x = head->returnDigit();
  Node *tmp = head;
  if (head == tail) 
    head = tail = 0;
  else head = head->next;
  delete tmp;
  return x;
}

int LinkedList::deleteFromTail() {
  int x = tail->returnDigit();
  if (head == tail) 
  { // if only one node in the list;
    delete head;
    head = tail = 0;
  }
  else 
  { // if more than one node in the list,
    Node *tmp; // find the predecessor of tail;
    for (tmp = head; tmp->next != tail; tmp = tmp->next);
    delete tail;
    tail = tmp; // the predecessor of tail becomes tail;
    tail->next = 0;
  }
  return x;  
}

void LinkedList::deleteNode(int x) 
{
  if (head != 0) // if nonempty list;
    if (head == tail && x == head->returnDigit()) 
    { // if only one
      delete head; // node in the list;
      head = tail = 0;
    }
    else if (x == head->returnDigit()) 
    {// if more than one node in the list
      Node *tmp = head;
      head = head->next;
      delete tmp; // and old head is deleted;
    }
    else 
    { // if more than one node in the list
      Node *prev, *tmp;
      for (prev = head, tmp = head->next; tmp != 0 && !(tmp->returnDigit() == x); prev = prev->next, tmp = tmp->next);
      if (tmp != 0) 
      {
        prev->next = tmp->next;
        if (tmp == tail)
          tail = prev;
        delete tmp;
      }
    }
}

bool LinkedList::isInList(int x) const 
{
  Node *tmp;
  for (tmp = head; tmp != 0 && !(tmp->returnDigit() == x); tmp = tmp->next);
  return tmp != 0;
}

std::string LinkedList::displayInfo() const
{
  Node *tmp;
  std::string result = "";
  std::string tempo;
  for (tmp = head; tmp != 0; tmp = tmp->next)
  {
    tempo = std::to_string(tmp->returnDigit());
    result.append(tempo);
  }
  return result;
}