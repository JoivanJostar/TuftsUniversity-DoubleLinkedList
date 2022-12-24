
#include "CharLinkedList.h"
#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>
using namespace std;
void CharLinkedList::initHeadNode() {
    //the first node of the list is not used
//it is just a head node;
    this->head = new Node;
    this->head->next = nullptr;
    this->head->previous = nullptr;
    this->tail = head;
    this->m_size = 0;
}
CharLinkedList::CharLinkedList() {

    initHeadNode();
}
CharLinkedList::CharLinkedList(char c){
    initHeadNode();
    pushAtBack(c);
}
CharLinkedList::CharLinkedList(char arr[], int size){
    initHeadNode();
    for(int i=0;i<size;++i)
        pushAtBack(arr[i]);
}
CharLinkedList::CharLinkedList(const CharLinkedList &other) {
    initHeadNode();
    for(int i=0;i<other.size();++i)
        pushAtBack(other.elementAt(i)); //not efficient
}
CharLinkedList::~CharLinkedList() {
    clear();
    delete this->head; //delete the head node
}

CharLinkedList& CharLinkedList::operator=(const CharLinkedList& other) {
    this->clear();
    for (int i = 0; i < other.size(); ++i) {
        this->pushAtBack(other.elementAt(i));
    }
    return *this;
}
bool CharLinkedList::isEmpty() const {
    //when the tail ptr equals the head ptr,
    // that means there is no data node in the list.
    return this->tail==this->head ;
}

int CharLinkedList::size() const {
    return this->m_size;
}



CharLinkedList::Node *CharLinkedList::indexOf(int index)const {
    std::stringstream ss;
    if(index<0||index>=size()){
        ss<<"index ("<<index<<") not in range [0.."<<size()<<")";
        throw std::range_error(ss.str());
    }
    Node * p= nullptr;
    if(index<=size()/2){ //forward
        p=this->head->next;
        for(int i=0;i!=index;++i)
            p=p->next;
    }else{ //backward
        p=this->tail;
        for(int i=size()-1;i!=index;--i)
            p=p->previous;
    }

    return p;
}
//• char first() const
//A first function that takes no parameters and returns the first element (char)
//in the list. If the list is empty it should throw a C++ std::runtime_error
//“cannot get first of empty LinkedList”.
char CharLinkedList::first() const {
    if(isEmpty())throw std::runtime_error("cannot get first of empty LinkedList");
    return indexOf(0)->c;
}
//A last function that takes no parameters and returns the last element
//(char) in the list. If the list is empty it throws a
//C++ std::runtime_error exception with the message “cannot get last of empty LinkedList”.
char CharLinkedList::last() const {
    if(isEmpty())throw std::runtime_error("cannot get last of empty LinkedList");
    return tail->c;
}
//• char elementAt(int index) const
//An elementAt function that takes an integer index and returns the
//element (char) in the list at that index. NOTE: Indices are 0-based.
//If the index is out of range it should throw a C++ std::range_error
//exception with the message “index (IDX) not in range [0..SIZE)” where
//IDX is the index that was given and SIZE is the size of the linked list.
//For example: “index (6) not in range [0..3)” if the function were to
//be called using the index 6 in a size 3 list. Note the braces and the
//spacing! This function must use a private recursive helper
//function.
char CharLinkedList::elementAt(int index) const {
    Node * p=indexOf(index);
    return p->c;
}
//A replaceAt function that takes an element (char) and an integer index as parameters and has a void return type. 
// It replaces the element
//at the specified index with the new element. If the index is out of
//range it should throw a C++ std::range_error exception with the
//message “index (IDX) not in range [0..SIZE)” where IDX is the index
//that was given and SIZE is the size of the list. This function must
//use a private recursive helper function.
void CharLinkedList::replaceAt(char c, int index) {
    Node * p= indexOf(index);
    p->c=c;
}
//An insertAt function that takes an element (char) and an integer
//index as parameters and has a void return type. It inserts the new
//element at the specified index. The new element is then in the indexth position.
//If the index is out of range it should throw a C++
//std::range_error exception with the message “index (IDX) not in
//range [0..SIZE]” where IDX is the index that was given and SIZE is
//the size of the list. NOTE: It is allowed to insert at the index after
//the last element. Also, the braces in this message are different from
//those in the elementAt range error.
void CharLinkedList::insertAt(char c, int index) {
    std::stringstream ss;
    if(index<0||index>size()){
        ss<<"index ("<<index<<") not in range [0.."<<size()<<"]";
        throw std::range_error(ss.str());
    }

    Node *node= new Node();
    node->c=c;
    if(index==size() ){//if it is inserting at the tail
         //since we use the tail ptr , it is no need to iterate to find the last node
        this->tail->next=node;
        node->previous=this->tail;
        node->next= nullptr;
        //update the tail ptr to the new created node;
        this->tail=node;
        this->m_size++;
        return;
    }
    //index : [0,size)
    Node * p= indexOf(index);
    node->previous=p->previous;
    p->previous->next=node;
    node->next=p;
    p->previous=node;

    this->m_size++;
    return;

}
//An insertInOrder function that takes an element (char), inserts it
//into the list in ASCII order, and returns nothing. When this function
//is called, it may assume the list is correctly sorted in ascending order,
//and it should insert the element at the first correct index. Example
//1: Inserting ‘C’ into “ABDEF” should yield “ABCDEF” Example 2:
//Inserting ‘A’ into “ZED” should yield “AZED.” You can rely on the
//built-in <, >, <=, >=, and == operators to compare two chars.
void CharLinkedList::insertInOrder(char c) {
    Node * p=this->head->next;
    Node * q=this->head;
    Node * node=new Node ();
    node->c=c;
    while(p && p->c<c){
        q=p;
        p=p->next;
    }
    q->next=node;
    node->previous=q;
    node->next=p;
    if(p!= nullptr)
        p->previous=node;
    else
        this->tail=node;
    m_size++;
}
void CharLinkedList::pushAtBack(char c) {
    insertAt(c,size());
}

