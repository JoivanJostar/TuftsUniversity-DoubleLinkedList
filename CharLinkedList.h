
#ifndef CHAR_LINKED_LIST_H
#define CHAR_LINKED_LIST_H
#include "iostream"

class CharLinkedList {

private:
    typedef  struct Node{
        char c;
        Node * next;
        Node * previous;
    }Node;


    Node * head;
    Node * tail;
    int m_size;

    Node * indexOf(int index)const;
    void initHeadNode();

public:
    CharLinkedList();
    CharLinkedList(char c);
    CharLinkedList(char arr[], int size);
    CharLinkedList(const CharLinkedList &other);

     ~CharLinkedList();
     CharLinkedList& operator=(const CharLinkedList& other);


    bool isEmpty() const;
    void clear();
    int size() const;
    char first() const;
    char last() const;

    char elementAt(int index) const;
    void insertAt(char c, int index);
    void insertInOrder(char c);
    void pushAtBack(char c);
    void pushAtFront(char c);
    void removeAt(int index);
    void popFromFront();
    void popFromBack();
    void replaceAt(char c, int index);
    void concatenate(CharLinkedList *other);

    std::string toString() const;
    std::string toReverseString() const;


};

#endif



