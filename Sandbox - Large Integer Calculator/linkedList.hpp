#include <string>
#include <string.h>

class Node
{
  private:
    int digit;
  public:
    Node *next = 0;
    Node();
    Node(int i, Node* p = 0)
    {
      digit = i;
      next = p;
    }
    int returnDigit();
};

class LinkedList
{ 
  private:
    Node *head, *tail;
  public:
    LinkedList()
    {
      head = tail = 0;
    }
    ~LinkedList();
    int isEmpty()
    {
      return head == 0;
    }
    void addToHead(int);
    void addToTail(int);
    int deleteFromHead();
    int deleteFromTail();
    void deleteNode(int);
    bool isInList(int) const; 
    std::string displayInfo() const;
};