void CharLinkedList::pushAtFront(char c) {
    insertAt(c,0);
}
//A removeAt function that takes an integer index and has a void return
//type. It removes the element at the specified index. If the index is out
//of range it should throw a C++ std::range_error exception with
//the message “index (IDX) not in range [0..SIZE)” where IDX is the
//index that was given and SIZE is the size of the list.
void CharLinkedList::removeAt(int index) {
    Node * p= indexOf(index);
    if(p==this->tail){
        this->tail=p->previous;
        tail->next= nullptr;
    }else{
        p->previous->next=p->next;
        p->next->previous=p->previous;
    }
    delete p;
    m_size--;
    return;
}
void CharLinkedList::popFromBack() {
    if(isEmpty()) throw std::runtime_error("cannot pop from empty LinkedList");
    removeAt(size()-1);
}

void CharLinkedList::popFromFront() {
    if(isEmpty()) throw std::runtime_error("cannot pop from empty LinkedList");
    removeAt(0);

}
//A clear function that takes no parameters and has a void return
//type. It makes the instance into an empty list. For example if you
//call the clear function and then the isEmpty function the isEmpty
//function should return true.
void CharLinkedList::clear() {
    while(!isEmpty()){
        popFromBack();
    }
}

std::string CharLinkedList::toString() const {
    //[CharLinkedList of size 5 <<Alice>>]
    std::stringstream ss;
    Node * p=this->head->next;
    std::string s;
    while(p){
        s+=p->c;
        p=p->next;
    }
    ss<<"[CharLinkedList of size "<<size()<<" <<"<<s <<">>]";
    return ss.str();
}

std::string CharLinkedList::toReverseString() const {
    std::stringstream ss;
    Node * p=this->tail;
    std::string s;
    while(p!=this->head){
        s+=p->c;
        p=p->previous;
    }
    ss<<"[CharLinkedList of size "<<size()<<" <<"<<s <<">>]";
    return ss.str();
}
//A concatenate function that takes a pointer to a second
//CharLinkedList and has a void return type. It adds a copy of the list
//pointed to by the parameter value to the end of the list the function
//was called from. For example if we concatenate CharLinkedListOne,
//which contains “cat” with CharLinkedListTwo, which contains
//“CHESHIRE”, CharLinkedListOne should contain “catCHESHIRE”.
//Note: An empty list concatenated with a second list is the same as
//copying the second list. Concatenating a list with an empty list doesn’t
//change the list. Also a list can be concatenated with itself,
// e.g concatenating CharLinkedListTwo with itself, results in CharLinkedListTwo
//containing “CHESHIRECHESHIRE”.
void CharLinkedList::concatenate(CharLinkedList *other) {
    if(other->isEmpty())
        return;
    CharLinkedList * temp=new CharLinkedList();
    for(int i=0;i<other->size();++i)
        temp->pushAtBack(other->elementAt(i));
    for(int i=0;i<temp->size();++i)
        this->pushAtBack(temp->elementAt(i));
    delete temp;
}