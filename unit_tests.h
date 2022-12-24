/*
 *  unit_tests.h
 *  YOUR NAME HERE
 *  DATE CREATED
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 *  FILE PURPOSE HERE
 *	Multiple test cases to test the Double Linked List
 */
#include "CharLinkedList.h"
#include <iostream>
#include <cassert>
#include <memory>
using namespace std;
/// <summary>
/// test the default constructor of CharLinkedList
/// </summary>
void defaultConstructorTest() {
	shared_ptr<CharLinkedList> list= shared_ptr<CharLinkedList>(new CharLinkedList());
	cout << list->toString() << endl;
	cout << list->toReverseString() << endl;
	assert(list->isEmpty());

}
/// <summary>
/// test the Constructor with argument (char c)
/// </summary>
void charArgConstructorTest() {
	shared_ptr<CharLinkedList> list = shared_ptr<CharLinkedList>(new CharLinkedList('3'));
	cout << list->toString() << endl;
	cout << list->toReverseString() << endl;
	assert(list->size() == 1);
}
/// <summary>
/// test the constrctor with argument char[]
/// </summary>

void arrayConstructorTest() {
	char arr[] = { 'a','b','c','d','e','f','g' };
	shared_ptr<CharLinkedList> list = shared_ptr<CharLinkedList>(new CharLinkedList(arr, sizeof(arr)));
	cout << list->toString() << endl;
	cout << list->toReverseString() << endl;
}
/// <summary>
/// test the copy constructor
/// </summary>
void copyConstructorTest() {
	char arr[] = { 'a','b','c','d','e','f','g' };
	shared_ptr<CharLinkedList> srcList = shared_ptr<CharLinkedList>(new CharLinkedList(arr, sizeof(arr)));
	cout << "srcList = " << srcList->toString() << endl;
	shared_ptr<CharLinkedList> dstList = shared_ptr<CharLinkedList>(new CharLinkedList(*srcList));
	cout << "dstList = " << dstList->toString() << endl;

	///test it is really deep copy

	srcList->replaceAt('@', 1);
	cout << "srcList = " << srcList->toString() << endl;
	cout << "dstList = " << dstList->toString() << endl;

	
	//test the empty copy 
	srcList = shared_ptr<CharLinkedList>(new CharLinkedList());
	dstList = shared_ptr<CharLinkedList>(new CharLinkedList(*srcList));
	cout << "srcList = " << srcList->toString() << endl;
	cout << "dstList = " << dstList->toString() << endl;
}
/// <summary>
/// test the operator = 
/// </summary>
void assignmentTest() {
	char arr[] = { 'a','b','c','d','e','f','g' };
	shared_ptr<CharLinkedList> srcList = shared_ptr<CharLinkedList>(new CharLinkedList(arr, sizeof(arr)));
	shared_ptr<CharLinkedList> dstList = shared_ptr<CharLinkedList>(new CharLinkedList('4'));
	cout << "srcList = " << srcList->toString() << endl;
	cout << "dstList = " << dstList->toString() << endl;

	*dstList = *srcList;
	cout << "srcList = " << srcList->toString() << endl;
	cout << "dstList = " << dstList->toString() << endl;
}
/// <summary>
/// test the empty() and size() 
/// it must be empty when the size=0;
/// </summary>
void empty_sizeTest() {
	shared_ptr<CharLinkedList> list = shared_ptr<CharLinkedList>(new CharLinkedList('4'));
	assert(list->size() == 1 && list->isEmpty() == false);
	list->clear();
	assert(list->size() == 0 && list->isEmpty() == true);
}
/// <summary>
/// test the first(),this will throw an exception if the list is empty
/// </summary>
void firstTest() {
	shared_ptr<CharLinkedList> list = shared_ptr<CharLinkedList>(new CharLinkedList('4'));
	assert(list->first() == '4');
	list = shared_ptr<CharLinkedList>(new CharLinkedList());
	list->first(); //this will throw an exception  "cannot get first of empty LinkedList"
}
/// <summary>
/// test the last() ,it will return the last element of the list,but throw an exception if the list is empty
/// </summary>
void lastTest() {
	char arr[] = { 'a','b','c','d','e','f','g' };
	shared_ptr<CharLinkedList> list = shared_ptr<CharLinkedList>(new CharLinkedList(arr, sizeof(arr)));
	assert(list->last() == 'g');
	list = shared_ptr<CharLinkedList>(new CharLinkedList());
	list->last();//this will throw an exception  "cannot get last of empty LinkedList"
}
/// <summary>
/// the pushFront and pushBack method are based the insertAt method.
/// some edge case are here,insert at the 0 index or at the tail.
/// </summary>
void insertTest() {
	shared_ptr<CharLinkedList> list = shared_ptr<CharLinkedList>(new CharLinkedList());
	list->insertAt('a', 0);  
	list->insertAt('b', 0);// insert at the head
	list->insertAt('e', 1);//insert at the middle
	// edge case insert  at the tail of list ,it is ok.
	list->insertAt('c', 3);
	cout << list->toString() << endl; //[CharLinkedList of size 4 <<beac>>]
	//   the following code will throw out of range exception;
	list->insertAt('c', -1);
}
/// <summary>
/// test the insertInOrder, if the original list is an empty list, repeated invoke this 
/// method will make it in ASC order
/// </summary>
void insertOrderTest() {
	shared_ptr<CharLinkedList> list = shared_ptr<CharLinkedList>(new CharLinkedList());
	list->insertInOrder('f');
	list->insertInOrder('c');
	list->insertInOrder('g');
	list->insertInOrder('a');
	list->insertInOrder('b');
	cout << list->toString() << endl; //[abcfg]


	//special ,if the given list is [ZED] then insert A 
	// it should insert the element at the first correct index
	char arr[3] = { 'Z','E','D' };
	list = shared_ptr<CharLinkedList>(new CharLinkedList(arr,3));
	list->insertInOrder('A');
	cout << list->toString() << endl;// [AZED]
}
/// <summary>
/// the popFront and popBack are based on removeAt() 
/// some edge case are here
/// </summary>
void removeTest() {
	char arr[] = { 'a','b','c','d','e','f','g' };
	shared_ptr<CharLinkedList> list = shared_ptr<CharLinkedList>(new CharLinkedList(arr, sizeof(arr)));
	list->removeAt(0);//remove at head; this equals popFront
	list->popFromFront();
	list->removeAt(2);//remove middle
	
	list->removeAt(list->size() - 1); // remove at tail, this euqals popBack
	list->popFromBack();
	cout << list->toString() << endl;
	list->removeAt(list->size()); //this must throw an out of range exception  

}
/// <summary>
/// test the replaceAt()method 
/// </summary>
void testReplace() {
	char arr[] = { 'a','b','c','d','e','f','g' };
	shared_ptr<CharLinkedList> list = shared_ptr<CharLinkedList>(new CharLinkedList(arr, sizeof(arr)));
	list->replaceAt( '@',3);
	assert(list->elementAt(3) == '@');
}
/// <summary>
/// test concatenate two list, including the empty ones,and concatenate itself
/// </summary>
void concatenateTest() {
	char arr1[] = { 'a','b','c','d','e','f','g' };
	shared_ptr<CharLinkedList> list1 = shared_ptr<CharLinkedList>(new CharLinkedList(arr1, sizeof(arr1)));
	char arr2[] = { '1','2','3','4','5' };
	shared_ptr<CharLinkedList> list2 = shared_ptr<CharLinkedList>(new CharLinkedList(arr2, sizeof(arr2)));
	list1->concatenate(list2.get());
	cout << list1->toString() << endl;

	// concatenate empty list
	list2->clear();
	assert(list2->isEmpty());
	list1->concatenate(list2.get());
	cout << list1->toString() << endl;

	// self concatenate

	list1->concatenate(list1.get());
	cout << list1->toString() << endl;
}