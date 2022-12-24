美国塔夫茨大学数据结构课的小作业，实现一个双向链表。



# Purpose

This program implements  a doubly linked character list class, with some methods for storing ,altering and geting the elements in the list. By comparing and analysing the performance of this program and ArrayList program on various operations, we can find the differences between the two data structures and their respective characteristics.



#  Acknowledgements



# FILES

CharLinkedList.h  : the class definition of the doubly linked character list 

CharLinkedList.cpp  : implementations of the methods defined in the CharLinkedList.h file

timer_main.cpp  : timer to test the linkedlist and take time measurements.

unit_tests.h : unit test files. it contains some test funcitons for the CharLinkedList.

Makefile  :Used to make compilation and unit testing easier, creates an  executable allows for compilation of all files, and execution of unit test.



# COMPILE &RUN

type "make" to use the makefile to build the project  and then run the ./timer to test the code performance.

# Data structures and Algorithms 

The program designs a doubly linked list with a head node and a tail pointer.

#### head node

The head node is a dummy node , once a LinkedList is constructed, it will create a head node first, and then make the head and tail point to the dummy node. The first element of list is head->next;

so if the tail ptr equals head ptr, it means that this list is empty.

#### tail pointer

I use a tail pointer which always point to the last element( head node if empty) in the list. Because there are some operations on the tail, such as last(), popBack(), pushBack() . Without a tail pointer, these operations would iterate from the head to the end , which would be time-consuming.



#### size

there is a private member called "size", this is the size of the list. "size" needs to be maintained every time a node is inserted or deleted from a linked list .

For the size() method is often used in the program, It's a waste of time to iterate to count size every time we use it. Method size()  just return the value of member "size".

Also this member can improve the iteration of the list. If we want to get the Index th element then firstly we should compare the index with size/2 . If index is less than size/2 ,that means the target element is more close to head, so we can iterate forward to find this element. Otherwise , it is more close to tail, so we can use tail ptr and the previous field to iterate backward.



LinkedLists are efficient for adding or removing from the front or near the front. When adding to a LinkedList, nodes do not have to be shifted, however, without a tail pointer, it can be inefficient to add or remove from the tail. Also , LinkedList does not support random access,  it requires iteration to access middle elements, which makes ACCESS operation  inefficient.



#### some ideas to improve the performance:

Some method need iteration , but there is no interface to iterate a list . See the following method

```C++
CharLinkedList::CharLinkedList(const CharLinkedList &other) {
    initHeadNode();
    for(int i=0;i<other.size();++i)
        pushAtBack(other.elementAt(i)); //not efficient
}
```

pushAtBack(other.elementAt(i));  This line iterate the whole  list to get the element i each time it is executed. However, the next element we need is right after the current element, so this method causes too many iterations.

A solution is to define a Iterator class :

```
class Iterator {
public:
    bool hasNext();
    char next();
private:
	Node * present; 
}
```

Use iterators to improve the efficiency of sequential iteration.



# Test

The test code is in the unit_tests.h 

I have tested each of the functions implemented in LinkedList, taking into account some edge cases. For example, inserting element into a empty list, removing from a empty list(this will throw a out of range exception ) , inserting a node at the tail of the list, finding a node with a negative index(  throw a out of range exception ) , trying pop from a empty list(throw a runtime_error), concatenating self and so on.

# Answer Question

1. There are three categories of operations listed (insertion, removal, and access). Within each category, list the times each operation took and rank the operations from fastest to slowest. 

   The result of timer :

   All operations below are run on a separate, randomly generated CharLinkedList of size 100000.

   | rank | INSERTION OPERATION               | Time (nanoseconds) |
   | ---- | --------------------------------- | ------------------ |
   | 1    | pushAtBack 100 times              | 27256              |
   | 2    | pushAtFront 100 times             | 53247              |
   | 3    | insertAt middle of list 100 times | 14448270           |

   | rank | REMOVAL OPERATION                 | Time (nanoseconds) |
   | ---- | --------------------------------- | ------------------ |
   | 1    | popFromFront 100 times            | 27474              |
   | 2    | popFromBack 100 times             | 27546              |
   | 3    | removeAt middle of list 100 times | 16090495           |

   | rank | ACCESS OPERATION                              | Time (nanoseconds) |
   | ---- | --------------------------------------------- | ------------------ |
   | 1    | call last() 100 times                         | 421                |
   | 2    | call first() 100 times                        | 25577              |
   | 3    | call elementAt() for middle of list 100 times | 15921032           |

   

2. Discuss these rankings. Why were certain operations so much faster or slower than others? What are the features of linked lists that cause these disparities? 

   According to the results of the above table, it is easy to find that the operation on the head and tail of the list is much more efficient than the operation on the middle of the list.

   Because  the middle operation must iterate to find the node  that corresponds to  the given index, which causes too many pointer operations. 
   If the operation occurs at the head/tail of the list, only a few nodes need to be manipulated, that is faster than iteration.

   why the fisrt operation is slower than last operation in the table ? Beacause  I maintain a tail pointer to get the last element directly.However, if we want to get the first element of the linked list, we need to firstly access the "next" feild of the head node( head is a dummy node) ,  which is 1 operation more than getting the last element.

   Linked list work well at the head and tail, and require some iterations if it works in the middle.

   

3. Now compare these measurements with the measurements you took for HW1. Which operations are faster when using array lists? Which are faster using linked lists? Why?



**access operation on ArrayList is faster than that of LinkedList.** Because ArrayList support random access, the access  time complexity is O(1). Access operaiton on LinkedList needs iteration , the time  complexity is O(n);

**insertion and removal operation on LinkedList is faster than that of ArrayList ,especially for head and tail operation.** Because very little pointer manipulation is required for LinkedList when inserting or removing a node from its positon. Inserting and removing elements may cause element movement for ArrayList